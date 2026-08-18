// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef CAMERA_HPP
#define CAMERA_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <algorithm>
#include <cmath>
#include <string>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../core/math_core.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Math
{
    struct Camera
    {
        //-----------------------------------------------------------------------------------------------------------------//
        const float m_CAMERA_MIN_PITCH_DEGREES_f = -89.0f;
        const float m_CAMERA_MIN_PITCH_RADIANS_f = m_CAMERA_MIN_PITCH_DEGREES_f * Math::Core::RADIANS_PER_DEGREE_f;

        const float m_CAMERA_MAX_PITCH_DEGREES_f = 89.0f;
        const float m_CAMERA_MAX_PITCH_RADIANS_f = m_CAMERA_MAX_PITCH_DEGREES_f * Math::Core::RADIANS_PER_DEGREE_f;
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Transform.
        //-----------------------------------------------------------------------------------------------------------------//
        Math::Core::Vec3_f m_position;    // Camera position.

        // Euler angles (radians).
        float m_pitch_rads;         // Rotation around local X axis.
        float m_yaw_rads;           // Rotation around local Y axis.
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Projection parameters.
        //-----------------------------------------------------------------------------------------------------------------//
        float m_fov_rads;
        float m_near_plane;
        float m_far_plane;
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Orientation vectors.
        //-----------------------------------------------------------------------------------------------------------------//
        Math::Core::Vec3_f m_world_up;    // World up direction.

        Math::Core::Vec3_f m_front;       // Forward direction.
        Math::Core::Vec3_f m_right;       // Right direction.
        Math::Core::Vec3_f m_up;          // Camera up direction.
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        Camera
        (
            const Math::Core::Vec3_f& position,
            const float pitch_rads,
            const float yaw_rads,
            const float fov_rads,
            const float near_plane,
            const float far_plane,
            const Math::Core::Vec3_f& world_up
        )
        {
            m_position = position;

            m_pitch_rads = std::clamp<float>(pitch_rads, m_CAMERA_MIN_PITCH_RADIANS_f, m_CAMERA_MAX_PITCH_RADIANS_f);
            m_yaw_rads   = std::fmod(yaw_rads, Math::Core::TWO_PI_f);

            m_fov_rads   = fov_rads;
            m_near_plane = near_plane;
            m_far_plane  = far_plane;

            m_world_up = world_up;
            m_world_up.normalise();

            this->updateVectors();
        }

        inline void updateVectors()
        {
            m_front = Math::Core::Vec3_f
            (
                cosf(m_pitch_rads) * sinf(m_yaw_rads),
                sinf(m_pitch_rads),
                cosf(m_pitch_rads) * cosf(m_yaw_rads)
            );
            m_front.normalise();

            Math::Core::crossProduct(m_right, m_front, m_world_up);
            m_right.normalise();

            Math::Core::crossProduct(m_up, m_right, m_front);
            m_up.normalise();
        }

        inline void moveForward(const float offset)
        {
            Math::Core::Vec3_f forward = m_front;
            forward.m_data[1] = 0.0f;
            forward.normalise();

            m_position = m_position + (forward * offset);
        }
        inline void moveRight(const float offset)
        {
            Math::Core::Vec3_f right = m_right;
            right.m_data[1] = 0.0f;
            right.normalise();

            m_position = m_position + (right * offset);
        }
        inline void moveUp(const float offset)
        {
            Math::Core::Vec3_f up = m_up;
            up.m_data[0] = 0.0f;
            up.m_data[2] = 0.0f;
            up.normalise();

            m_position = m_position + (up * offset);
        }

        inline void lookRight(const float offset)
        {
            m_yaw_rads += offset;
            m_yaw_rads = std::fmod(m_yaw_rads, Math::Core::TWO_PI_f);

            this->updateVectors();
        }
        inline void lookUp(const float offset)
        {
            m_pitch_rads += offset;
            m_pitch_rads = std::clamp<float>(m_pitch_rads, m_CAMERA_MIN_PITCH_RADIANS_f, m_CAMERA_MAX_PITCH_RADIANS_f);

            this->updateVectors();
        }

        inline Math::Core::Mat4_f calcViewMatrix() const
        {
            Math::Core::Mat4_f new_mat;
            new_mat.lookAt
            (
                m_position.m_data[0], m_position.m_data[1], m_position.m_data[2],
                m_front.m_data[0], m_front.m_data[1], m_front.m_data[2], 
                m_right.m_data[0], m_right.m_data[1], m_right.m_data[2], 
                m_up.m_data[0], m_up.m_data[1], m_up.m_data[2]
            );
            return new_mat;
        }
        inline Math::Core::Mat4_f calcProjectionMatrix(const float aspect_ratio) const
        {
            Math::Core::Mat4_f new_mat;
            new_mat.perspective(m_fov_rads, aspect_ratio, m_near_plane, m_far_plane);
            return new_mat;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        inline std::string toString(int min_num_width, int num_decimals)
        {
            std::string result =
                std::string("CAM POSITION: ") + m_position.toStringRow(min_num_width, num_decimals) + std::string("\n") +
                std::string("CAM WORLD UP: ") + m_world_up.toStringRow(min_num_width, num_decimals) + std::string("\n") +
                std::string("CAM FRONT:    ") + m_front.toStringRow(min_num_width, num_decimals)    + std::string("\n") +
                std::string("CAM RIGHT:    ") + m_right.toStringRow(min_num_width, num_decimals)    + std::string("\n") +
                std::string("CAM UP:       ") + m_up.toStringRow(6, 2);

            return result;
        }
        //-----------------------------------------------------------------------------------------------------------------//
    };
};

/*
struct Camera
{
    //---------------------------------------------------------------------------------------------------------------------//
    // Transform.
    //---------------------------------------------------------------------------------------------------------------------//
    Math::Core::Vec3_f     m_position;  // Camera position.
    Math::Core::Quaternion m_rotation;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Orientation vectors (Derived data).
    //---------------------------------------------------------------------------------------------------------------------//
    Math::Core::Vec3_f m_world_up = Math::Core::Vec3_f(0.0f, 1.0f,  0.0f);
    Math::Core::Vec3_f m_front    = Math::Core::Vec3_f(0.0f, 0.0f, -1.0f);
    Math::Core::Vec3_f m_right    = Math::Core::Vec3_f(1.0f, 0.0f,  0.0f);
    Math::Core::Vec3_f m_up       = Math::Core::Vec3_f(0.0f, 1.0f,  0.0f);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Projection parameters.
    //---------------------------------------------------------------------------------------------------------------------//
    float m_fov_rads;
    float m_near_plane;
    float m_far_plane;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    Camera
    (
        const Math::Core::Vec3_f& position,
        const float               fov_rads,
        const float               near_plane,
        const float               far_plane
    )
    {
        m_position = position;

        m_fov_rads   = fov_rads;
        m_near_plane = near_plane;
        m_far_plane  = far_plane;

        this->updateVectors();
    }

    inline void updateVectors()
    {
        Math::Core::Mat4_f rotation_matrix = m_rotation.toRotationMatrix();

        static const Math::Core::Vec4_f local_front(0.0f, 0.0f, -1.0f, 0.0f);
        static const Math::Core::Vec4_f local_right(1.0f, 0.0f,  0.0f, 0.0f);
        static const Math::Core::Vec4_f local_up   (0.0f, 1.0f,  0.0f, 0.0f);

        Math::Core::Vec4_f front = rotation_matrix * local_front;
        Math::Core::Vec4_f right = rotation_matrix * local_right;
        Math::Core::Vec4_f up    = rotation_matrix * local_up;

        m_front = Math::Core::Vec3_f(front.m_data[0], front.m_data[1], front.m_data[2]);
        m_right = Math::Core::Vec3_f(right.m_data[0], right.m_data[1], right.m_data[2]);
        m_up    = Math::Core::Vec3_f(up.m_data[0], up.m_data[1], up.m_data[2]);
    }

    inline void moveForward(const float offset)
    {
        Math::Core::Vec3_f forward = m_front;
        forward.m_data[1] = 0.0f;
        forward.normalise();

        m_position = m_position + (forward * offset);
    }
    inline void moveRight(const float offset)
    {
        Math::Core::Vec3_f right = m_right;
        right.m_data[1] = 0.0f;
        right.normalise();

        m_position = m_position + (right * offset);
    }
    inline void moveUp(const float offset)
    {
        Math::Core::Vec3_f up = m_up;
        up.m_data[0] = 0.0f;
        up.m_data[2] = 0.0f;
        up.normalise();

        m_position = m_position + (up * offset);
    }

    inline void lookRight(const float offset)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle
        (
            m_world_up.m_data[0],
            m_world_up.m_data[1],
            m_world_up.m_data[2],
            offset
        );

        m_rotation = delta * m_rotation;
        m_rotation.normalise();

        updateVectors();
    }
    inline void lookUp(const float offset)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle
        (
            m_right.m_data[0],
            m_right.m_data[1],
            m_right.m_data[2],
            offset
        );

        m_rotation = m_rotation * delta;
        m_rotation.normalise();

        updateVectors();
    }

    inline Math::Core::Mat4_f calcViewMatrix() const
    {
        Math::Core::Mat4_f new_mat;
        new_mat.lookAt
        (
            m_position.m_data[0], m_position.m_data[1], m_position.m_data[2],
            m_front.m_data[0], m_front.m_data[1], m_front.m_data[2], 
            m_right.m_data[0], m_right.m_data[1], m_right.m_data[2], 
            m_up.m_data[0], m_up.m_data[1], m_up.m_data[2]
        );
        return new_mat;
    }
    inline Math::Core::Mat4_f calcProjectionMatrix(const float aspect_ratio) const
    {
        Math::Core::Mat4_f new_mat;
        new_mat.perspective(m_fov_rads, aspect_ratio, m_near_plane, m_far_plane);
        return new_mat;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    inline std::string toString(int min_num_width, int num_decimals)
    {
        std::string result =
            std::string("CAM POSITION: ") + m_position.toStringRow(min_num_width, num_decimals) + std::string("\n") +
            std::string("CAM WORLD UP: ") + m_world_up.toStringRow(min_num_width, num_decimals) + std::string("\n") +
            std::string("CAM FRONT:    ") + m_front.toStringRow(min_num_width, num_decimals)    + std::string("\n") +
            std::string("CAM RIGHT:    ") + m_right.toStringRow(min_num_width, num_decimals)    + std::string("\n") +
            std::string("CAM UP:       ") + m_up.toStringRow(6, 2);

        return result;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    inline Math::Core::Vec3_f rotateVector(const Math::Core::Vec3_f& vector) const
    {
        Math::Core::Quaternion vector_quaternion(vector.m_data[0], vector.m_data[1], vector.m_data[2], 0.0f);

        Math::Core::Quaternion result = m_rotation * vector_quaternion * m_rotation.conjugate();

        return Math::Core::Vec3_f(result.m_x, result.m_y, result.m_z);
    }
};
*/
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
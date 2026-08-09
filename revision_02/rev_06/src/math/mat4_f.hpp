// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef MAT4_F_HPP
#define MAT4_F_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <string>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../utils/utils.hpp"

#include "vec4_f.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Math
{
    struct Mat4_f
    {
        //-----------------------------------------------------------------------------------------------------------------//
        float m_data[16];
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Standard constructor.
        //-----------------------------------------------------------------------------------------------------------------//
        Mat4_f()
        {
            for(int i = 0; i < 16; i++)
            {
                m_data[i] = 0.0f;
            }
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Copy constructors.
        //-----------------------------------------------------------------------------------------------------------------//
        Mat4_f(const Mat4_f& other)
        {
            for(int i = 0; i < 16; i++)
            {
                m_data[i] = other.m_data[i];
            }
        }

        Mat4_f& operator=(const Mat4_f& other)
        {
            for(int i = 0; i < 16; i++)
            {
                m_data[i] = other.m_data[i];
            }
            return *this;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Comparison operator overloads.
        //-----------------------------------------------------------------------------------------------------------------//
        bool operator==(const Mat4_f& other) const
        {
            for(int i = 0; i < 16; i++)
            {
                if(Utils::checkFloatEquals(m_data[i], other.m_data[i]) == false)
                {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Mat4_f& other) const
        {
            for(int i = 0; i < 16; i++)
            {
                if(Utils::checkFloatEquals(m_data[i], other.m_data[i]) == true)
                {
                    return false;
                }
            }
            return true;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Arithmetic operator overloads.
        //-----------------------------------------------------------------------------------------------------------------//
        Mat4_f operator+(const Mat4_f& rhs) const
        {
            Mat4_f new_mat;

            for(int i = 0; i < 16; i++)
            {
                new_mat.m_data[i] = m_data[i] + rhs.m_data[i];
            }

            return new_mat;
        }

        Mat4_f operator-(const Mat4_f& rhs) const
        {
            Mat4_f new_mat;

            for(int i = 0; i < 16; i++)
            {
                new_mat.m_data[i] = m_data[i] - rhs.m_data[i];
            }

            return new_mat;
        }

        Mat4_f operator*(const float scalar) const
        {
            Mat4_f new_mat;

            for(int i = 0; i < 16; i++)
            {
                new_mat.m_data[i] = m_data[i] * scalar;
            }

            return new_mat;
        }

        // ROW MAJOR MULTIPLICATION
        Mat4_f operator*(const Mat4_f& rhs) const
        {
            Mat4_f new_mat;

            for(int row = 0; row < 4; row++)
            {
                for(int col = 0; col < 4; col++)
                {
                    float value = 0.0f;

                    for(int i = 0; i < 4; i++)
                    {
                        value += m_data[(row * 4) + i] * rhs.m_data[(i * 4) + col];
                    }

                    new_mat.m_data[(row * 4) + col] = value;
                }
            }

            return new_mat;
        }

        Vec4_f operator*(const Vec4_f& rhs) const
        {
            Vec4_f new_vec;

            for(int row = 0; row < 4; row++)
            {
                float value =
                    m_data[(row * 4) + 0] * rhs.m_data[0] +
                    m_data[(row * 4) + 1] * rhs.m_data[1] +
                    m_data[(row * 4) + 2] * rhs.m_data[2] +
                    m_data[(row * 4) + 3] * rhs.m_data[3];

                new_vec.m_data[row] = value;
            }

            return new_vec;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Single-Object Operations.
        //-----------------------------------------------------------------------------------------------------------------//
        inline void identity()
        {
            m_data[0]  = 1.0f;    m_data[1]   = 0.0f;    m_data[2]  = 0.0f;    m_data[3]  = 0.0f;
            m_data[4]  = 0.0f;    m_data[5]   = 1.0f;    m_data[6]  = 0.0f;    m_data[7]  = 0.0f;
            m_data[8]  = 0.0f;    m_data[9]   = 0.0f;    m_data[10] = 1.0f;    m_data[11] = 0.0f;
            m_data[12] = 0.0f;    m_data[13]  = 0.0f;    m_data[14] = 0.0f;    m_data[15] = 1.0f;
        }

        inline void translation(const float x, const float y, const float z)
        {
            m_data[0]  = 1.0f;    m_data[1]   = 0.0f;    m_data[2]  = 0.0f;    m_data[3]  = x;
            m_data[4]  = 0.0f;    m_data[5]   = 1.0f;    m_data[6]  = 0.0f;    m_data[7]  = y;
            m_data[8]  = 0.0f;    m_data[9]   = 0.0f;    m_data[10] = 1.0f;    m_data[11] = z;
            m_data[12] = 0.0f;    m_data[13]  = 0.0f;    m_data[14] = 0.0f;    m_data[15] = 1.0f;
        }

        inline void rotation(const float axis_x, const float axis_y, const float axis_z, const float theta_rad)
        {
            //-------------------------------------------------------------------------------------------------------------//
            float x;
            float y;
            float z;

            float length = axis_x + axis_y + axis_z;
            length = sqrtf(length);

            if(length == 0.0f)
            {
                x = 0.0f;
                y = 0.0f;
                z = 0.0f;
            }
            else
            {
                x = axis_x / length;
                y = axis_y / length;
                z = axis_z / length;
            }   

            if( (x == 0.0f) && (y == 0.0f) && (z == 0.0f) )
            {
                this->identity();
                return;
            }

            float cos_theta = cosf(theta_rad);
            float sin_theta = sinf(theta_rad);
            float one_minus_cos_theta = 1.0f - cos_theta;
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Row-major rotation matrix

            m_data[0]  = cos_theta + (x * x * one_minus_cos_theta);
            m_data[1]  = (x * y * one_minus_cos_theta) - (z * sin_theta);
            m_data[2]  = (x * z * one_minus_cos_theta) + (y * sin_theta);
            m_data[3]  = 0.0f;

            m_data[4]  = (y * x * one_minus_cos_theta) + (z * sin_theta);
            m_data[5]  = cos_theta + (y * y * one_minus_cos_theta);
            m_data[6]  = (y * z * one_minus_cos_theta) - (x * sin_theta);
            m_data[7]  = 0.0f;

            m_data[8]  = (z * x * one_minus_cos_theta) - (y * sin_theta);
            m_data[9]  = (z * y * one_minus_cos_theta) + (x * sin_theta);
            m_data[10] = cos_theta + (z * z * one_minus_cos_theta);
            m_data[11] = 0.0f;

            m_data[12] = 0.0f;
            m_data[13] = 0.0f;
            m_data[14] = 0.0f;
            m_data[15] = 1.0f;
            //-------------------------------------------------------------------------------------------------------------//
        }

        inline void scale(const float x, const float y, const float z)
        {
            m_data[0]  = x;       m_data[1]  = 0.0f;    m_data[2]  = 0.0f;    m_data[3]  = 0.0f;
            m_data[4]  = 0.0f;    m_data[5]  = y;       m_data[6]  = 0.0f;    m_data[7]  = 0.0f;
            m_data[8]  = 0.0f;    m_data[9]  = 0.0f;    m_data[10] = z;       m_data[11] = 0.0f;
            m_data[12] = 0.0f;    m_data[13] = 0.0f;    m_data[14] = 0.0f;    m_data[15] = 1.0f;
        }

        inline void perspective(const float fov_radians, const float aspect_ratio, const float near_plane, const float far_plane)
        {
            if( (near_plane <= 0.0f) || (far_plane <= near_plane) )
            {
                this->identity();
                return;
            }

            float focal_length = 1.0f / tanf(fov_radians * 0.5f);

            m_data[0]  = focal_length / aspect_ratio;
            m_data[1]  = 0.0f;
            m_data[2]  = 0.0f;
            m_data[3]  = 0.0f;

            m_data[4]  = 0.0f;
            m_data[5]  = focal_length;
            m_data[6]  = 0.0f;
            m_data[7]  = 0.0f;

            m_data[8]  = 0.0f;
            m_data[9]  = 0.0f;
            m_data[10] = -(far_plane + near_plane) / (near_plane - far_plane);
            m_data[11] = -(2.0f * far_plane * near_plane) / (near_plane - far_plane);

            m_data[12] = 0.0f;
            m_data[13] = 0.0f;
            m_data[14] = -1.0f;
            m_data[15] = 0.0f;
        }

        /*
        // Ortho currently broken
        inline void orthographic
        (
            const float left,
            const float right,
            const float bottom,
            const float top,
            const float near_plane,
            const float far_plane
        )
        {
            if( (right <= left) || (top <= bottom) || (far_plane <= near_plane) )
            {
                this->identity();
                return;
            }

            m_data[0]  = 2.0f / (right - left);
            m_data[1]  = 0.0f;
            m_data[2]  = 0.0f;
            m_data[3]  = -(right + left) / (right - left);

            m_data[4]  = 0.0f;
            m_data[5]  = 2.0f / (top - bottom);
            m_data[6]  = 0.0f;
            m_data[7]  = -(top + bottom) / (top - bottom);

            m_data[8]  = 0.0f;
            m_data[9]  = 0.0f;
            m_data[10] = -2.0f / (far_plane - near_plane);
            m_data[11] = -(far_plane + near_plane) / (far_plane - near_plane);

            m_data[12] = 0.0f;
            m_data[13] = 0.0f;
            m_data[14] = 0.0f;
            m_data[15] = 1.0f;
        }
        */

        inline void lookAt
        (
            float cam_pos_x, float cam_pos_y, float cam_pos_z,
            float cam_direction_x, float cam_direction_y, float cam_direction_z, 
            float cam_right_x, float cam_right_y, float cam_right_z, 
            float cam_up_x, float cam_up_y, float cam_up_z
        )
        {
            float pos_dot_right = (cam_pos_x * cam_right_x) + (cam_pos_y * cam_right_y) + (cam_pos_z * cam_right_z);
            float pos_dot_up = (cam_pos_x * cam_up_x) + (cam_pos_y * cam_up_y) + (cam_pos_z * cam_up_z);
            float pos_dot_dir = (cam_pos_x * cam_direction_x) + (cam_pos_y * cam_direction_y) + (cam_pos_z * cam_direction_z);

            m_data[0]  = cam_right_x;
            m_data[1]  = cam_right_y;
            m_data[2]  = cam_right_z;
            m_data[3]  = -pos_dot_right;

            m_data[4]  = cam_up_x;
            m_data[5]  = cam_up_y;
            m_data[6]  = cam_up_z;
            m_data[7]  = -pos_dot_up;

            m_data[8]  = -cam_direction_x;
            m_data[9]  = -cam_direction_y;
            m_data[10] = -cam_direction_z;
            m_data[11] = pos_dot_dir;

            m_data[12] = 0.0f;
            m_data[13] = 0.0f;
            m_data[14] = 0.0f;
            m_data[15] = 1.0f;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Visulisation.
        //-----------------------------------------------------------------------------------------------------------------//
        std::string toString(int min_num_width, int num_decimals) const
        {
            return
            (
                std::string("[") +
                Utils::floatToString(m_data[0], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[1], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[2], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[3], min_num_width, num_decimals) +
                std::string("]") +
                std::string("\n") +
                std::string("[") +
                Utils::floatToString(m_data[4], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[5], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[6], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[7], min_num_width, num_decimals) +
                std::string("]") +
                std::string("\n") +
                std::string("[") +
                Utils::floatToString(m_data[8], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[9], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[10], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[11], min_num_width, num_decimals) +
                std::string("]") +
                std::string("\n") +
                std::string("[") +
                Utils::floatToString(m_data[12], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[13], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[14], min_num_width, num_decimals) + std::string(", ") +
                Utils::floatToString(m_data[15], min_num_width, num_decimals) +
                std::string("]")
            );
        }
        //-----------------------------------------------------------------------------------------------------------------//
    };
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
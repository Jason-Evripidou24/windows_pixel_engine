// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "camera.hpp"

#include "../00_types/level_00/mat4/mat4_f.hpp"
#include "../00_types/level_00/vec3/vec3_f.hpp"

#include "../01_utils/math/math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Camera::Camera
(
    const Vec3_f& position,
    const float pitch_rads,
    const float yaw_rads,
    const float roll_rads,
    const float fov_rads,
    const float near_plane,
    const float far_plane,
    const Vec3_f& world_up
)
{
    m_position = position;

    m_pitch_rads = pitch_rads;
    m_yaw_rads   = yaw_rads;
    m_roll_rads  = roll_rads;

    m_fov_rads   = fov_rads;
    m_near_plane = near_plane;
    m_far_plane  = far_plane;

    m_world_up = Math::normalise(world_up);

    this->updateVectors();
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Camera::updateVectors()
{
    m_front = Vec3_f(cosf(m_pitch_rads) * cosf(m_yaw_rads), sinf(m_pitch_rads), cosf(m_pitch_rads) * sinf(m_yaw_rads));
    m_front = Math::normalise(m_front);

    m_right = Math::cross(m_front, m_world_up);
    m_right = Math::normalise(m_right);

    m_up = Math::cross(m_right, m_front);
    m_up = Math::normalise(m_up);

    if(m_roll_rads != 0.0f)
    {
        Mat4_f roll_matrix = Math::rotationMat4_f(m_front.m_data[0], m_front.m_data[1], m_front.m_data[2], m_roll_rads);

        Vec4_f up4(m_up.m_data[0], m_up.m_data[1], m_up.m_data[2], 0.0f);
        Vec4_f right4(m_right.m_data[0], m_right.m_data[1], m_right.m_data[2], 0.0f);

        up4 = Math::multiply(roll_matrix, up4);
        right4 = Math::multiply(roll_matrix, right4);

        m_up = Vec3_f(up4.m_data[0], up4.m_data[1], up4.m_data[2]);
        m_right = Vec3_f(right4.m_data[0], right4.m_data[1], right4.m_data[2]);

        m_up = Math::normalise(m_up);
        m_right = Math::normalise(m_right);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Camera::moveForward(const float offset)
{
    m_position = Math::add(m_position, Math::scalarMultiply(m_front, offset));
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Camera::moveRight(const float offset)
{
    m_position = Math::add(m_position, Math::scalarMultiply(m_right, offset));
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Camera::moveUp(const float offset)
{
    m_position = Math::add(m_position, Math::scalarMultiply(m_up, offset));
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Camera::lookRight(const float offset)
{
    m_yaw_rads += offset;
    this->updateVectors();
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Camera::lookUp(const float offset)
{
    m_pitch_rads += offset;

    // Prevent looking straight up/down.
    const float limit = 1.55334306f; // ~89 degrees.
    if(m_pitch_rads > limit)  { m_pitch_rads = limit; }
    if(m_pitch_rads < -limit) { m_pitch_rads = -limit; }

    this->updateVectors();
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Camera::rollRight(const float offset)
{
    m_roll_rads += offset;
    this->updateVectors();
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Camera::calcModelMatrix() const
{
    Mat4_f rotate = Math::rotationMat4_f(m_front.m_data[0], m_front.m_data[1], m_front.m_data[2], 0.0f);
    Mat4_f translate = Math::translationMat4_f(m_position.m_data[0], m_position.m_data[1], m_position.m_data[2]);
    return Math::multiply(translate, rotate);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Camera::calcViewMatrix() const
{
    return Math::lookAtMat4_f(m_position, m_front, m_right, m_up);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Camera::calcProjectionMatrix(const float aspect_ratio) const
{
    return Math::perspectiveMat4_f(m_fov_rads, aspect_ratio, m_near_plane, m_far_plane);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
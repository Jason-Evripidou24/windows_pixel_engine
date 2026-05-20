// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cmath>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "math.hpp"

#include "../../00_types/level_00/mat4/mat4_f.hpp"
#include "../../00_types/level_00/vec2/vec2_f.hpp"
#include "../../00_types/level_00/vec2/vec2_i.hpp"
#include "../../00_types/level_00/vec3/vec3_f.hpp"
#include "../../00_types/level_00/vec4/vec4_f.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Math::identityMat4_f()
{
    Mat4_f new_mat;

    new_mat.m_data[0]  = 1.0f;    new_mat.m_data[1]   = 0.0f;    new_mat.m_data[2]  = 0.0f;    new_mat.m_data[3]  = 0.0f;
    new_mat.m_data[4]  = 0.0f;    new_mat.m_data[5]   = 1.0f;    new_mat.m_data[6]  = 0.0f;    new_mat.m_data[7]  = 0.0f;
    new_mat.m_data[8]  = 0.0f;    new_mat.m_data[9]   = 0.0f;    new_mat.m_data[10] = 1.0f;    new_mat.m_data[11] = 0.0f;
    new_mat.m_data[12] = 0.0f;    new_mat.m_data[13]  = 0.0f;    new_mat.m_data[14] = 0.0f;    new_mat.m_data[15] = 1.0f;

    return new_mat;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Math::translationMat4_f(const float x, const float y, const float z)
{
    Mat4_f new_mat;

    new_mat.m_data[0]  = 1.0f;    new_mat.m_data[1]   = 0.0f;    new_mat.m_data[2]  = 0.0f;    new_mat.m_data[3]  = x;
    new_mat.m_data[4]  = 0.0f;    new_mat.m_data[5]   = 1.0f;    new_mat.m_data[6]  = 0.0f;    new_mat.m_data[7]  = y;
    new_mat.m_data[8]  = 0.0f;    new_mat.m_data[9]   = 0.0f;    new_mat.m_data[10] = 1.0f;    new_mat.m_data[11] = z;
    new_mat.m_data[12] = 0.0f;    new_mat.m_data[13]  = 0.0f;    new_mat.m_data[14] = 0.0f;    new_mat.m_data[15] = 1.0f;

    return new_mat;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   (axis_x, axis_y, axis_z) must create a normalised 3 dimensional vector.
*/
Mat4_f Math::rotationMat4_f(const float axis_x, const float axis_y, const float axis_z, const float theta_rad)
{
    //---------------------------------------------------------------------------------------------------------------------//
    float x = axis_x;
    float y = axis_y;
    float z = axis_z;

    float cos_theta = cosf(theta_rad);
    float sin_theta = sinf(theta_rad);
    float one_minus_cos_theta = 1.0f - cos_theta;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    Mat4_f new_mat;

    // Row-major rotation matrix (Rodrigues' formula)

    new_mat.m_data[0]  = cos_theta + (x * x * one_minus_cos_theta);
    new_mat.m_data[1]  = (x * y * one_minus_cos_theta) - (z * sin_theta);
    new_mat.m_data[2]  = (x * z * one_minus_cos_theta) + (y * sin_theta);
    new_mat.m_data[3]  = 0.0f;

    new_mat.m_data[4]  = (y * x * one_minus_cos_theta) + (z * sin_theta);
    new_mat.m_data[5]  = cos_theta + (y * y * one_minus_cos_theta);
    new_mat.m_data[6]  = (y * z * one_minus_cos_theta) - (x * sin_theta);
    new_mat.m_data[7]  = 0.0f;

    new_mat.m_data[8]  = (z * x * one_minus_cos_theta) - (y * sin_theta);
    new_mat.m_data[9]  = (z * y * one_minus_cos_theta) + (x * sin_theta);
    new_mat.m_data[10] = cos_theta + (z * z * one_minus_cos_theta);
    new_mat.m_data[11] = 0.0f;

    new_mat.m_data[12] = 0.0f;
    new_mat.m_data[13] = 0.0f;
    new_mat.m_data[14] = 0.0f;
    new_mat.m_data[15] = 1.0f;

    return new_mat;
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Math::scaleMat4_f(const float x, const float y, const float z)
{
    Mat4_f new_mat;

    new_mat.m_data[0]  = x;       new_mat.m_data[1]  = 0.0f;    new_mat.m_data[2]  = 0.0f;    new_mat.m_data[3]  = 0.0f;
    new_mat.m_data[4]  = 0.0f;    new_mat.m_data[5]  = y;       new_mat.m_data[6]  = 0.0f;    new_mat.m_data[7]  = 0.0f;
    new_mat.m_data[8]  = 0.0f;    new_mat.m_data[9]  = 0.0f;    new_mat.m_data[10] = z;       new_mat.m_data[11] = 0.0f;
    new_mat.m_data[12] = 0.0f;    new_mat.m_data[13] = 0.0f;    new_mat.m_data[14] = 0.0f;    new_mat.m_data[15] = 1.0f;

    return new_mat;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Math::perspectiveMat4_f(const float fov_radians, const float aspect_ratio, const float near, const float far)
{
    if( (near <= 0.0f) || (far <= near) ) { return Math::identityMat4_f(); }

    Mat4_f new_mat;

    float focal_length = 1.0f / tanf(fov_radians * 0.5f);

    new_mat.m_data[0]  = focal_length / aspect_ratio;
    new_mat.m_data[1]  = 0.0f;
    new_mat.m_data[2]  = 0.0f;
    new_mat.m_data[3]  = 0.0f;

    new_mat.m_data[4]  = 0.0f;
    new_mat.m_data[5]  = focal_length;
    new_mat.m_data[6]  = 0.0f;
    new_mat.m_data[7]  = 0.0f;

    new_mat.m_data[8]  = 0.0f;
    new_mat.m_data[9]  = 0.0f;
    new_mat.m_data[10] = (far + near) / (near - far);
    new_mat.m_data[11] = (2.0f * far * near) / (near - far);

    new_mat.m_data[12] = 0.0f;
    new_mat.m_data[13] = 0.0f;
    new_mat.m_data[14] = -1.0f;
    new_mat.m_data[15] = 0.0f;

    return new_mat;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Math::lookAtMat4_f(const Vec3_f& position, const Vec3_f& front, const Vec3_f& right, const Vec3_f& up)
{
    Mat4_f new_mat;

    float front_dot_pos = Math::dotProduct(front, position);
    float right_dot_pos = Math::dotProduct(right, position);
    float up_dot_pos = Math::dotProduct(up, position);

    new_mat.m_data[0]   = right.m_data[0];
    new_mat.m_data[1]   = right.m_data[1];
    new_mat.m_data[2]   = right.m_data[2];
    new_mat.m_data[3]   = -right_dot_pos;

    new_mat.m_data[4]   = up.m_data[0];
    new_mat.m_data[5]   = up.m_data[1];
    new_mat.m_data[6]   = up.m_data[2];
    new_mat.m_data[7]   = -up_dot_pos;

    new_mat.m_data[8]   = -front.m_data[0];
    new_mat.m_data[9]   = -front.m_data[1];
    new_mat.m_data[10]  = -front.m_data[2];
    new_mat.m_data[11]  = front_dot_pos;

    new_mat.m_data[12]  = 0.0f;
    new_mat.m_data[13]  = 0.0f;
    new_mat.m_data[14]  = 0.0f;
    new_mat.m_data[15]  = 1.0f;

    return new_mat;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec3_f Math::add(const Vec3_f& vec_l, const Vec3_f& vec_r)
{
    Vec3_f new_vec;

    new_vec.m_data[0] = vec_l.m_data[0] + vec_r.m_data[0];
    new_vec.m_data[1] = vec_l.m_data[1] + vec_r.m_data[1];
    new_vec.m_data[2] = vec_l.m_data[2] + vec_r.m_data[2];

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
float Math::dotProduct(const Vec2_f& vec_l, const Vec2_f& vec_r)
{
    return
    (
        (vec_l.m_data[0] * vec_r.m_data[0]) +
        (vec_l.m_data[1] * vec_r.m_data[1])
    );
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int Math::dotProduct(const Vec2_i& vec_l, const Vec2_i& vec_r)
{
    return
    (
        (vec_l.m_data[0] * vec_r.m_data[0]) +
        (vec_l.m_data[1] * vec_r.m_data[1])
    );
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
float Math::dotProduct(const Vec3_f& vec_l, const Vec3_f& vec_r)
{
    return
    (
        (vec_l.m_data[0] * vec_r.m_data[0]) +
        (vec_l.m_data[1] * vec_r.m_data[1]) +
        (vec_l.m_data[2] * vec_r.m_data[2])
    );
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
float Math::dotProduct(const Vec4_f& vec_l, const Vec4_f& vec_r)
{
    return
    (
        (vec_l.m_data[0] * vec_r.m_data[0]) +
        (vec_l.m_data[1] * vec_r.m_data[1]) +
        (vec_l.m_data[2] * vec_r.m_data[2]) +
        (vec_l.m_data[3] * vec_r.m_data[3])
    );
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec3_f Math::cross(const Vec3_f& vec_l, const Vec3_f& vec_r)
{
    Vec3_f new_vec;

    new_vec.m_data[0] = (vec_l.m_data[1] * vec_r.m_data[2]) - (vec_l.m_data[2] * vec_r.m_data[1]);
    new_vec.m_data[1] = (vec_l.m_data[2] * vec_r.m_data[0]) - (vec_l.m_data[0] * vec_r.m_data[2]);
    new_vec.m_data[2] = (vec_l.m_data[0] * vec_r.m_data[1]) - (vec_l.m_data[1] * vec_r.m_data[0]);

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Math::multiply(const Mat4_f& mat_l, const Mat4_f& mat_r)
{
    Mat4_f new_mat;

    //---------------------------------------------------------------------------------------------------------------------//
    // 1st row of mat_l multiplied by each column of mat_r.
    //---------------------------------------------------------------------------------------------------------------------//
    new_mat.m_data[0] =
    (
        (mat_l.m_data[0] * mat_r.m_data[0]) +
        (mat_l.m_data[1] * mat_r.m_data[4]) +
        (mat_l.m_data[2] * mat_r.m_data[8]) +
        (mat_l.m_data[3] * mat_r.m_data[12])
    );

    new_mat.m_data[1] =
    (
        (mat_l.m_data[0] * mat_r.m_data[1]) +
        (mat_l.m_data[1] * mat_r.m_data[5]) +
        (mat_l.m_data[2] * mat_r.m_data[9]) +
        (mat_l.m_data[3] * mat_r.m_data[13])
    );

    new_mat.m_data[2] =
    (
        (mat_l.m_data[0] * mat_r.m_data[2]) +
        (mat_l.m_data[1] * mat_r.m_data[6]) +
        (mat_l.m_data[2] * mat_r.m_data[10]) +
        (mat_l.m_data[3] * mat_r.m_data[14])
    );

    new_mat.m_data[3] =
    (
        (mat_l.m_data[0] * mat_r.m_data[3]) +
        (mat_l.m_data[1] * mat_r.m_data[7]) +
        (mat_l.m_data[2] * mat_r.m_data[11]) +
        (mat_l.m_data[3] * mat_r.m_data[15])
    );
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // 2nd row of mat_l multiplied by each column of mat_r.
    //---------------------------------------------------------------------------------------------------------------------//
    new_mat.m_data[4] =
    (
        (mat_l.m_data[4] * mat_r.m_data[0]) +
        (mat_l.m_data[5] * mat_r.m_data[4]) +
        (mat_l.m_data[6] * mat_r.m_data[8]) +
        (mat_l.m_data[7] * mat_r.m_data[12])
    );

    new_mat.m_data[5] =
    (
        (mat_l.m_data[4] * mat_r.m_data[1]) +
        (mat_l.m_data[5] * mat_r.m_data[5]) +
        (mat_l.m_data[6] * mat_r.m_data[9]) +
        (mat_l.m_data[7] * mat_r.m_data[13])
    );

    new_mat.m_data[6] =
    (
        (mat_l.m_data[4] * mat_r.m_data[2]) +
        (mat_l.m_data[5] * mat_r.m_data[6]) +
        (mat_l.m_data[6] * mat_r.m_data[10]) +
        (mat_l.m_data[7] * mat_r.m_data[14])
    );

    new_mat.m_data[7] =
    (
        (mat_l.m_data[4] * mat_r.m_data[3]) +
        (mat_l.m_data[5] * mat_r.m_data[7]) +
        (mat_l.m_data[6] * mat_r.m_data[11]) +
        (mat_l.m_data[7] * mat_r.m_data[15])
    );
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // 3rd row of mat_l multiplied by each column of mat_r.
    //---------------------------------------------------------------------------------------------------------------------//
    new_mat.m_data[8] =
    (
        (mat_l.m_data[8] * mat_r.m_data[0]) +
        (mat_l.m_data[9] * mat_r.m_data[4]) +
        (mat_l.m_data[10] * mat_r.m_data[8]) +
        (mat_l.m_data[11] * mat_r.m_data[12])
    );

    new_mat.m_data[9] =
    (
        (mat_l.m_data[8] * mat_r.m_data[1]) +
        (mat_l.m_data[9] * mat_r.m_data[5]) +
        (mat_l.m_data[10] * mat_r.m_data[9]) +
        (mat_l.m_data[11] * mat_r.m_data[13])
    );

    new_mat.m_data[10] =
    (
        (mat_l.m_data[8] * mat_r.m_data[2]) +
        (mat_l.m_data[9] * mat_r.m_data[6]) +
        (mat_l.m_data[10] * mat_r.m_data[10]) +
        (mat_l.m_data[11] * mat_r.m_data[14])
    );

    new_mat.m_data[11] =
    (
        (mat_l.m_data[8] * mat_r.m_data[3]) +
        (mat_l.m_data[9] * mat_r.m_data[7]) +
        (mat_l.m_data[10] * mat_r.m_data[11]) +
        (mat_l.m_data[11] * mat_r.m_data[15])
    );
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // 4th row of mat_l multiplied by each column of mat_r.
    //---------------------------------------------------------------------------------------------------------------------//
    new_mat.m_data[12] =
    (
        (mat_l.m_data[12] * mat_r.m_data[0]) +
        (mat_l.m_data[13] * mat_r.m_data[4]) +
        (mat_l.m_data[14] * mat_r.m_data[8]) +
        (mat_l.m_data[15] * mat_r.m_data[12])
    );

    new_mat.m_data[13] =
    (
        (mat_l.m_data[12] * mat_r.m_data[1]) +
        (mat_l.m_data[13] * mat_r.m_data[5]) +
        (mat_l.m_data[14] * mat_r.m_data[9]) +
        (mat_l.m_data[15] * mat_r.m_data[13])
    );

    new_mat.m_data[14] =
    (
        (mat_l.m_data[12] * mat_r.m_data[2]) +
        (mat_l.m_data[13] * mat_r.m_data[6]) +
        (mat_l.m_data[14] * mat_r.m_data[10]) +
        (mat_l.m_data[15] * mat_r.m_data[14])
    );

    new_mat.m_data[15] =
    (
        (mat_l.m_data[12] * mat_r.m_data[3]) +
        (mat_l.m_data[13] * mat_r.m_data[7]) +
        (mat_l.m_data[14] * mat_r.m_data[11]) +
        (mat_l.m_data[15] * mat_r.m_data[15])
    );
    //---------------------------------------------------------------------------------------------------------------------//

    return new_mat;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec4_f Math::multiply(const Mat4_f& mat, const Vec4_f& vec)
{
    Vec4_f new_vec;

    new_vec.m_data[0] =
    (
        (mat.m_data[0]  * vec.m_data[0]) +
        (mat.m_data[1]  * vec.m_data[1]) +
        (mat.m_data[2]  * vec.m_data[2]) +
        (mat.m_data[3]  * vec.m_data[3])
    );

    new_vec.m_data[1] =
    (
        (mat.m_data[4]  * vec.m_data[0]) +
        (mat.m_data[5]  * vec.m_data[1]) +
        (mat.m_data[6]  * vec.m_data[2]) +
        (mat.m_data[7]  * vec.m_data[3])
    );

    new_vec.m_data[2] =
    (
        (mat.m_data[8]  * vec.m_data[0]) +
        (mat.m_data[9]  * vec.m_data[1]) +
        (mat.m_data[10] * vec.m_data[2]) +
        (mat.m_data[11] * vec.m_data[3])
    );

    new_vec.m_data[3] =
    (
        (mat.m_data[12] * vec.m_data[0]) +
        (mat.m_data[13] * vec.m_data[1]) +
        (mat.m_data[14] * vec.m_data[2]) +
        (mat.m_data[15] * vec.m_data[3])
    );

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec4_f Math::multiply(const Vec4_f& vec, const Mat4_f& mat)
{
    Vec4_f new_vec;

    new_vec.m_data[0] =
    (
        (vec.m_data[0] * mat.m_data[0]) +
        (vec.m_data[1] * mat.m_data[4]) +
        (vec.m_data[2] * mat.m_data[8]) +
        (vec.m_data[3] * mat.m_data[12])
    );

    new_vec.m_data[1] =
    (
        (vec.m_data[0] * mat.m_data[1]) +
        (vec.m_data[1] * mat.m_data[5]) +
        (vec.m_data[2] * mat.m_data[9]) +
        (vec.m_data[3] * mat.m_data[13])
    );

    new_vec.m_data[2] =
    (
        (vec.m_data[0] * mat.m_data[2]) +
        (vec.m_data[1] * mat.m_data[6]) +
        (vec.m_data[2] * mat.m_data[10]) +
        (vec.m_data[3] * mat.m_data[14])
    );

    new_vec.m_data[3] =
    (
        (vec.m_data[0] * mat.m_data[3]) +
        (vec.m_data[1] * mat.m_data[7]) +
        (vec.m_data[2] * mat.m_data[11]) +
        (vec.m_data[3] * mat.m_data[15])
    );

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec2_f Math::normalise(const Vec2_f& vec)
{
    Vec2_f new_vec;

    float length = sqrtf
    (
        (vec.m_data[0] * vec.m_data[0]) +
        (vec.m_data[1] * vec.m_data[1])
    );

    if(length == 0.0f)
    {
        new_vec.m_data[0] = 0.0f;
        new_vec.m_data[1] = 0.0f;
        return new_vec;
    }

    new_vec.m_data[0] = vec.m_data[0] / length;
    new_vec.m_data[1] = vec.m_data[1] / length;

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec3_f Math::normalise(const Vec3_f& vec)
{
    Vec3_f new_vec;

    float length = sqrtf
    (
        (vec.m_data[0] * vec.m_data[0]) +
        (vec.m_data[1] * vec.m_data[1]) +
        (vec.m_data[2] * vec.m_data[2])
    );

    if(length == 0.0f)
    {
        new_vec.m_data[0] = 0.0f;
        new_vec.m_data[1] = 0.0f;
        new_vec.m_data[2] = 0.0f;
        return new_vec;
    }

    new_vec.m_data[0] = vec.m_data[0] / length;
    new_vec.m_data[1] = vec.m_data[1] / length;
    new_vec.m_data[2] = vec.m_data[2] / length;
    
    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec4_f Math::normalise(const Vec4_f& vec)
{
    Vec4_f new_vec;

    float length = sqrtf
    (
        (vec.m_data[0] * vec.m_data[0]) +
        (vec.m_data[1] * vec.m_data[1]) +
        (vec.m_data[2] * vec.m_data[2]) +
        (vec.m_data[3] * vec.m_data[3])
    );

    if(length == 0.0f)
    {
        new_vec.m_data[0] = 0.0f;
        new_vec.m_data[1] = 0.0f;
        new_vec.m_data[2] = 0.0f;
        new_vec.m_data[3] = 0.0f;
        return new_vec;
    }

    new_vec.m_data[0] = vec.m_data[0] / length;
    new_vec.m_data[1] = vec.m_data[1] / length;
    new_vec.m_data[2] = vec.m_data[2] / length;
    new_vec.m_data[3] = vec.m_data[3] / length;
    
    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Math::scalarMultiply(const Mat4_f& mat, const float scalar)
{
    Mat4_f new_mat;

    new_mat.m_data[0]  = mat.m_data[0]  * scalar;
    new_mat.m_data[1]  = mat.m_data[1]  * scalar;
    new_mat.m_data[2]  = mat.m_data[2]  * scalar;
    new_mat.m_data[3]  = mat.m_data[3]  * scalar;
    
    new_mat.m_data[4]  = mat.m_data[4]  * scalar;
    new_mat.m_data[5]  = mat.m_data[5]  * scalar;
    new_mat.m_data[6]  = mat.m_data[6]  * scalar;
    new_mat.m_data[7]  = mat.m_data[7]  * scalar;

    new_mat.m_data[8]  = mat.m_data[8]  * scalar;
    new_mat.m_data[9]  = mat.m_data[9]  * scalar;
    new_mat.m_data[10] = mat.m_data[10] * scalar;
    new_mat.m_data[11] = mat.m_data[11] * scalar;

    new_mat.m_data[12] = mat.m_data[12] * scalar;
    new_mat.m_data[13] = mat.m_data[13] * scalar;
    new_mat.m_data[14] = mat.m_data[14] * scalar;
    new_mat.m_data[15] = mat.m_data[15] * scalar;

    return new_mat;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec2_f Math::scalarMultiply(const Vec2_f& vec, const float scalar)
{
    Vec2_f new_vec;

    new_vec.m_data[0] = vec.m_data[0] * scalar;
    new_vec.m_data[1] = vec.m_data[1] * scalar;

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec2_i Math::scalarMultiply(const Vec2_i& vec, const int scalar)
{
    Vec2_i new_vec;

    new_vec.m_data[0] = vec.m_data[0] * scalar;
    new_vec.m_data[1] = vec.m_data[1] * scalar;

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec3_f Math::scalarMultiply(const Vec3_f& vec, const float scalar)
{
    Vec3_f new_vec;

    new_vec.m_data[0] = vec.m_data[0] * scalar;
    new_vec.m_data[1] = vec.m_data[1] * scalar;
    new_vec.m_data[2] = vec.m_data[2] * scalar;

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec4_f Math::scalarMultiply(const Vec4_f& vec, const float scalar)
{
    Vec4_f new_vec;

    new_vec.m_data[0] = vec.m_data[0] * scalar;
    new_vec.m_data[1] = vec.m_data[1] * scalar;
    new_vec.m_data[2] = vec.m_data[2] * scalar;
    new_vec.m_data[3] = vec.m_data[3] * scalar;

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Vec3_f Math::subtract(const Vec3_f& vec_l, const Vec3_f& vec_r)
{
    Vec3_f new_vec;

    new_vec.m_data[0] = vec_l.m_data[0] - vec_r.m_data[0];
    new_vec.m_data[1] = vec_l.m_data[1] - vec_r.m_data[1];
    new_vec.m_data[2] = vec_l.m_data[2] - vec_r.m_data[2];

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vec4_f clip = {x, y, z, w};
*/
Vec3_f Math::clipCoordsToNormalisedDeviceCoords(const Vec4_f& clip_coords)
{
    Vec3_f new_vec;

    new_vec.m_data[0] = clip_coords.m_data[0] / clip_coords.m_data[3];
    new_vec.m_data[1] = clip_coords.m_data[1] / clip_coords.m_data[3];
    new_vec.m_data[2] = clip_coords.m_data[2] / clip_coords.m_data[3];

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
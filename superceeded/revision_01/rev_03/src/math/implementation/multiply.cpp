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
#include "../math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Mat4_f Math::multiply(const Mat4_f& mat_l, const Mat4_f& mat_r)
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
Math::Vec4_f Math::multiply(const Mat4_f& mat_l, const Vec4_f& vec_r)
{
    Vec4_f new_vec;

    new_vec.m_data[0] =
    (
        (mat_l.m_data[0]  * vec_r.m_data[0]) +
        (mat_l.m_data[1]  * vec_r.m_data[1]) +
        (mat_l.m_data[2]  * vec_r.m_data[2]) +
        (mat_l.m_data[3]  * vec_r.m_data[3])
    );

    new_vec.m_data[1] =
    (
        (mat_l.m_data[4]  * vec_r.m_data[0]) +
        (mat_l.m_data[5]  * vec_r.m_data[1]) +
        (mat_l.m_data[6]  * vec_r.m_data[2]) +
        (mat_l.m_data[7]  * vec_r.m_data[3])
    );

    new_vec.m_data[2] =
    (
        (mat_l.m_data[8]  * vec_r.m_data[0]) +
        (mat_l.m_data[9]  * vec_r.m_data[1]) +
        (mat_l.m_data[10] * vec_r.m_data[2]) +
        (mat_l.m_data[11] * vec_r.m_data[3])
    );

    new_vec.m_data[3] =
    (
        (mat_l.m_data[12] * vec_r.m_data[0]) +
        (mat_l.m_data[13] * vec_r.m_data[1]) +
        (mat_l.m_data[14] * vec_r.m_data[2]) +
        (mat_l.m_data[15] * vec_r.m_data[3])
    );

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Vec4_f Math::multiply(const Vec4_f& vec_l, const Mat4_f& mat_r)
{
    Vec4_f new_vec;

    new_vec.m_data[0] =
    (
        (vec_l.m_data[0] * mat_r.m_data[0]) +
        (vec_l.m_data[1] * mat_r.m_data[4]) +
        (vec_l.m_data[2] * mat_r.m_data[8]) +
        (vec_l.m_data[3] * mat_r.m_data[12])
    );

    new_vec.m_data[1] =
    (
        (vec_l.m_data[0] * mat_r.m_data[1]) +
        (vec_l.m_data[1] * mat_r.m_data[5]) +
        (vec_l.m_data[2] * mat_r.m_data[9]) +
        (vec_l.m_data[3] * mat_r.m_data[13])
    );

    new_vec.m_data[2] =
    (
        (vec_l.m_data[0] * mat_r.m_data[2]) +
        (vec_l.m_data[1] * mat_r.m_data[6]) +
        (vec_l.m_data[2] * mat_r.m_data[10]) +
        (vec_l.m_data[3] * mat_r.m_data[14])
    );

    new_vec.m_data[3] =
    (
        (vec_l.m_data[0] * mat_r.m_data[3]) +
        (vec_l.m_data[1] * mat_r.m_data[7]) +
        (vec_l.m_data[2] * mat_r.m_data[11]) +
        (vec_l.m_data[3] * mat_r.m_data[15])
    );

    return new_vec;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
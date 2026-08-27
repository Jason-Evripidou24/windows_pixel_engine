// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef MAT4_F_HPP
#define MAT4_F_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "vec4_f.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Math
{
    namespace Core
    {
        struct Mat4_f
        {
            //-------------------------------------------------------------------------------------------------------------//
            static constexpr size_t m_data_size = 16;
            float m_data[m_data_size];
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Standard constructor.
            //-------------------------------------------------------------------------------------------------------------//
            Mat4_f()
            {
                for(size_t i = 0; i < m_data_size; i++)
                {
                    m_data[i] = 0.0f;
                }
            }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Copy and Move constructors.
            //-------------------------------------------------------------------------------------------------------------//
            Mat4_f(const Mat4_f& other)
            {
                for(size_t i = 0; i < m_data_size; i++)
                {
                    m_data[i] = other.m_data[i];
                }
            }

            Mat4_f& operator=(const Mat4_f& other)
            {
                if(this != &other)
                {
                    for(size_t i = 0; i < m_data_size; i++)
                    {
                        m_data[i] = other.m_data[i];
                    }
                }
                return *this;
            }

            Mat4_f(Mat4_f&& other) noexcept
            {
                for(size_t i = 0; i < m_data_size; i++)
                {
                    m_data[i] = other.m_data[i];
                }
            }

            Mat4_f& operator=(Mat4_f&& other) noexcept
            {
                if(this != &other)
                {
                    for(size_t i = 0; i < m_data_size; i++)
                    {
                        m_data[i] = other.m_data[i];
                    }
                }
                return *this;
            }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Comparison operator overloads.
            //-------------------------------------------------------------------------------------------------------------//
            bool operator==(const Mat4_f& other) const
            {
                for(size_t i = 0; i < m_data_size; i++)
                {
                    if( std::abs(m_data[i] - other.m_data[i]) > 0.0001f )
                    {
                        return false;
                    }
                }
                return true;
            }

            bool operator!=(const Mat4_f& other) const
            {
                for(size_t i = 0; i < m_data_size; i++)
                {
                    if( std::abs(m_data[i] - other.m_data[i]) > 0.0001f )
                    {
                        return true;
                    }
                }
                return false;
            }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Arithmetic operator overloads.
            //-------------------------------------------------------------------------------------------------------------//
            Mat4_f operator+(const Mat4_f& rhs) const
            {
                Mat4_f new_mat;

                for(size_t i = 0; i < m_data_size; i++)
                {
                    new_mat.m_data[i] = m_data[i] + rhs.m_data[i];
                }

                return new_mat;
            }

            Mat4_f operator-(const Mat4_f& rhs) const
            {
                Mat4_f new_mat;

                for(size_t i = 0; i < m_data_size; i++)
                {
                    new_mat.m_data[i] = m_data[i] - rhs.m_data[i];
                }

                return new_mat;
            }

            Mat4_f operator*(const float scalar) const
            {
                Mat4_f new_mat;

                for(size_t i = 0; i < m_data_size; i++)
                {
                    new_mat.m_data[i] = m_data[i] * scalar;
                }

                return new_mat;
            }

            // ROW MAJOR MULTIPLICATION
            Mat4_f operator*(const Mat4_f& rhs) const
            {
                Mat4_f new_mat;

                for(size_t row = 0; row < 4; row++)
                {
                    for(size_t col = 0; col < 4; col++)
                    {
                        float value = 0.0f;

                        for(size_t i = 0; i < 4; i++)
                        {
                            value += m_data[(row * 4) + i] * rhs.m_data[(i * 4) + col];
                        }

                        new_mat.m_data[(row * 4) + col] = value;
                    }
                }

                return new_mat;
            }

            Math::Core::Vec4_f operator*(const Math::Core::Vec4_f& rhs) const
            {
                Math::Core::Vec4_f new_vec;

                for(size_t row = 0; row < 4; row++)
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
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Single-Object Operations.
            //-------------------------------------------------------------------------------------------------------------//
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

            // Rotation matrix constructed from euler angles.
            inline void rotation(const float axis_x, const float axis_y, const float axis_z, const float theta_rad)
            {
                //---------------------------------------------------------------------------------------------------------//
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
                //---------------------------------------------------------------------------------------------------------//

                //---------------------------------------------------------------------------------------------------------//
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
                //---------------------------------------------------------------------------------------------------------//
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
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Visulisation.
            //-------------------------------------------------------------------------------------------------------------//
            std::string toString(int min_num_width, int num_decimals) const
            {
                std::ostringstream ss;

                ss << std::fixed << std::setprecision(num_decimals);

                ss << "["
                << std::setw(min_num_width) << m_data[0] << ", "
                << std::setw(min_num_width) << m_data[1] << ", "
                << std::setw(min_num_width) << m_data[2] << ", "
                << std::setw(min_num_width) << m_data[3] << "]\n"

                << "["
                << std::setw(min_num_width) << m_data[4] << ", "
                << std::setw(min_num_width) << m_data[5] << ", "
                << std::setw(min_num_width) << m_data[6] << ", "
                << std::setw(min_num_width) << m_data[7] << "]\n"

                << "["
                << std::setw(min_num_width) << m_data[8] << ", "
                << std::setw(min_num_width) << m_data[9] << ", "
                << std::setw(min_num_width) << m_data[10] << ", "
                << std::setw(min_num_width) << m_data[11] << "]\n"

                << "["
                << std::setw(min_num_width) << m_data[12] << ", "
                << std::setw(min_num_width) << m_data[13] << ", "
                << std::setw(min_num_width) << m_data[14] << ", "
                << std::setw(min_num_width) << m_data[15] << "]";

                return ss.str();
            }
            //-------------------------------------------------------------------------------------------------------------//
        };
    };
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
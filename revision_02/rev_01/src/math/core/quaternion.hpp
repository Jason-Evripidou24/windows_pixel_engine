// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef QUATERNION_HPP
#define QUATERNION_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   NOTE: Maths in this program is done ROW MAJOR!!
    -   Since we are not using opengl and rendering by our own methods this is easier for us to visualiase mathematically.
*/
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


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
#include "mat4_f.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Math
{
    namespace Core
    {
        struct Quaternion
        {
            // q = xi + yj + zk + w where w is the scalar component.
            float m_x;
            float m_y;
            float m_z;
            float m_w;

            //-------------------------------------------------------------------------------------------------------------//
            // Standard constructor.
            //-------------------------------------------------------------------------------------------------------------//
            Quaternion()
            {
                m_x = 0.0f;
                m_y = 0.0f;
                m_z = 0.0f;
                m_w = 1.0f;
            }
            Quaternion(float x, float y, float z, float w)
            {
                m_x = x;
                m_y = y;
                m_z = z;
                m_w = w;
            }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Copy and Move constructors.
            //-------------------------------------------------------------------------------------------------------------//
            Quaternion(const Quaternion& other)
            {
                m_x = other.m_x;
                m_y = other.m_y;
                m_z = other.m_z;
                m_w = other.m_w;
            }

            Quaternion& operator=(const Quaternion& other)
            {
                if(this != &other)
                {
                    m_x = other.m_x;
                    m_y = other.m_y;
                    m_z = other.m_z;
                    m_w = other.m_w;
                }
                return *this;
            }

            Quaternion(Quaternion&& other) noexcept
            {
                m_x = other.m_x;
                m_y = other.m_y;
                m_z = other.m_z;
                m_w = other.m_w;
            }

            Quaternion& operator=(Quaternion&& other) noexcept
            {
                if(this != &other)
                {
                    m_x = other.m_x;
                    m_y = other.m_y;
                    m_z = other.m_z;
                    m_w = other.m_w;
                }
                return *this;
            }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Comparison operator overloads.
            //-------------------------------------------------------------------------------------------------------------//
            bool operator==(const Quaternion& other) const
            {
                if
                (
                    ( std::abs(m_x - other.m_x) > 0.0001f ) ||
                    ( std::abs(m_y - other.m_y) > 0.0001f ) ||
                    ( std::abs(m_z - other.m_z) > 0.0001f ) ||
                    ( std::abs(m_w - other.m_w) > 0.0001f )
                )
                {
                    return false;
                }
                return true;
            }

            bool operator!=(const Quaternion& other) const
            {
                if
                (
                    ( std::abs(m_x - other.m_x) > 0.0001f ) ||
                    ( std::abs(m_y - other.m_y) > 0.0001f ) ||
                    ( std::abs(m_z - other.m_z) > 0.0001f ) ||
                    ( std::abs(m_w - other.m_w) > 0.0001f )
                )
                {
                    return true;
                }
                return false;
            }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            // Arithmetic operator overloads.
            //-------------------------------------------------------------------------------------------------------------//
            Quaternion operator+(const Quaternion& rhs) const
            {
                Quaternion result;
                result.m_x = m_x + rhs.m_x;
                result.m_y = m_y + rhs.m_y;
                result.m_z = m_z + rhs.m_z;
                result.m_w = m_w + rhs.m_w;
                return result;
            }

            Quaternion operator-(const Quaternion& rhs) const
            {
                Quaternion result;
                result.m_x = m_x - rhs.m_x;
                result.m_y = m_y - rhs.m_y;
                result.m_z = m_z - rhs.m_z;
                result.m_w = m_w - rhs.m_w;
                return result;
            }

            Quaternion operator*(const float scalar) const
            {
                Quaternion result;
                result.m_x = m_x * scalar;
                result.m_y = m_y * scalar;
                result.m_z = m_z * scalar;
                result.m_w = m_w * scalar;
                return result;
            }

            Quaternion operator*(const Quaternion& rhs) const
            {
                Quaternion result;
                result.m_x = (m_w * rhs.m_x) + (m_x * rhs.m_w) + (m_y * rhs.m_z) - (m_z * rhs.m_y);
                result.m_y = (m_w * rhs.m_y) - (m_x * rhs.m_z) + (m_y * rhs.m_w) + (m_z * rhs.m_x);
                result.m_z = (m_w * rhs.m_z) + (m_x * rhs.m_y) - (m_y * rhs.m_x) + (m_z * rhs.m_w);
                result.m_w = (m_w * rhs.m_w) - (m_x * rhs.m_x) - (m_y * rhs.m_y) - (m_z * rhs.m_z);
                return result;
            }

            Quaternion operator/(const float scalar) const
            {
                Quaternion result;
                result.m_x = m_x / scalar;
                result.m_y = m_y / scalar;
                result.m_z = m_z / scalar;
                result.m_w = m_w / scalar;
                return result;
            }
            //-------------------------------------------------------------------------------------------------------------//

            inline Quaternion conjugate() const
            {
                Quaternion result;
                result.m_x = -m_x;
                result.m_y = -m_y;
                result.m_z = -m_z;
                result.m_w =  m_w;
                return result;
            }

            inline float length() const
            {
                const float length = sqrtf( (m_x * m_x) + (m_y * m_y) + (m_z * m_z) + (m_w * m_w) );
                return length;
            }

            inline void normalise()
            {
                const float length = sqrtf( (m_x * m_x) + (m_y * m_y) + (m_z * m_z) + (m_w * m_w) );
                if(length <= 0.0f)
                {
                    m_x = 0.0f;
                    m_y = 0.0f;
                    m_z = 0.0f;
                    m_w = 1.0f;
                    return;
                }

                const float inv_length = 1.0f / length;
                m_x *= inv_length;
                m_y *= inv_length;
                m_z *= inv_length;
                m_w *= inv_length;
            }

            inline static Quaternion fromAxisAngle(float x_axis, float y_axis, float z_axis, float angle)
            {
                const float half_angle = angle * 0.5f;
                const float s = sinf(half_angle);
                const float c = cosf(half_angle);

                const float length_squared = (x_axis * x_axis) + (y_axis * y_axis) + (z_axis * z_axis);
                if(length_squared <= 0.0f)
                {
                    return Quaternion();
                }

                const float inv_len = 1.0f / sqrtf(length_squared);

                return Quaternion(x_axis * s * inv_len, y_axis * s * inv_len, z_axis * s * inv_len, c);
            }

            // Rotation matrix constructed from quaternion.
            inline Math::Core::Mat4_f toRotationMatrix() const
            {
                Mat4_f result;

                const float xx = m_x * m_x;
                const float yy = m_y * m_y;
                const float zz = m_z * m_z;

                const float xy = m_x * m_y;
                const float xz = m_x * m_z;
                const float yz = m_y * m_z;

                const float wx = m_w * m_x;
                const float wy = m_w * m_y;
                const float wz = m_w * m_z;

                result.m_data[0]  = 1.0f - (2.0f * yy) - (2.0f * zz);
                result.m_data[1]  = (2.0f * xy) - (2.0f * wz);
                result.m_data[2]  = (2.0f * xz) + (2.0f * wy);
                result.m_data[3]  = 0.0f;

                result.m_data[4]  = (2.0f * xy) + (2.0f * wz);
                result.m_data[5]  = 1.0f - (2.0f * xx) - (2.0f * zz);
                result.m_data[6]  = (2.0f * yz) - (2.0f * wx);
                result.m_data[7]  = 0.0f;

                result.m_data[8]  = (2.0f * xz) - (2.0f * wy);
                result.m_data[9]  = (2.0f * yz) + (2.0f * wx);
                result.m_data[10] = 1.0f - (2.0f * xx) - (2.0f * yy);
                result.m_data[11] = 0.0f;

                result.m_data[12] = 0.0f;
                result.m_data[13] = 0.0f;
                result.m_data[14] = 0.0f;
                result.m_data[15] = 1.0f;

                return result;
            }
        };
    };
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
#include "../../utils/utils.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Math
{
    namespace Core
    {
        struct Quaternion
        {
            // q = xi + yj + zk + w
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
                    (Utils::checkFloatEquals(m_x, other.m_x) == false) ||
                    (Utils::checkFloatEquals(m_y, other.m_y) == false) ||
                    (Utils::checkFloatEquals(m_z, other.m_z) == false) ||
                    (Utils::checkFloatEquals(m_w, other.m_w) == false)
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
                    (Utils::checkFloatEquals(m_x, other.m_x) == false) ||
                    (Utils::checkFloatEquals(m_y, other.m_y) == false) ||
                    (Utils::checkFloatEquals(m_z, other.m_z) == false) ||
                    (Utils::checkFloatEquals(m_w, other.m_w) == false)
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

            inline Quaternion fromEuler(float x_axis, float y_axis, float z_axis) const
            {
                const float x = x_axis * 0.5f;
                const float y = y_axis * 0.5f;
                const float z = z_axis * 0.5f;

                const float cx = cosf(x);
                const float sx = sinf(x);
                const float cy = cosf(y);
                const float sy = sinf(y);
                const float cz = cosf(z);
                const float sz = sinf(z);

                Quaternion result;
                result.m_x = (sx * cy * cz) - (cx * sy * sz);
                result.m_y = (cx * sy * cz) + (sx * cy * sz);
                result.m_z = (cx * cy * sz) - (sx * sy * cz);
                result.m_w = (cx * cy * cz) + (sx * sy * sz);
                return result;
            }

            inline Quaternion fromAxisAngle(float x_axis, float y_axis, float z_axis, float angle) const
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
        };
    };
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
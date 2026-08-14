// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef MATH_CORE_HPP
#define MATH_CORE_HPP
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
#include <cstdint>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "mat4_f.hpp"
#include "vec2_f.hpp"
#include "vec3_f.hpp"
#include "vec4_f.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Math
{
    namespace Core
    {
        //-----------------------------------------------------------------------------------------------------------------//
        static const float  PI_f                 = 3.14159265358979323846f;
        static const double PI_d                 = 3.14159265358979323846;

        static const float  TWO_PI_f             = 2.0f * 3.14159265358979323846f;
        static const double TWO_PI_d             = 2.0 * 3.14159265358979323846;

        static const float  DEGREES_PER_RADIAN_f = 180.0f / PI_f;
        static const double DEGREES_PER_RADIAN_d = 180.0  / PI_d;
        static const float  RADIANS_PER_DEGREE_f = PI_f   / 180.0f;
        static const double RADIANS_PER_DEGREE_d = PI_d   / 180.0;
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Dot product.
        //-----------------------------------------------------------------------------------------------------------------//
        inline float dotProduct(const Math::Core::Vec2_f& vec_l, const Math::Core::Vec2_f& vec_r)
        {
            float dot_product = 0.0f;
            for(size_t i = 0; i < vec_l.m_data_size; i++)
            {
                dot_product += vec_l.m_data[i] * vec_r.m_data[i];
            }
            return dot_product;
        }

        inline float dotProduct(const Math::Core::Vec3_f& vec_l, const Math::Core::Vec3_f& vec_r)
        {
            float dot_product = 0.0f;
            for(size_t i = 0; i < vec_l.m_data_size; i++)
            {
                dot_product += vec_l.m_data[i] * vec_r.m_data[i];
            }
            return dot_product;
        }

        inline float dotProduct(const Math::Core::Vec4_f& vec_l, const Math::Core::Vec4_f& vec_r)
        {
            float dot_product = 0.0f;
            for(size_t i = 0; i < vec_l.m_data_size; i++)
            {
                dot_product += vec_l.m_data[i] * vec_r.m_data[i];
            }
            return dot_product;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Cross product.
        //-----------------------------------------------------------------------------------------------------------------//
        inline void crossProduct
        (
            Math::Core::Vec3_f& output,
            const Math::Core::Vec3_f& vec_l,
            const Math::Core::Vec3_f& vec_r
        )
        {
            output.m_data[0] = (vec_l.m_data[1] * vec_r.m_data[2]) - (vec_l.m_data[2] * vec_r.m_data[1]);
            output.m_data[1] = (vec_l.m_data[2] * vec_r.m_data[0]) - (vec_l.m_data[0] * vec_r.m_data[2]);
            output.m_data[2] = (vec_l.m_data[0] * vec_r.m_data[1]) - (vec_l.m_data[1] * vec_r.m_data[0]);
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Interpolations.
        //-----------------------------------------------------------------------------------------------------------------//
        inline float interpolateFloat(const float start, const float end, float t)
        {
            if(t <= 0.0f) { t = 0.0f; }
            if(t >= 1.0f) { t = 1.0f; }

            return (start * (1.0f - t)) + (end * t);
        }

        inline void interpolateVec2f
        (
            Math::Core::Vec2_f& output,
            const Math::Core::Vec2_f& start,
            const Math::Core::Vec2_f& end,
            float t
        )
        {
            if(t <= 0.0f) { t = 0.0f; }
            if(t >= 1.0f) { t = 1.0f; }

            for(int i = 0; i < start.m_data_size; i++)
            {
                output.m_data[i] = Math::Core::interpolateFloat(start.m_data[i], end.m_data[i], t);
            }
        }

        inline void interpolateVec3f
        (
            Math::Core::Vec3_f& output,
            const Math::Core::Vec3_f& start,
            const Math::Core::Vec3_f& end,
            float t
        )
        {
            if(t <= 0.0f) { t = 0.0f; }
            if(t >= 1.0f) { t = 1.0f; }

            for(int i = 0; i < start.m_data_size; i++)
            {
                output.m_data[i] = Math::Core::interpolateFloat(start.m_data[i], end.m_data[i], t);
            }
        }

        inline void interpolateVec4f
        (
            Math::Core::Vec4_f& output,
            const Math::Core::Vec4_f& start,
            const Math::Core::Vec4_f& end,
            float t
        )
        {
            if(t <= 0.0f) { t = 0.0f; }
            if(t >= 1.0f) { t = 1.0f; }

            for(int i = 0; i < start.m_data_size; i++)
            {
                output.m_data[i] = Math::Core::interpolateFloat(start.m_data[i], end.m_data[i], t);
            }
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Misc.
        //-----------------------------------------------------------------------------------------------------------------//
        inline uint32_t mixUint32(uint32_t color_a, float alpha, uint32_t color_b, float beta, uint32_t color_c, float gamma)
        {
            float a0 = static_cast<float>((color_a >> 0) & 0xFF);
            float a1 = static_cast<float>((color_a >> 8) & 0xFF);
            float a2 = static_cast<float>((color_a >> 16) & 0xFF);
            float a3 = static_cast<float>((color_a >> 24) & 0xFF);

            float b0 = static_cast<float>((color_b >> 0) & 0xFF);
            float b1 = static_cast<float>((color_b >> 8) & 0xFF);
            float b2 = static_cast<float>((color_b >> 16) & 0xFF);
            float b3 = static_cast<float>((color_b >> 24) & 0xFF);

            float c0 = static_cast<float>((color_c >> 0) & 0xFF);
            float c1 = static_cast<float>((color_c >> 8) & 0xFF);
            float c2 = static_cast<float>((color_c >> 16) & 0xFF);
            float c3 = static_cast<float>((color_c >> 24) & 0xFF);

            uint8_t mix0 = static_cast<uint8_t>( (a0 * alpha) + (b0 * beta) + (c0 * gamma) );
            uint8_t mix1 = static_cast<uint8_t>( (a1 * alpha) + (b1 * beta) + (c1 * gamma) );
            uint8_t mix2 = static_cast<uint8_t>( (a2 * alpha) + (b2 * beta) + (c2 * gamma) );
            uint8_t mix3 = static_cast<uint8_t>( (a3 * alpha) + (b3 * beta) + (c3 * gamma) );

            uint32_t result =
                (static_cast<uint32_t>(mix0) << 0)  |
                (static_cast<uint32_t>(mix1) << 8)  |
                (static_cast<uint32_t>(mix2) << 16) |
                (static_cast<uint32_t>(mix3) << 24);

            return result;
        }

        inline float convertDegreesToRadians(const float degrees)
        {
            return degrees * Math::Core::RADIANS_PER_DEGREE_f;
        }

        inline uint32_t convertVec4fToColor(const Math::Core::Vec3_f& color)
        {
            uint32_t a = 0xFF;
            uint32_t r = static_cast<uint32_t>(color.m_data[0] * 255.0f);
            uint32_t g = static_cast<uint32_t>(color.m_data[1] * 255.0f);
            uint32_t b = static_cast<uint32_t>(color.m_data[2] * 255.0f);

            return (a << 24) | (r << 16) | (g << 8) | (b << 0);
        }

        inline uint32_t convertVec4fToColor(const Math::Core::Vec4_f& color)
        {
            uint32_t a = static_cast<uint32_t>(color.m_data[0] * 255.0f);
            uint32_t r = static_cast<uint32_t>(color.m_data[1] * 255.0f);
            uint32_t g = static_cast<uint32_t>(color.m_data[2] * 255.0f);
            uint32_t b = static_cast<uint32_t>(color.m_data[3] * 255.0f);

            return (a << 24) | (r << 16) | (g << 8) | (b << 0);
        }
        //-----------------------------------------------------------------------------------------------------------------//
    };
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
#include "../renderer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
*/

// An edge function (used in fillTriangle for Edge-function rasterization) tells us which side of a line a point lies on.
float edge(float ax, float ay, float bx, float by,float px, float py)
{
    return (px - ax) * (by - ay) - (py - ay) * (bx - ax);
}

uint32_t mixColor(uint32_t color_a, float alpha, uint32_t color_b, float beta, uint32_t color_c, float gamma)
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

void TileRenderer::fillTriangle(const Math::Triangle& triangle, const Material& material)
{
    //-----------------------------------------------------------------------------------------------------------------//
    // Material colors that do not depend on texture coords.
    //-----------------------------------------------------------------------------------------------------------------//
    uint32_t material_diffuse_color = Math::convertVec3fToColor(material.m_diffuse);
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    const Math::Vertex& v0 = triangle.m_v0;
    int v0_x = m_backbuffer->toBackbufferCoordX(v0.m_position.m_data[0]);
    int v0_y = m_backbuffer->toBackbufferCoordY(v0.m_position.m_data[1]);
    float v0_z = v0.m_position.m_data[2];
    uint32_t v0_color = v0.m_color;

    const Math::Vertex& v1 = triangle.m_v1;
    int v1_x = m_backbuffer->toBackbufferCoordX(v1.m_position.m_data[0]);
    int v1_y = m_backbuffer->toBackbufferCoordY(v1.m_position.m_data[1]);
    float v1_z = v1.m_position.m_data[2];
    uint32_t v1_color = v1.m_color;

    const Math::Vertex& v2 = triangle.m_v2;
    int v2_x = m_backbuffer->toBackbufferCoordX(v2.m_position.m_data[0]);
    int v2_y = m_backbuffer->toBackbufferCoordY(v2.m_position.m_data[1]);
    float v2_z = v2.m_position.m_data[2];
    uint32_t v2_color = v2.m_color;

    float area = edge((float)v0_x, (float)v0_y, (float)v1_x, (float)v1_y, (float)v2_x, (float)v2_y);
    if(Utils::checkFloatEquals(area, 0.0f)) { return; }
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Bounding box.
    //-----------------------------------------------------------------------------------------------------------------//
    int min_x = v0_x;
    if(v1_x < min_x) { min_x = v1_x; }
    if(v2_x < min_x) { min_x = v2_x; }
    if(min_x < 0) { min_x = 0; }

    int max_x = v0_x;
    if(v1_x > max_x) { max_x = v1_x; }
    if(v2_x > max_x) { max_x = v2_x; }
    if(max_x >= m_backbuffer->m_width) { max_x = m_backbuffer->m_width - 1; }

    int min_y = v0_y;
    if(v1_y < min_y) { min_y = v1_y; }
    if(v2_y < min_y) { min_y = v2_y; }
    if(min_y < 0) { min_y = 0; }

    int max_y = v0_y;
    if(v1_y > max_y) { max_y = v1_y; }
    if(v2_y > max_y) { max_y = v2_y; }
    if(max_y >= m_backbuffer->m_height) { max_y = m_backbuffer->m_height - 1; }
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Rasterize all pixels inside the bounding box.
    //-----------------------------------------------------------------------------------------------------------------//
    for(int y = min_y; y <= max_y; y++)
    {
        for(int x = min_x; x <= max_x; x++)
        {
            // Compute barycentric edge values.
            float w0 = edge((float)v1_x, (float)v1_y, (float)v2_x, (float)v2_y, (float)x, (float)y);
            float w1 = edge((float)v2_x, (float)v2_y, (float)v0_x, (float)v0_y, (float)x, (float)y);
            float w2 = edge((float)v0_x, (float)v0_y, (float)v1_x, (float)v1_y, (float)x, (float)y);

            // Accept either winding order.
            bool all_non_negative = ( (w0 >= 0.0f) && (w1 >= 0.0f) && (w2 >= 0.0f) );
            bool all_non_positive = ( (w0 <= 0.0f) && (w1 <= 0.0f) && (w2 <= 0.0f) );
            if(!(all_non_negative || all_non_positive)) { continue; }

            // Compute barycentric coordinates.
            float alpha = w0 / area;
            float beta  = w1 / area;
            float gamma = w2 / area;

            // Interpolate depth and color.
            float z = (alpha * v0_z) + (beta * v1_z) + (gamma * v2_z);
            uint32_t color = mixColor(v0_color, alpha, v1_color, beta, v2_color, gamma);

            uint32_t output_color = Math::interpolateUint32(color, material_diffuse_color, 0.5f);

            m_backbuffer->setPixel(x, y, z, output_color);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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

/*
-   color_mix is 0.0f <= color_mix <= 1.0f where 0 is 100% color from triangle vertex colors and 1 is 100% color from
    material.
*/
void Renderer::fillTriangle(const Math::Triangle& triangle, const Material& material, float color_mix)
{
    const Math::Vertex& v0 = triangle.m_v0;
    const Math::Vertex& v1 = triangle.m_v1;
    const Math::Vertex& v2 = triangle.m_v2;

    //-----------------------------------------------------------------------------------------------------------------//
    // Screen coordinates.
    //-----------------------------------------------------------------------------------------------------------------//
    int v0_x = m_backbuffer->toBackbufferCoordX(v0.m_position.m_data[0]);
    int v0_y = m_backbuffer->toBackbufferCoordY(v0.m_position.m_data[1]);

    int v1_x = m_backbuffer->toBackbufferCoordX(v1.m_position.m_data[0]);
    int v1_y = m_backbuffer->toBackbufferCoordY(v1.m_position.m_data[1]);

    int v2_x = m_backbuffer->toBackbufferCoordX(v2.m_position.m_data[0]);
    int v2_y = m_backbuffer->toBackbufferCoordY(v2.m_position.m_data[1]);
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Depth.
    //-----------------------------------------------------------------------------------------------------------------//
    float v0_z = v0.m_position.m_data[2];
    float v1_z = v1.m_position.m_data[2];
    float v2_z = v2.m_position.m_data[2];
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Colors.
    //-----------------------------------------------------------------------------------------------------------------//
    uint32_t v0_color = Math::convertVec4fToColor(v0.m_color);
    uint32_t v1_color = Math::convertVec4fToColor(v1.m_color);
    uint32_t v2_color = Math::convertVec4fToColor(v2.m_color);

    uint32_t material_diffuse_color = Math::convertVec3fToColor(material.m_diffuse);
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Perspective interpolation values.
    //-----------------------------------------------------------------------------------------------------------------//
    float v0_inv_w = 1.0f / v0.m_position.m_data[3];
    float v1_inv_w = 1.0f / v1.m_position.m_data[3];
    float v2_inv_w = 1.0f / v2.m_position.m_data[3];

    float v0_u_over_w = v0.m_tex_coords.m_data[0] * v0_inv_w;
    float v1_u_over_w = v1.m_tex_coords.m_data[0] * v1_inv_w;
    float v2_u_over_w = v2.m_tex_coords.m_data[0] * v2_inv_w;

    float v0_v_over_w = v0.m_tex_coords.m_data[1] * v0_inv_w;
    float v1_v_over_w = v1.m_tex_coords.m_data[1] * v1_inv_w;
    float v2_v_over_w = v2.m_tex_coords.m_data[1] * v2_inv_w;
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Triangle area.
    //-----------------------------------------------------------------------------------------------------------------//
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

            float z = (alpha * v0_z) + (beta * v1_z) + (gamma * v2_z);

            float inv_w = (alpha * v0_inv_w) + (beta * v1_inv_w) + (gamma * v2_inv_w);

            float u_over_w = (alpha * v0_u_over_w) + (beta * v1_u_over_w) + (gamma * v2_u_over_w);
            float v_over_w = (alpha * v0_v_over_w) + (beta * v1_v_over_w) + (gamma * v2_v_over_w);

            float u = u_over_w / inv_w;
            float v = v_over_w / inv_w;

            uint32_t vertex_color = mixColor(v0_color, alpha, v1_color, beta, v2_color, gamma);
            uint32_t material_color = material.calcMaterialColor(u, v);
            uint32_t output_color = Math::interpolateUint32(vertex_color, material_color, color_mix);

            m_backbuffer->setPixel(x, y, z, output_color);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
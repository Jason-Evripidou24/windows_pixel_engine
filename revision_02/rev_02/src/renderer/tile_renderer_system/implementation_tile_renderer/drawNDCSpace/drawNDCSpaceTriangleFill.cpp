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
#include "../../tile_renderer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void TileRenderer::drawNDCSpaceTriangleFill
(
    Backbuffer*                   target  ,
    const Math::Geometry::Vertex* v0      ,
    const Math::Geometry::Vertex* v1      ,
    const Math::Geometry::Vertex* v2      ,
    const Material*               material
)
{
    //---------------------------------------------------------------------------------------------------------------------//
    // Screen coordinates.
    //---------------------------------------------------------------------------------------------------------------------//
    int v0_x_screen = target->toBackbufferCoordX(v0->m_position.m_data[0]);
    int v0_y_screen = target->toBackbufferCoordY(v0->m_position.m_data[1]);

    int v1_x_screen = target->toBackbufferCoordX(v1->m_position.m_data[0]);
    int v1_y_screen = target->toBackbufferCoordY(v1->m_position.m_data[1]);

    int v2_x_screen = target->toBackbufferCoordX(v2->m_position.m_data[0]);
    int v2_y_screen = target->toBackbufferCoordY(v2->m_position.m_data[1]);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Bounding box.
    //---------------------------------------------------------------------------------------------------------------------//
    int min_x = v0_x_screen;
    if(v1_x_screen < min_x) { min_x = v1_x_screen; }
    if(v2_x_screen < min_x) { min_x = v2_x_screen; }
    if(min_x < 0) { min_x = 0; }

    int max_x = v0_x_screen;
    if(v1_x_screen > max_x) { max_x = v1_x_screen; }
    if(v2_x_screen > max_x) { max_x = v2_x_screen; }
    if(max_x >= target->m_width) { max_x = target->m_width - 1; }

    int min_y = v0_y_screen;
    if(v1_y_screen < min_y) { min_y = v1_y_screen; }
    if(v2_y_screen < min_y) { min_y = v2_y_screen; }
    if(min_y < 0) { min_y = 0; }

    int max_y = v0_y_screen;
    if(v1_y_screen > max_y) { max_y = v1_y_screen; }
    if(v2_y_screen > max_y) { max_y = v2_y_screen; }
    if(max_y >= target->m_height) { max_y = target->m_height - 1; }

    int tile_min_x = (m_tile_x * target->m_width) / m_tile_split;
    int tile_max_x = ((m_tile_x + 1) * target->m_width) / m_tile_split - 1;

    int tile_min_y = (m_tile_y * target->m_height) / m_tile_split;
    int tile_max_y = ((m_tile_y + 1) * target->m_height) / m_tile_split - 1;

    if(min_x < tile_min_x) { min_x = tile_min_x; }
    if(max_x > tile_max_x) { max_x = tile_max_x; }

    if(min_y < tile_min_y) { min_y = tile_min_y; }
    if(max_y > tile_max_y) { max_y = tile_max_y; }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Draw pixels within bounding box.
    //---------------------------------------------------------------------------------------------------------------------//
    float bx_minus_ax = (float)(v1_x_screen - v0_x_screen);
    float by_minus_ay = (float)(v1_y_screen - v0_y_screen);

    float cx_minus_ax = (float)(v2_x_screen - v0_x_screen);
    float cy_minus_ay = (float)(v2_y_screen - v0_y_screen);

    float w1_denominator = (bx_minus_ax * cy_minus_ay) - (by_minus_ay * cx_minus_ax);
    if(w1_denominator == 0.0f) { return; }

    float w2_denominator = (by_minus_ay * cx_minus_ax) - (bx_minus_ax * cy_minus_ay);
    if(w2_denominator == 0.0f) { return; }

    for(int y = min_y; y <= max_y; y++)
    {
        for(int x = min_x; x <= max_x; x++)
        {
            //-------------------------------------------------------------------------------------------------------------//
            float ay_minus_py = (float)(v0_y_screen - y);
            float px_minus_ax = (float)(x - v0_x_screen);

            float w1 = ( (cx_minus_ax * ay_minus_py) + (cy_minus_ay * px_minus_ax) ) / w1_denominator;
            if(w1 < -0.0001f) { continue; }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            float w2 = ( (ay_minus_py * bx_minus_ax) + (px_minus_ax * by_minus_ay) ) / w2_denominator;
            if(w2 < -0.0001f) { continue; }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            float w0 = 1.0f - w1 - w2;
            if(w0 < -0.0001f) { continue; }
            //-------------------------------------------------------------------------------------------------------------//

            float z = (w0 * v0->m_position.m_data[2]) + (w1 * v1->m_position.m_data[2]) + (w2 * v2->m_position.m_data[2]);

            //-------------------------------------------------------------------------------------------------------------//
            // Perspective correction.
            float a0 = w0 * (1.0f / v0->m_position.m_data[3]);
            float a1 = w1 * (1.0f / v1->m_position.m_data[3]);
            float a2 = w2 * (1.0f / v2->m_position.m_data[3]);
            float denominator = a0 + a1 + a2;
            if(denominator == 0.0f) { continue; }

            a0 /= denominator;
            a1 /= denominator;
            a2 /= denominator;

            // Perspective-correct color.
            Math::Core::Vec4_f color = (v0->m_color * a0) + (v1->m_color * a1) + (v2->m_color * a2);

            Math::Core::Vec2_f tex_coord = (v0->m_tex_coords * a0) + (v1->m_tex_coords * a1) + (v2->m_tex_coords * a2);
            uint32_t tex_color = material->calcMaterialColor(tex_coord.m_data[0], tex_coord.m_data[1]);
            //-------------------------------------------------------------------------------------------------------------//

            //target->setPixel(x, y, z, Math::Core::convertVec4fToColor(color));
            target->setPixel(x, y, z, tex_color);
        }
    }
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
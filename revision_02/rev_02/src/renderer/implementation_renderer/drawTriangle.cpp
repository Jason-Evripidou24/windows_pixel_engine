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
-   Triangle has been transformed to clip space and undergone perspective divide but no clipping against x,y,z planes.
*/
void Renderer::drawTriangle(const Math::Triangle& triangle, Material* material, bool draw_filled, float color_mix)
{
    Math::Triangle new_triangle(triangle);
    
    //---------------------------------------------------------------------------------------------------------------------//
    // Calculate bounding box of triangle in screen space (backbuffer pixel coordinates).
    //---------------------------------------------------------------------------------------------------------------------//
    int x0 = m_backbuffer->toBackbufferCoordX(triangle.m_v0.m_position.m_data[0]);
    int y0 = m_backbuffer->toBackbufferCoordY(triangle.m_v0.m_position.m_data[1]);

    int x1 = m_backbuffer->toBackbufferCoordX(triangle.m_v1.m_position.m_data[0]);
    int y1 = m_backbuffer->toBackbufferCoordY(triangle.m_v1.m_position.m_data[1]);

    int x2 = m_backbuffer->toBackbufferCoordX(triangle.m_v2.m_position.m_data[0]);
    int y2 = m_backbuffer->toBackbufferCoordY(triangle.m_v2.m_position.m_data[1]);

    int x_min = x0;
    if(x1 < x_min) { x_min = x1; }
    if(x2 < x_min) { x_min = x2; }
    if(x_min < 0) { x_min = 0; }

    int x_max = x0;
    if(x1 > x_max) { x_max = x1; }
    if(x2 > x_max) { x_max = x2; }
    if(x_max > m_backbuffer->m_width - 1) { x_max = m_backbuffer->m_width - 1; }

    int y_min = y0;
    if(y1 < y_min) { y_min = y1; }
    if(y2 < y_min) { y_min = y2; }
    if(y_min < 0) { y_min = 0; }

    int y_max = y0;
    if(y1 > y_max) { y_max = y1; }
    if(y2 > y_max) { y_max = y2; }
    if(y_max > m_backbuffer->m_height - 1) { y_max = m_backbuffer->m_height - 1; }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Convert bounding box to tile coordinates that it overlaps.
    //---------------------------------------------------------------------------------------------------------------------//
    int tile_min_x = x_min / m_tile_width;
    int tile_max_x = x_max / m_tile_width;

    int tile_min_y = y_min / m_tile_height;
    int tile_max_y = y_max / m_tile_height;

    int tile_renderers_required = (tile_max_x - tile_min_x + 1) * (tile_max_y - tile_min_y + 1);
    //---------------------------------------------------------------------------------------------------------------------//

    if(draw_filled == true)
    {
        m_pending_jobs.store(tile_renderers_required);
        for(int tile_y = tile_min_y; tile_y <= tile_max_y; tile_y++)
        {
            for(int tile_x = tile_min_x; tile_x <= tile_max_x; tile_x++)
            {
                m_tile_renderers[tile_x + (tile_y * m_tiles_x)]->submitJob(&triangle, material, color_mix);
            }
        }

        std::unique_lock lock(m_pending_jobs_mutex);
        m_pending_jobs_condition_variable.wait
        (
            lock,
            [&]
            {
                return m_pending_jobs.load() == 0;
            }
        );
    }
    else
    {
        this->drawLine(triangle.m_v0, triangle.m_v1, material, color_mix);
        this->drawLine(triangle.m_v0, triangle.m_v2, material, color_mix);
        this->drawLine(triangle.m_v1, triangle.m_v2, material, color_mix);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
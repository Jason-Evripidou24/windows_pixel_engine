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
-   Triangle is in clip space.
*/
void Renderer::drawPolygon(const std::vector<Math::Vertex>& polygon, Material* material, bool draw_filled, float color_mix)
{
    //---------------------------------------------------------------------------------------------------------------------//
    // Calculate bounding box of triangle in screen space (backbuffer pixel coordinates).
    //---------------------------------------------------------------------------------------------------------------------//
    int x_min = m_backbuffer->m_width - 1;
    int x_max = 0;
    int y_min = m_backbuffer->m_height - 1;
    int y_max = 0;

    for(size_t i = 0; i < polygon.size(); i++)
    {
        int x = m_backbuffer->toBackbufferCoordX(polygon[i].m_position.m_data[0]);
        int y = m_backbuffer->toBackbufferCoordY(polygon[i].m_position.m_data[1]);

        if(x < x_min) { x_min = x; }
        if(x > x_max) { x_max = x; }

        if(y < y_min) { y_min = y; }
        if(y > y_max) { y_max = y; }
    }

    if(x_min < 0) { x_min = 0; }
    if(x_min >= m_backbuffer->m_width) { x_min = m_backbuffer->m_width - 1; }

    if(x_max < 0) { x_max = 0; }
    if(x_max >= m_backbuffer->m_width) { x_max = m_backbuffer->m_width - 1; }

    if(y_min < 0) { y_min = 0; }
    if(y_min >= m_backbuffer->m_height) { y_min = m_backbuffer->m_height - 1; }

    if(y_max < 0) { y_max = 0; }
    if(y_max >= m_backbuffer->m_height) { y_max = m_backbuffer->m_height - 1; }
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

    std::atomic<int>        pending_jobs;
    std::mutex              pending_jobs_mutex;
    std::condition_variable pending_jobs_condition_variable;

    pending_jobs.store(tile_renderers_required);

    for(int tile_y = tile_min_y; tile_y <= tile_max_y; tile_y++)
    {
        for(int tile_x = tile_min_x; tile_x <= tile_max_x; tile_x++)
        {
            m_tile_renderers[tile_x + (tile_y * m_tiles_x)]->submitJob
            (
                &polygon,
                material,
                draw_filled,
                color_mix,
                &pending_jobs,
                &pending_jobs_mutex,
                &pending_jobs_condition_variable
            );
        }
    }

    std::unique_lock lock(pending_jobs_mutex);
    pending_jobs_condition_variable.wait
    (
        lock,
        [&]
        {
            return pending_jobs.load() == 0;
        }
    );
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
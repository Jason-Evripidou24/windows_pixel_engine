// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cstdint>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../renderer.hpp"

#include "../../model/model.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawMaterialTriangles(std::queue<MaterialTriangle>& material_triangles_queue, bool draw_filled, float color_mix)
{
    while(material_triangles_queue.empty() == false)
    {
        MaterialTriangle material_triangle = material_triangles_queue.front();
        material_triangles_queue.pop();

        for(int i = 0; i < 16; i++)
        {
            m_tile_renderers[i].second = false;
        }
        for(int i = 0; i < 16; i++)
        {
            m_tile_renderers[i].first->parentRequestDrawMaterialTriangle(&material_triangle, draw_filled, color_mix, &(m_tile_renderers[i].second));
        }

        std::unique_lock renderer_lock(m_renderer_mutex);

        m_renderer_condition_variable.wait
        (
            renderer_lock,
            [&]
            {
                return
                (
                    (m_tile_renderers[0].second == true) &&
                    (m_tile_renderers[1].second == true) &&
                    (m_tile_renderers[2].second == true) &&
                    (m_tile_renderers[3].second == true) &&
                    (m_tile_renderers[4].second == true) &&
                    (m_tile_renderers[5].second == true) &&
                    (m_tile_renderers[6].second == true) &&
                    (m_tile_renderers[7].second == true) &&
                    (m_tile_renderers[8].second == true) &&
                    (m_tile_renderers[9].second == true) &&
                    (m_tile_renderers[10].second == true) &&
                    (m_tile_renderers[11].second == true) &&
                    (m_tile_renderers[12].second == true) &&
                    (m_tile_renderers[13].second == true) &&
                    (m_tile_renderers[14].second == true) &&
                    (m_tile_renderers[15].second == true)
                );
            }
        );
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
void Renderer::drawMaterialTriangles(std::queue<MaterialTriangle*> material_triangles_queue, bool draw_filled)
{
    while(material_triangles_queue.empty() == false)
    {
        MaterialTriangle* material_triangle = material_triangles_queue.front();
        material_triangles_queue.pop();

        m_tile_renderer_0_job_complete = false;
        m_tile_renderer_1_job_complete = false;
        m_tile_renderer_2_job_complete = false;
        m_tile_renderer_3_job_complete = false;

        m_tile_renderer_0.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_0_job_complete);
        m_tile_renderer_1.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_1_job_complete);
        m_tile_renderer_2.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_2_job_complete);
        m_tile_renderer_3.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_3_job_complete);

        std::unique_lock renderer_lock(m_renderer_mutex);

        m_renderer_condition_variable.wait
        (
            renderer_lock,
            [&]
            {
                return
                (
                    (m_tile_renderer_0_job_complete == true) &&
                    (m_tile_renderer_1_job_complete == true) &&
                    (m_tile_renderer_2_job_complete == true) &&
                    (m_tile_renderer_3_job_complete == true)
                );
            }
        );

        delete material_triangle;
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
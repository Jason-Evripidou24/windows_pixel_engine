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

        m_tile_renderer_00_job_complete = false;
        m_tile_renderer_01_job_complete = false;
        m_tile_renderer_02_job_complete = false;
        m_tile_renderer_03_job_complete = false;
        m_tile_renderer_04_job_complete = false;
        m_tile_renderer_05_job_complete = false;
        m_tile_renderer_06_job_complete = false;
        m_tile_renderer_07_job_complete = false;
        m_tile_renderer_08_job_complete = false;
        m_tile_renderer_09_job_complete = false;
        m_tile_renderer_10_job_complete = false;
        m_tile_renderer_11_job_complete = false;
        m_tile_renderer_12_job_complete = false;
        m_tile_renderer_13_job_complete = false;
        m_tile_renderer_14_job_complete = false;
        m_tile_renderer_15_job_complete = false;

        m_tile_renderer_00.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_00_job_complete);
        m_tile_renderer_01.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_01_job_complete);
        m_tile_renderer_02.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_02_job_complete);
        m_tile_renderer_03.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_03_job_complete);
        m_tile_renderer_04.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_04_job_complete);
        m_tile_renderer_05.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_05_job_complete);
        m_tile_renderer_06.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_06_job_complete);
        m_tile_renderer_07.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_07_job_complete);
        m_tile_renderer_08.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_08_job_complete);
        m_tile_renderer_09.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_09_job_complete);
        m_tile_renderer_10.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_10_job_complete);
        m_tile_renderer_11.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_11_job_complete);
        m_tile_renderer_12.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_12_job_complete);
        m_tile_renderer_13.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_13_job_complete);
        m_tile_renderer_14.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_14_job_complete);
        m_tile_renderer_15.parentRequestDrawMaterialTriangle(material_triangle, draw_filled, &m_tile_renderer_15_job_complete);

        std::unique_lock renderer_lock(m_renderer_mutex);

        m_renderer_condition_variable.wait
        (
            renderer_lock,
            [&]
            {
                return
                (
                    (m_tile_renderer_00_job_complete == true) &&
                    (m_tile_renderer_01_job_complete == true) &&
                    (m_tile_renderer_02_job_complete == true) &&
                    (m_tile_renderer_03_job_complete == true) &&
                    (m_tile_renderer_04_job_complete == true) &&
                    (m_tile_renderer_05_job_complete == true) &&
                    (m_tile_renderer_06_job_complete == true) &&
                    (m_tile_renderer_07_job_complete == true) &&
                    (m_tile_renderer_08_job_complete == true) &&
                    (m_tile_renderer_09_job_complete == true) &&
                    (m_tile_renderer_10_job_complete == true) &&
                    (m_tile_renderer_11_job_complete == true) &&
                    (m_tile_renderer_12_job_complete == true) &&
                    (m_tile_renderer_13_job_complete == true) &&
                    (m_tile_renderer_14_job_complete == true) &&
                    (m_tile_renderer_15_job_complete == true)
                );
            }
        );

        delete material_triangle;
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
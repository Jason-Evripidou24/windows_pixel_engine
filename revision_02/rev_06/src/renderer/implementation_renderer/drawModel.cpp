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
void Renderer::drawModel(Model& model, const Math::Mat4_f& projection_view_matrix, bool draw_filled, float color_mix)
{
    std::atomic<int>        pending_jobs(0);
    std::mutex              pending_jobs_mutex;
    std::condition_variable pending_jobs_condition_variable;

    const Math::Mat4_f proj_view_model_matrix = projection_view_matrix * model.calcModelMatrix();

    for(size_t i = 0; i < model.m_mesh->m_sub_meshes.size(); i++)
    {
        Material* material = nullptr;
        int material_index = model.m_mesh->m_sub_meshes[i].m_material_index;
        if(material_index != -1) { material = model.m_mesh->m_materials[material_index]; }

        for(size_t j = 0; j < model.m_mesh->m_sub_meshes[i].m_polygons.size(); j++)
        {
            model.m_polygon_buffers.m_buffer0[i][j].resize(model.m_mesh->m_sub_meshes[i].m_polygons[j].m_num_vertices);

            for(size_t k = 0; k < model.m_mesh->m_sub_meshes[i].m_polygons[j].m_num_vertices; k++)
            {
                Math::transformVertex
                (
                    model.m_polygon_buffers.m_buffer0[i][j].m_vertices[k],
                    model.m_mesh->m_sub_meshes[i].m_polygons[j].m_vertices[k],
                    proj_view_model_matrix
                );
            }

            Math::clipPolygonAgainstPlaneMinX(model.m_polygon_buffers.m_buffer1[i][j], model.m_polygon_buffers.m_buffer0[i][j]);
            Math::clipPolygonAgainstPlaneMaxX(model.m_polygon_buffers.m_buffer0[i][j], model.m_polygon_buffers.m_buffer1[i][j]);
            Math::clipPolygonAgainstPlaneMinY(model.m_polygon_buffers.m_buffer1[i][j], model.m_polygon_buffers.m_buffer0[i][j]);
            Math::clipPolygonAgainstPlaneMaxY(model.m_polygon_buffers.m_buffer0[i][j], model.m_polygon_buffers.m_buffer1[i][j]);
            Math::clipPolygonAgainstPlaneMinZ(model.m_polygon_buffers.m_buffer1[i][j], model.m_polygon_buffers.m_buffer0[i][j]);
            Math::clipPolygonAgainstPlaneMaxZ(model.m_polygon_buffers.m_buffer0[i][j], model.m_polygon_buffers.m_buffer1[i][j]);

            for(size_t k = 0; k < model.m_polygon_buffers.m_buffer0[i][j].m_num_vertices; k++)
            {
                if(Utils::checkFloatEquals(model.m_polygon_buffers.m_buffer0[i][j].m_vertices[k].m_position.m_data[3], 0.0f))
                {
                    model.m_polygon_buffers.m_buffer0[i][j].clear();
                    break;
                }
                model.m_polygon_buffers.m_buffer0[i][j].m_vertices[k].perspectiveDivide();
            }
            if(model.m_polygon_buffers.m_buffer0[i][j].m_num_vertices < 3) { continue; }

            this->sendPolygonToTiles
            (
                &(model.m_polygon_buffers.m_buffer0[i][j]),
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
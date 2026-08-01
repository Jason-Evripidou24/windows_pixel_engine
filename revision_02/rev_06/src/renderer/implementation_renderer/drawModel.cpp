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

    size_t num_sub_meshes = model.m_mesh->m_sub_meshes.size();
    for(size_t i = 0; i < num_sub_meshes; i++)
    {
        SubMesh& model_sub_mesh = model.m_mesh->m_sub_meshes[i];
        std::vector<Geometry::Polygon>& model_sub_mesh_buffer0 = model.m_polygon_buffers.m_buffer0[i];
        std::vector<Geometry::Polygon>& model_sub_mesh_buffer1 = model.m_polygon_buffers.m_buffer1[i];

        Material* material = nullptr;
        int material_index = model_sub_mesh.m_material_index;
        if(material_index != -1) { material = model.m_mesh->m_materials[material_index]; }

        size_t num_polygons = model_sub_mesh.m_wireframe.m_num_polygons;
        for(size_t j = 0; j < num_polygons; j++)
        {
            model_sub_mesh_buffer0[j].resize(model_sub_mesh.m_wireframe.m_polygons[j].m_num_vertices);

            Geometry::transformPolygon
            (
                model_sub_mesh_buffer0[j],
                model_sub_mesh.m_wireframe.m_polygons[j],
                proj_view_model_matrix
            );

            Geometry::clipPolygonAgainstPlaneMinX(model_sub_mesh_buffer1[j], model_sub_mesh_buffer0[j]);
            Geometry::clipPolygonAgainstPlaneMaxX(model_sub_mesh_buffer0[j], model_sub_mesh_buffer1[j]);
            Geometry::clipPolygonAgainstPlaneMinY(model_sub_mesh_buffer1[j], model_sub_mesh_buffer0[j]);
            Geometry::clipPolygonAgainstPlaneMaxY(model_sub_mesh_buffer0[j], model_sub_mesh_buffer1[j]);
            Geometry::clipPolygonAgainstPlaneMinZ(model_sub_mesh_buffer1[j], model_sub_mesh_buffer0[j]);
            Geometry::clipPolygonAgainstPlaneMaxZ(model_sub_mesh_buffer0[j], model_sub_mesh_buffer1[j]);

            for(size_t k = 0; k < model_sub_mesh_buffer0[j].m_num_vertices; k++)
            {
                if(Utils::checkFloatEquals(model_sub_mesh_buffer0[j].m_vertices[k].m_position.m_data[3], 0.0f))
                {
                    model_sub_mesh_buffer0[j].clear();
                    break;
                }
                model_sub_mesh_buffer0[j].m_vertices[k].perspectiveDivide();
            }
            if(model_sub_mesh_buffer0[j].m_num_vertices < 3) { continue; }

            this->sendPolygonToTiles
            (
                &(model_sub_mesh_buffer0[j]),
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
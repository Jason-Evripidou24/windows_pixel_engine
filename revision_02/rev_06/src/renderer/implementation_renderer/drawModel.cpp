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

    size_t num_sub_meshes = model.m_mesh->m_render_meshes.size();
    for(size_t i = 0; i < num_sub_meshes; i++)
    {
        RenderMesh& model_render_mesh = model.m_mesh->m_render_meshes[i];

        Material* material = nullptr;
        int material_index = model_render_mesh.m_material_index;
        if(material_index != -1) { material = model.m_mesh->m_materials[material_index]; }

        size_t num_polygons = model_render_mesh.m_wireframe.m_num_polygons;
        for(size_t j = 0; j < num_polygons; j++)
        {
            std::shared_ptr<Geometry::Polygon> buffer0 = std::make_shared<Geometry::Polygon>();
            Geometry::Polygon buffer1;

            buffer0->resize(model_render_mesh.m_wireframe.m_polygons[j].m_num_vertices);
            buffer1.resize(model_render_mesh.m_wireframe.m_polygons[j].m_num_vertices);

            Geometry::transformPolygon( (*buffer0), model_render_mesh.m_wireframe.m_polygons[j], proj_view_model_matrix);

            Geometry::clipPolygonAgainstPlaneMinX(buffer1, (*buffer0));
            Geometry::clipPolygonAgainstPlaneMaxX((*buffer0), buffer1);
            Geometry::clipPolygonAgainstPlaneMinY(buffer1, (*buffer0));
            Geometry::clipPolygonAgainstPlaneMaxY((*buffer0), buffer1);
            Geometry::clipPolygonAgainstPlaneMinZ(buffer1, (*buffer0));
            Geometry::clipPolygonAgainstPlaneMaxZ((*buffer0), buffer1);

            for(size_t k = 0; k < buffer0->m_num_vertices; k++)
            {
                if(Utils::checkFloatEquals(buffer0->m_vertices[k].m_position.m_data[3], 0.0f))
                {
                    buffer0->clear();
                    break;
                }
                buffer0->m_vertices[k].perspectiveDivide();
            }
            if(buffer0->m_num_vertices < 3) { continue; }

            this->sendPolygonToTiles
            (
                buffer0,
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
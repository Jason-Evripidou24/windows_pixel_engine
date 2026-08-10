// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <thread>
#include <vector>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../model.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Model::renderModel(Renderer& renderer, const Math::Core::Mat4_f& projection_view_matrix, bool draw_filled, float color_mix)
{
    std::atomic<int>        pending_jobs(0);
    std::mutex              pending_jobs_mutex;
    std::condition_variable pending_jobs_condition_variable;

    const Math::Core::Mat4_f proj_view_model_matrix = projection_view_matrix * this->calcModelMatrix();

    size_t num_render_wireframes = m_mesh->m_render_wireframes.size();
    for(size_t i = 0; i < num_render_wireframes; i++)
    {
        Math::Geometry::Wireframe& render_wireframe = m_mesh->m_render_wireframes[i].m_wireframe;
        std::string& render_wireframe_material_name = m_mesh->m_render_wireframes[i].m_wireframe_material_name;

        Material* material = nullptr;
        if
        (
            m_mesh->m_material_library.m_materials.find(render_wireframe_material_name) !=
            m_mesh->m_material_library.m_materials.end()
        )
        {
            material = m_mesh->m_material_library.m_materials[render_wireframe_material_name].get();
        }

        size_t num_polygons = render_wireframe.m_num_polygons;
        for(size_t j = 0; j < num_polygons; j++)
        {
            std::shared_ptr<Math::Geometry::Polygon> buffer0 = std::make_shared<Math::Geometry::Polygon>();
            Math::Geometry::Polygon buffer1;

            buffer0->resize(render_wireframe.m_polygons[j].m_num_vertices);
            buffer1.resize(render_wireframe.m_polygons[j].m_num_vertices);

            Math::Geometry::transformPolygon( (*buffer0), render_wireframe.m_polygons[j], proj_view_model_matrix);

            Math::Geometry::clipPolygonAgainstPlaneMinX(buffer1, (*buffer0));
            Math::Geometry::clipPolygonAgainstPlaneMaxX((*buffer0), buffer1);
            Math::Geometry::clipPolygonAgainstPlaneMinY(buffer1, (*buffer0));
            Math::Geometry::clipPolygonAgainstPlaneMaxY((*buffer0), buffer1);
            Math::Geometry::clipPolygonAgainstPlaneMinZ(buffer1, (*buffer0));
            Math::Geometry::clipPolygonAgainstPlaneMaxZ((*buffer0), buffer1);

            for(size_t k = 0; k < buffer0->m_num_vertices; k++)
            {
                if(Math::Core::checkFloatEquals(buffer0->m_vertices[k].m_position.m_data[3], 0.0f))
                {
                    buffer0->clear();
                    break;
                }
                buffer0->m_vertices[k].perspectiveDivide();
            }
            if(buffer0->m_num_vertices < 3) { continue; }

            renderer.sendPolygonToTiles
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
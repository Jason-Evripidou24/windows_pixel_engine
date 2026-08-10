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
void Renderer::transformAndDrawLocalSpaceModel
(
    const Model&              model,
    const Math::Core::Mat4_f& projection_view_matrix,
    bool                      draw_filled,
    float                     color_mix
)
{
    std::atomic<int>        pending_jobs(0);
    std::mutex              pending_jobs_mutex;
    std::condition_variable pending_jobs_condition_variable;

    const Math::Core::Mat4_f proj_view_model_matrix = projection_view_matrix * model.calcModelMatrix();

    size_t num_render_wireframes = model.m_mesh->m_render_wireframes.size();

    for(size_t i = 0; i < num_render_wireframes; i++)
    {
        Math::Geometry::Wireframe& render_wireframe = model.m_mesh->m_render_wireframes[i].m_wireframe;
        std::string& render_wireframe_material_name = model.m_mesh->m_render_wireframes[i].m_wireframe_material_name;

        Material* material = nullptr;
        if
        (
            model.m_mesh->m_material_library.m_materials.find(render_wireframe_material_name) !=
            model.m_mesh->m_material_library.m_materials.end()
        )
        {
            material = model.m_mesh->m_material_library.m_materials[render_wireframe_material_name].get();
        }

        this->transformAndDrawLocalSpaceWireframe
        (
            render_wireframe,
            proj_view_model_matrix,
            material,
            draw_filled,
            color_mix,
            &pending_jobs,
            &pending_jobs_mutex,
            &pending_jobs_condition_variable
        );
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
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cmath>
#include <memory>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../renderer.hpp"

#include "../../math/core/math_core.hpp"
#include "../../math/geometry/math_geometry.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawLocalSpaceModel
(
    std::shared_ptr<Backbuffer> target                ,
    const Model&                model                 ,
    size_t                      polygon_max_chunk_size,
    const Math::Core::Mat4_f&   proj_view_matrix      ,
    const bool                  draw_filled
)
{
    const Math::Core::Mat4_f proj_view_model_matrix = proj_view_matrix * model.calcModelMatrix();

    const MaterialLibrary& material_library = model.m_mesh->m_material_library;

    for(size_t i = 0; i < model.m_mesh->m_render_wireframes.size(); i++)
    {
        const Math::Geometry::Wireframe& wireframe = model.m_mesh->m_render_wireframes[i].m_wireframe;
        const std::string& material_name = model.m_mesh->m_render_wireframes[i].m_wireframe_material_name;

        std::shared_ptr<const Material> material   = nullptr;
        auto it = material_library.m_materials.find(material_name);
        if(it != material_library.m_materials.end())
        {
            material = it->second;
        }
        else
        {
            material = std::make_shared<Material>();
        }

        m_transformation_system.sendLocalSpaceWireframeToTransformers
        (
            target                ,
            wireframe             ,
            polygon_max_chunk_size,
            proj_view_model_matrix,
            material              ,
            draw_filled
        );
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
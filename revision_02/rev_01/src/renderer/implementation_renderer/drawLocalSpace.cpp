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
    const Math::Core::Mat4_f&   proj_view_matrix,
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

        for(int j = 0; j < wireframe.m_num_polygons; j++)
        {
            const Math::Geometry::Polygon& polygon = wireframe.m_polygons[j];

            Math::Geometry::Polygon polygon_transformed;
            Math::Geometry::transformPolygon(polygon_transformed, polygon, proj_view_model_matrix);

            this->drawClipSpacePolygon(target, polygon_transformed, material, draw_filled);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
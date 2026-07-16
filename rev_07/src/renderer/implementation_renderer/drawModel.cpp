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
/*
*/
void Renderer::drawModel
(
    Backbuffer& backbuffer,
    const Model& model,
    const Math::Mat4_f& projection_view_matrix,
    const bool draw_filled
)
{
    const Math::Mat4_f proj_view_model_matrix = projection_view_matrix * model.calcModelMatrix();

    for(int i = 0; i < model.m_mesh->m_triangles.size(); i++)
    {
        const Math::Triangle& triangle = model.m_mesh->m_triangles[i];
        const int material_index = model.m_mesh->m_triangles_material_index[i];
        const Material& material = model.m_mesh->m_materials[material_index];

        const Math::Triangle triangle_transform = Math::transformTriangle(triangle, proj_view_model_matrix);
        if
        (
            (triangle_transform.m_vertices[0].m_position.m_data[3] <= 0.0f) ||
            (triangle_transform.m_vertices[1].m_position.m_data[3] <= 0.0f) ||
            (triangle_transform.m_vertices[2].m_position.m_data[3] <= 0.0f)
        )
        {
            continue;
        }

        const Math::Triangle perspective_divide_triangle = Math::perspectiveDivideTriangle(triangle_transform);
        if
        (
            (Utils::checkFloatEquals(perspective_divide_triangle.m_vertices[0].m_position.m_data[3], 0.0f) == true) ||
            (Utils::checkFloatEquals(perspective_divide_triangle.m_vertices[1].m_position.m_data[3], 0.0f) == true) ||
            (Utils::checkFloatEquals(perspective_divide_triangle.m_vertices[2].m_position.m_data[3], 0.0f) == true)
        )
        {
            continue;
        }

        this->drawTriangle(backbuffer, perspective_divide_triangle, material, draw_filled);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
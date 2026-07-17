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
#include "../model.hpp"
#include "../render_triangle.hpp"

#include "../../math/mat4_f.hpp"
#include "../../math/math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<RenderTriangle> Model::transformModelForRendering(const Math::Mat4_f& projection_view_matrix) const
{
    const Math::Mat4_f proj_view_model_matrix = projection_view_matrix * this->calcModelMatrix();

    std::vector<RenderTriangle> output_render_triangles;
    output_render_triangles.reserve(m_mesh->m_triangles.size());

    for(int i = 0; i < m_mesh->m_triangles.size(); i++)
    {
        Math::Triangle triangle = m_mesh->m_triangles[i];
        const int material_index = m_mesh->m_triangles_material_index[i];
        const Material& material = m_mesh->m_materials[material_index];

        triangle = Math::transformTriangle(triangle, proj_view_model_matrix);
        if
        (
            (triangle.m_vertices[0].m_position.m_data[3] <= 0.0f) ||
            (triangle.m_vertices[1].m_position.m_data[3] <= 0.0f) ||
            (triangle.m_vertices[2].m_position.m_data[3] <= 0.0f)
        )
        {
            continue;
        }

        triangle = Math::perspectiveDivideTriangle(triangle);
        if
        (
            (Utils::checkFloatEquals(triangle.m_vertices[0].m_position.m_data[3], 0.0f) == true) ||
            (Utils::checkFloatEquals(triangle.m_vertices[1].m_position.m_data[3], 0.0f) == true) ||
            (Utils::checkFloatEquals(triangle.m_vertices[2].m_position.m_data[3], 0.0f) == true)
        )
        {
            continue;
        }

        output_render_triangles.push_back(RenderTriangle(triangle, &material));
    }

    return output_render_triangles;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
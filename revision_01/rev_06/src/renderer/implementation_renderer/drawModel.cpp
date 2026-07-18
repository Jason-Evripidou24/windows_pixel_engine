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

    for(const Math::Vec3_i& triangle_indices : model.m_mesh->m_triangles_indices)
    {
        int index_0 = triangle_indices.m_data[0];
        int index_1 = triangle_indices.m_data[1];
        int index_2 = triangle_indices.m_data[2];

        const Math::Vertex& vertex_0 = model.m_mesh->m_vertices[index_0];
        const Math::Vertex& vertex_1 = model.m_mesh->m_vertices[index_1];
        const Math::Vertex& vertex_2 = model.m_mesh->m_vertices[index_2];

        const Math::Triangle triangle(vertex_0, vertex_1, vertex_2);

        const Math::Triangle triangle_transform = this->transformTriangle(triangle, proj_view_model_matrix);
        if
        (
            (triangle_transform.m_vertices[0].m_position.m_data[3] <= 0.0f) ||
            (triangle_transform.m_vertices[1].m_position.m_data[3] <= 0.0f) ||
            (triangle_transform.m_vertices[2].m_position.m_data[3] <= 0.0f)
        )
        {
            continue;
        }

        const Math::Triangle perspective_divide_triangle = this->perspectiveDivideTriangle(triangle_transform);
        if
        (
            (Utils::checkFloatEquals(perspective_divide_triangle.m_vertices[0].m_position.m_data[3], 0.0f) == true) ||
            (Utils::checkFloatEquals(perspective_divide_triangle.m_vertices[1].m_position.m_data[3], 0.0f) == true) ||
            (Utils::checkFloatEquals(perspective_divide_triangle.m_vertices[2].m_position.m_data[3], 0.0f) == true)
        )
        {
            continue;
        }

        this->drawTriangle(backbuffer, perspective_divide_triangle, draw_filled);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
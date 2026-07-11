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

#include "../../backbuffer/backbuffer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawModel
(
    Backbuffer&  backbuffer,
    Model& model,
    Math::Mat4_f proj_view_matrix
)
{
    Math::Mat4_f model_mat = model.calcModelMatrix();
    Math::Mat4_f proj_view_mode_mat = proj_view_matrix * model_mat;

    for(int j = 0; j < model.m_mesh->m_triangles.size(); j++)
    {
        int triangle_vertex_0_index = model.m_mesh->m_triangles[j].m_data[0];
        int triangle_vertex_1_index = model.m_mesh->m_triangles[j].m_data[1];
        int triangle_vertex_2_index = model.m_mesh->m_triangles[j].m_data[2];

        Math::Vec4_f transformed_position_0 = proj_view_mode_mat * model.m_mesh->m_vertices[triangle_vertex_0_index].m_position;
        Math::Vec4_f transformed_position_1 = proj_view_mode_mat * model.m_mesh->m_vertices[triangle_vertex_1_index].m_position;
        Math::Vec4_f transformed_position_2 = proj_view_mode_mat * model.m_mesh->m_vertices[triangle_vertex_2_index].m_position;

        if
        (
            transformed_position_0.m_data[3] <= 0.0f ||
            transformed_position_1.m_data[3] <= 0.0f ||
            transformed_position_2.m_data[3] <= 0.0f
        )
        {
            continue;
        }

        uint32_t color_0 = model.m_mesh->m_vertices[triangle_vertex_0_index].m_color;
        uint32_t color_1 = model.m_mesh->m_vertices[triangle_vertex_1_index].m_color;
        uint32_t color_2 = model.m_mesh->m_vertices[triangle_vertex_2_index].m_color;

        Math::Vec3_f p0_clip = Math::Vec3_f
        (
            transformed_position_0.m_data[0] / transformed_position_0.m_data[3],
            transformed_position_0.m_data[1] / transformed_position_0.m_data[3],
            transformed_position_0.m_data[2] / transformed_position_0.m_data[3]
        );
        Math::Vec3_f p1_clip = Math::Vec3_f
        (
            transformed_position_1.m_data[0] / transformed_position_1.m_data[3],
            transformed_position_1.m_data[1] / transformed_position_1.m_data[3],
            transformed_position_1.m_data[2] / transformed_position_1.m_data[3]
        );
        Math::Vec3_f p2_clip = Math::Vec3_f
        (
            transformed_position_2.m_data[0] / transformed_position_2.m_data[3],
            transformed_position_2.m_data[1] / transformed_position_2.m_data[3],
            transformed_position_2.m_data[2] / transformed_position_2.m_data[3]
        );

        this->drawWireframeTriangle(backbuffer, p0_clip, color_0, p1_clip, color_1, p2_clip, color_2);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
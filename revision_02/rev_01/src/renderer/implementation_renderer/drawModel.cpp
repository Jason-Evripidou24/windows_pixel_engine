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
void Renderer::drawModel(const Model& model, const Math::Mat4_f& projection_view_matrix, bool draw_filled, float color_mix)
{
    const Math::Mat4_f proj_view_model_matrix = projection_view_matrix * model.calcModelMatrix();

    for(size_t i = 0; i < model.m_mesh->m_sub_meshes.size(); i++)
    {
        for(size_t j = 0; j < model.m_mesh->m_sub_meshes[i].m_triangles.size(); j++)
        {
            Math::Triangle triangle = model.m_mesh->m_sub_meshes[i].m_triangles[j];
            int material_index = model.m_mesh->m_sub_meshes[i].m_material_index;
            Material material;

            if(material_index != -1)
            {
                material = *(model.m_mesh->m_materials[material_index]);
            }
            else
            {
                material = Material();
            }

            triangle = Math::transformTriangle(triangle, proj_view_model_matrix);
            if
            (
                (triangle.m_v0.m_position.m_data[3] <= 0.0f) ||
                (triangle.m_v1.m_position.m_data[3] <= 0.0f) ||
                (triangle.m_v2.m_position.m_data[3] <= 0.0f)
            )
            {
                continue;
            }

            triangle = Math::perspectiveDivideTriangle(triangle);
            if
            (
                (Utils::checkFloatEquals(triangle.m_v0.m_position.m_data[3], 0.0f) == true) ||
                (Utils::checkFloatEquals(triangle.m_v1.m_position.m_data[3], 0.0f) == true) ||
                (Utils::checkFloatEquals(triangle.m_v2.m_position.m_data[3], 0.0f) == true)
            )
            {
                continue;
            }

            std::vector<Math::Triangle> triangles_clipped = Math::clipTriangleBetweenXYZ
            (
                triangle,
                -1.0f,
                1.0f,
                -1.0f,
                1.0f,
                -1.0f,
                1.0f
            );

            for(size_t j = 0; j < triangles_clipped.size(); j++)
            {
                Math::Triangle& triangle_clipped = triangles_clipped[j];
                this->drawTriangle(triangle_clipped, material, draw_filled, color_mix);
            }
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
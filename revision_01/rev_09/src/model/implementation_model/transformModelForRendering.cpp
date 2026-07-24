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
#include "../material_triangle.hpp"

#include "../../math/mat4_f.hpp"
#include "../../math/math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::queue<MaterialTriangle*> Model::transformModelForRendering(const Math::Mat4_f& projection_view_matrix) const
{
    const Math::Mat4_f proj_view_model_matrix = projection_view_matrix * this->calcModelMatrix();

    std::queue<MaterialTriangle*> output_material_triangles_queue;

    for(int i = 0; i < m_mesh->m_triangles.size(); i++)
    {
        Math::Triangle triangle = m_mesh->m_triangles[i];
        const int material_index = m_mesh->m_triangles_material_index[i];
        const Material& material = m_mesh->m_materials[material_index];

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

        MaterialTriangle* new_material_triangle = new MaterialTriangle(triangle, material);
        output_material_triangles_queue.push(new_material_triangle);
    }

    return output_material_triangles_queue;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
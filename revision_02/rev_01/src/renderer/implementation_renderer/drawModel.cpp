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

            Material* material = nullptr;
            if(material_index != -1) { material = model.m_mesh->m_materials[material_index]; }

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
            if( (i == 0) && (j == 0) )
            {
                std::string info_string = triangle.toString(4, 2);
                m_backbuffer->setText(10, 30, info_string.c_str(), info_string.size(), 0xFF00FF00);
            }

            //std::vector<Math::Triangle> triangles_clipped = Math::clipAgainstPlaneMinX(triangle);
            std::vector<Math::Triangle> triangles_clipped = Math::clipAgainstPlaneMinMaxX(triangle);
            //polygon = clipAgainstPlane(polygon, ClipPlane::MIN_X);
            //polygon = clipAgainstPlane(polygon, ClipPlane::MAX_X);

            //polygon = clipAgainstPlane(polygon, ClipPlane::MIN_Y);
            //polygon = clipAgainstPlane(polygon, ClipPlane::MAX_Y);

            //polygon = clipAgainstPlane(polygon, ClipPlane::MIN_Z);
            //polygon = clipAgainstPlane(polygon, ClipPlane::MAX_Z);


            for(Math::Triangle& triangle_clipped : triangles_clipped)
            {
                triangle_clipped = Math::perspectiveDivideTriangle(triangle_clipped);
                if
                (
                    (Utils::checkFloatEquals(triangle.m_v0.m_position.m_data[3], 0.0f) == true) ||
                    (Utils::checkFloatEquals(triangle.m_v1.m_position.m_data[3], 0.0f) == true) ||
                    (Utils::checkFloatEquals(triangle.m_v2.m_position.m_data[3], 0.0f) == true)
                )
                {
                    continue;
                }
                this->drawTriangle(triangle_clipped, material, draw_filled, color_mix);
            }
            


            /*
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
            */
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
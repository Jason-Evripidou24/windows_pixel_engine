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
void Renderer::drawModel(Model& model, const Math::Mat4_f& projection_view_matrix, bool draw_filled, float color_mix)
{
    const Math::Mat4_f proj_view_model_matrix = projection_view_matrix * model.calcModelMatrix();

    for(size_t i = 0; i < model.m_mesh->m_sub_meshes.size(); i++)
    {
        Material* material = nullptr;
        int material_index = model.m_mesh->m_sub_meshes[i].m_material_index;
        if(material_index != -1) { material = model.m_mesh->m_materials[material_index]; }

        for(size_t j = 0; j < model.m_mesh->m_sub_meshes[i].m_triangles.size(); j++)
        {
            const Math::Triangle& orig_triangle = model.m_mesh->m_sub_meshes[i].m_triangles[j];
            Math::Triangle& transform_triangle = model.m_sub_meshes_for_transform[i].m_triangles[j];
            transform_triangle = Math::transformTriangle(orig_triangle, proj_view_model_matrix);

            std::vector<Math::Vertex> polygon;
            polygon.push_back(transform_triangle.m_v0);
            polygon.push_back(transform_triangle.m_v1);
            polygon.push_back(transform_triangle.m_v2);
            polygon = Math::clipPolygonAgainstPlaneMinX(polygon);
            polygon = Math::clipPolygonAgainstPlaneMaxX(polygon);
            polygon = Math::clipPolygonAgainstPlaneMinY(polygon);
            polygon = Math::clipPolygonAgainstPlaneMaxY(polygon);
            polygon = Math::clipPolygonAgainstPlaneMinZ(polygon);
            polygon = Math::clipPolygonAgainstPlaneMaxZ(polygon);

            for(size_t k = 0; k < polygon.size(); k++)
            {
                if(Utils::checkFloatEquals(polygon[k].m_position.m_data[3], 0.0f))
                {
                    polygon.clear();
                    break;
                }

                polygon[k] = Math::perspectiveDivideVertex(polygon[k]);
            }
            if(polygon.size() < 3) { continue; }
            //std::vector<Math::Triangle> triangles_clipped = Math::clipAgainstPlaneMinMaxXYZ(transform_triangle);

            for(size_t k = 1; k < polygon.size() - 1; k++)
            {
                /*
                triangle_clipped = Math::perspectiveDivideTriangle(triangle_clipped);
                if
                (
                    (Utils::checkFloatEquals(triangle_clipped.m_v0.m_position.m_data[3], 0.0f) == true) ||
                    (Utils::checkFloatEquals(triangle_clipped.m_v1.m_position.m_data[3], 0.0f) == true) ||
                    (Utils::checkFloatEquals(triangle_clipped.m_v2.m_position.m_data[3], 0.0f) == true)
                )
                {
                    continue;
                }
                */
                Math::Triangle triangle_clipped(polygon[0], polygon[k], polygon[k + 1]);
                this->drawTriangle(triangle_clipped, material, draw_filled, color_mix);
            }
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
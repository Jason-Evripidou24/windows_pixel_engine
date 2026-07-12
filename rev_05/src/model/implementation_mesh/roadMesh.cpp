// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <vector>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../mesh.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mesh Mesh::roadMesh(uint32_t color)
{
    Mesh road_mesh;
    
    int cross_section_vertex_count = 13;
    int num_cross_sections = 2;

    int triangles_count = ((cross_section_vertex_count - 1) * 2) * (num_cross_sections - 1);

    //---------------------------------------------------------------------------------------------------------------------//
    // Vertices: Position and colour.
    //---------------------------------------------------------------------------------------------------------------------//
    float cen_x  = 0.0f;    float cen_y  = 0.45f;
    float leb_x  = -4.0f;   float leb_y  = 0.15f;           float reb_x  = 4.0f;   float reb_y  = 0.15f;
    float linv_x = -4.3f;   float linv_y = 0.0f;            float rinv_x = 4.3f;   float rinv_y = 0.0f;
    float ltk_x  = -4.4f;   float ltk_y  = 0.45f;           float rtk_x  = 4.4f;   float rtk_y  = 0.45f;
    float lbk_x  = -4.7f;   float lbk_y  = 0.45f;           float rbk_x  = 4.7f;   float rbk_y  = 0.45f;
    float lfp_x  = -6.0f;   float lfp_y  = 0.7f;            float rfp_x  = 6.0f;   float rfp_y  = 0.7f;
    float lbp_x  = -7.0f;   float lbp_y  = 0.7f;            float rbp_x  = 7.0f;   float rbp_y  = 0.7f;

    road_mesh.m_vertices = std::vector<Math::Vertex>(cross_section_vertex_count * num_cross_sections);

    for(int i = 0; i < num_cross_sections; i++)
    {
        float z_pos = (float)i;

        // LHS
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 0].m_position = Math::Vec4_f(lbp_x, lbp_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 1].m_position = Math::Vec4_f(lfp_x, lfp_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 2].m_position = Math::Vec4_f(lbk_x, lbk_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 3].m_position = Math::Vec4_f(ltk_x, ltk_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 4].m_position = Math::Vec4_f(linv_x, linv_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 5].m_position = Math::Vec4_f(leb_x, leb_y, z_pos, 1.0f);

        // Center
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 6].m_position = Math::Vec4_f(cen_x, cen_y, z_pos, 1.0f);

        // RHS
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 7].m_position = Math::Vec4_f(reb_x, reb_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 8].m_position = Math::Vec4_f(rinv_x, rinv_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 9].m_position = Math::Vec4_f(rtk_x, rtk_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 10].m_position = Math::Vec4_f(rbk_x, rbk_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 11].m_position = Math::Vec4_f(rfp_x, rfp_y, z_pos, 1.0f);
        road_mesh.m_vertices[(i * cross_section_vertex_count) + 12].m_position = Math::Vec4_f(rbp_x, rbp_y, z_pos, 1.0f);
    }
    for(int i = 0; i < cross_section_vertex_count * num_cross_sections; i++)
    {
        road_mesh.m_vertices[i].m_color = color;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Indicies: Each triplet represents a triangle face.
    //---------------------------------------------------------------------------------------------------------------------//
    road_mesh.m_triangles = std::vector<Math::Vec3_i>(triangles_count);

    for(int i = 0; i < cross_section_vertex_count - 1; i++)
    {
        road_mesh.m_triangles[(i * 2) + 0] = Math::Vec3_i(i, i + cross_section_vertex_count, i + cross_section_vertex_count + 1);
        road_mesh.m_triangles[(i * 2) + 1] = Math::Vec3_i(i, i + cross_section_vertex_count + 1, i + 1);
    }
    //---------------------------------------------------------------------------------------------------------------------//

    return road_mesh;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
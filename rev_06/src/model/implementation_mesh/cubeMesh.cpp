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
/*
-   A 1 * 1 * 1 cube, with center at (0, 0, 0)
*/
Mesh Mesh::cubeMesh()
{
    Mesh cube_mesh;
    
    int vertex_count    = 8;
    int triangles_count = 12;

    //-----------------------------------------------------------------------------------------------------------------//
    // Vertices: Position and colour.
    //-----------------------------------------------------------------------------------------------------------------//
    float right_x = 0.5f;
    float left_x = -0.5f;

    float top_y = 0.5f;
    float bottom_y = -0.5f;

    float front_z = 0.5f;
    float back_z = -0.5f;

    cube_mesh.m_vertices = std::vector<Math::Vertex>(vertex_count);

    // Front faces
    cube_mesh.m_vertices[0].m_position = Math::Vec4_f(left_x, top_y, front_z, 1.0f);
    cube_mesh.m_vertices[0].m_color = 0xFFFF00FF; // Magenta

    cube_mesh.m_vertices[1].m_position = Math::Vec4_f(right_x, top_y, front_z, 1.0f);
    cube_mesh.m_vertices[1].m_color = 0xFFFF00FF; // Magenta

    cube_mesh.m_vertices[2].m_position = Math::Vec4_f(left_x, bottom_y, front_z, 1.0f);
    cube_mesh.m_vertices[2].m_color = 0xFF00FFFF; // Cyan

    cube_mesh.m_vertices[3].m_position = Math::Vec4_f(right_x, bottom_y, front_z, 1.0f);
    cube_mesh.m_vertices[3].m_color = 0xFF00FFFF; // Cyan

    // Back faces
    cube_mesh.m_vertices[4].m_position = Math::Vec4_f(right_x, top_y, back_z, 1.0f);
    cube_mesh.m_vertices[4].m_color = 0xFFFF00FF; // Magenta

    cube_mesh.m_vertices[5].m_position = Math::Vec4_f(left_x, top_y, back_z, 1.0f);
    cube_mesh.m_vertices[5].m_color = 0xFFFF00FF; // Magenta

    cube_mesh.m_vertices[6].m_position = Math::Vec4_f(right_x, bottom_y, back_z, 1.0f);
    cube_mesh.m_vertices[6].m_color = 0xFF00FFFF; // Cyan

    cube_mesh.m_vertices[7].m_position = Math::Vec4_f(left_x, bottom_y, back_z, 1.0f);
    cube_mesh.m_vertices[7].m_color = 0xFF00FFFF; // Cyan
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Indicies: Each triplet represents a triangle face.
    //-----------------------------------------------------------------------------------------------------------------//
    cube_mesh.m_triangles_indices = std::vector<Math::Vec3_i>(triangles_count);

    // Front Face (+Z)
    cube_mesh.m_triangles_indices[0] = Math::Vec3_i(0, 1, 2);
    cube_mesh.m_triangles_indices[1] = Math::Vec3_i(1, 3, 2);

    // Rear Face (-Z)
    cube_mesh.m_triangles_indices[2] = Math::Vec3_i(4, 5, 6);
    cube_mesh.m_triangles_indices[3] = Math::Vec3_i(5, 7, 6);

    // Top Face (+Y)
    cube_mesh.m_triangles_indices[4] = Math::Vec3_i(5, 4, 0);
    cube_mesh.m_triangles_indices[5] = Math::Vec3_i(4, 1, 0);

    // Bottom Face (-Y)
    cube_mesh.m_triangles_indices[6] = Math::Vec3_i(2, 3, 7);
    cube_mesh.m_triangles_indices[7] = Math::Vec3_i(3, 6, 7);

    // Left Face (-X)
    cube_mesh.m_triangles_indices[8] = Math::Vec3_i(5, 0, 7);
    cube_mesh.m_triangles_indices[9] = Math::Vec3_i(0, 2, 7);

    // Right Face (+X)
    cube_mesh.m_triangles_indices[10] = Math::Vec3_i(1, 4, 3);
    cube_mesh.m_triangles_indices[11] = Math::Vec3_i(4, 6, 3);
    //-----------------------------------------------------------------------------------------------------------------//

    return cube_mesh;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
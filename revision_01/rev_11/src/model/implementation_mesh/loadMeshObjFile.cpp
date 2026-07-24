// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
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

#include "../../math/triangle.hpp"
#include "../../math/vec2_f.hpp"
#include "../../math/vec3_f.hpp"
#include "../../math/vec4_f.hpp"
#include "../../math/vertex.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Mesh::loadMeshObjFile(const std::string& file_folder, const std::string& filename)
{
    m_obj_file_info.loadObjFile(file_folder, filename);
    m_mtl_file_info.loadMtlFile(file_folder, std::string("mtl.mtl"));

    m_material_triangles.clear();

    for(const ObjFile::ObjMaterialTriangleInfo& material_triangle_info : m_obj_file_info.m_material_triangles)
    {
        const ObjFile::ObjTriangleInfo& triangle_info = material_triangle_info.m_triangle;
        const std::string& material_name = material_triangle_info.m_material_name;

        const ObjFile::ObjVertexInfo& v0_info = triangle_info.m_v0;
        const ObjFile::ObjVertexInfo& v1_info = triangle_info.m_v1;
        const ObjFile::ObjVertexInfo& v2_info = triangle_info.m_v2;

        int v0_pos_and_color_index = v0_info.m_position_and_color;
        int v0_tex_coord_index = v0_info.m_tex_coord;
        int v0_normal_index = v0_info.m_normal;

        int v1_pos_and_color_index = v1_info.m_position_and_color;
        int v1_tex_coord_index = v1_info.m_tex_coord;
        int v1_normal_index = v1_info.m_normal;

        int v2_pos_and_color_index = v2_info.m_position_and_color;
        int v2_tex_coord_index = v2_info.m_tex_coord;
        int v2_normal_index = v2_info.m_normal;

        int material_index = m_mtl_file_info.m_material_name_to_index[material_name];

        MaterialTriangle material_triangle;

        material_triangle.m_triangle.m_v0.m_position = m_obj_file_info.m_vertex_positions_and_colors[v0_pos_and_color_index].first;
        material_triangle.m_triangle.m_v0.m_tex_coords = m_obj_file_info.m_vertex_tex_coords[v0_tex_coord_index];
        material_triangle.m_triangle.m_v0.m_normal = m_obj_file_info.m_vertex_normals[v0_normal_index];
        material_triangle.m_triangle.m_v0.m_color = m_obj_file_info.m_vertex_positions_and_colors[v0_pos_and_color_index].second;

        material_triangle.m_triangle.m_v1.m_position = m_obj_file_info.m_vertex_positions_and_colors[v1_pos_and_color_index].first;
        material_triangle.m_triangle.m_v1.m_tex_coords = m_obj_file_info.m_vertex_tex_coords[v1_tex_coord_index];
        material_triangle.m_triangle.m_v1.m_normal = m_obj_file_info.m_vertex_normals[v1_normal_index];
        material_triangle.m_triangle.m_v1.m_color = m_obj_file_info.m_vertex_positions_and_colors[v1_pos_and_color_index].second;

        material_triangle.m_triangle.m_v2.m_position = m_obj_file_info.m_vertex_positions_and_colors[v2_pos_and_color_index].first;
        material_triangle.m_triangle.m_v2.m_tex_coords = m_obj_file_info.m_vertex_tex_coords[v2_tex_coord_index];
        material_triangle.m_triangle.m_v2.m_normal = m_obj_file_info.m_vertex_normals[v2_normal_index];
        material_triangle.m_triangle.m_v2.m_color = m_obj_file_info.m_vertex_positions_and_colors[v2_pos_and_color_index].second;

        material_triangle.m_material = m_mtl_file_info.m_materials[material_index];

        m_material_triangles.push_back(material_triangle);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
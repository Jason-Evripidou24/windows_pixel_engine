// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <fstream>
#include <sstream>
#include <string>
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
/*
-   OBJ file
    -   v      (vertex position)
    -   vt     (vertex texture coordinates)
    -   vn     (vertex normal)
    -   f      (face consisting of three vertices)
    -   usemtl
    -   mtllib

-   MTL file
    -   newmtl
    -   Kd (diffuse colour)
    -   Ka (ambient colour)
    -   Ks (specular colour)
    -   Ns (shininess)
    -   map_Kd (diffuse texture)
    -   d / Tr (opacity)
*/
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::pair<Math::Vec4_f, Math::Vec4_f> parseVertexPositionAndColor(std::stringstream& stream)
{
    float x;
    float y;
    float z;

    // Invalid position coordinate.
    if(!(stream >> x >> y >> z))
    {
        return std::pair<Math::Vec4_f, Math::Vec4_f>
        (
            Math::Vec4_f(0.0f, 0.0f, 0.0f, 1.0f),
            Math::Vec4_f(1.0f, 1.0f, 1.0f, 1.0f)
        );
    }

    float r;
    float g;
    float b;

    if(!(stream >> r >> g >> b))
    {
        return std::pair<Math::Vec4_f, Math::Vec4_f>
        (
            Math::Vec4_f(x, y, z, 1.0f),
            Math::Vec4_f(1.0f, 1.0f, 1.0f, 1.0f)
        );
    }

    float a;

    if(!(stream >> a))
    {
        return std::pair<Math::Vec4_f, Math::Vec4_f>
        (
            Math::Vec4_f(x, y, z, 1.0f),
            Math::Vec4_f(1.0f, r, g, b)
        );
    }

    return std::pair<Math::Vec4_f, Math::Vec4_f>
    (
        Math::Vec4_f(x, y, z, 1.0f),
        Math::Vec4_f(a, r, g, b)
    );
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Vec2_f parseVertexTexCoord(std::stringstream& stream)
{
    float u = 0.0f;
    float v = 0.0f;

    // Invalid texture coordinate.
    if(!(stream >> u >> v)) { return Math::Vec2_f(0.0f, 0.0f); }

    return Math::Vec2_f(u, v);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Vec3_f parseVertexNormal(std::stringstream& stream)
{
    float x;
    float y;
    float z;

    // Invalid normal direction.
    if(!(stream >> x >> y >> z)) { return Math::Vec3_f(0.0f, 1.0f, 0.0f); }

    return Math::Vec3_f(x, y, z);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
struct ObjVertexInfo
{
    int m_position_and_color = -1;
    int m_tex_coord          = -1;
    int m_normal             = -1;
};
ObjVertexInfo parseVertexInfo(const std::string& token)
{
    ObjVertexInfo vertex_info{ -1, -1, -1 };

    std::stringstream ss(token);

    std::string value;

    // position
    std::getline(ss, value, '/');
    if(!value.empty())
    {
        vertex_info.m_position_and_color = std::stoi(value) - 1;
    }

    // texcoord
    if(std::getline(ss, value, '/'))
    {
        if(!value.empty())
        {
            vertex_info.m_tex_coord = std::stoi(value) - 1;
        }
    }

    // normal
    if(std::getline(ss, value, '/'))
    {
        if(!value.empty())
        {
            vertex_info.m_normal = std::stoi(value) - 1;
        }
    }

    return vertex_info;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<ObjVertexInfo> parseFace(std::stringstream& stream)
{
    std::vector<ObjVertexInfo> vertices;

    std::string token;

    while(stream >> token)
    {
        vertices.push_back(parseVertexInfo(token));
    }

    return vertices;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<Math::Triangle> createTriangles
(
    const std::vector<ObjVertexInfo>& face_vertices,
    const std::vector<std::pair<Math::Vec4_f, Math::Vec4_f>>& vertex_positions_and_colors,
    const std::vector<Math::Vec2_f>& vertex_tex_coords,
    const std::vector<Math::Vec3_f>& vertex_normals
)
{
    std::vector<Math::Triangle> new_triangles;

    for(size_t i = 1; i + 1 < face_vertices.size(); i++)
    {
        Math::Triangle new_triangle;

        //-----------------------------------------------------------------------------------------------------------------//
        int v0_pos_index = face_vertices[0].m_position_and_color;
        int v0_pos_tex_coord_index = face_vertices[0].m_tex_coord;
        int v0_normal_index = face_vertices[0].m_normal;
        int v0_color_index = face_vertices[0].m_position_and_color;

        if( (v0_pos_index >= 0) && (v0_pos_index < vertex_positions_and_colors.size()) )
        {
            new_triangle.m_v0.m_position = vertex_positions_and_colors[v0_pos_index].first;
        }
        if( (v0_pos_tex_coord_index >= 0) && (v0_pos_tex_coord_index < vertex_tex_coords.size()) )
        {
            new_triangle.m_v0.m_tex_coords = vertex_tex_coords[v0_pos_tex_coord_index];
        }
        if( (v0_normal_index >= 0) && (v0_normal_index < vertex_normals.size()) )
        {
            new_triangle.m_v0.m_normal = vertex_normals[v0_normal_index];
        }
        if( (v0_color_index >= 0) && (v0_color_index < vertex_positions_and_colors.size()) )
        {
            new_triangle.m_v0.m_color = vertex_positions_and_colors[v0_color_index].second;
        }
        //-----------------------------------------------------------------------------------------------------------------//
        
        //-----------------------------------------------------------------------------------------------------------------//
        int v1_pos_index = face_vertices[i].m_position_and_color;
        int v1_pos_tex_coord_index = face_vertices[i].m_tex_coord;
        int v1_normal_index = face_vertices[i].m_normal;
        int v1_color_index = face_vertices[i].m_position_and_color;

        if( (v1_pos_index >= 0) && (v1_pos_index < vertex_positions_and_colors.size()) )
        {
            new_triangle.m_v1.m_position = vertex_positions_and_colors[v1_pos_index].first;
        }
        if( (v1_pos_tex_coord_index >= 0) && (v1_pos_tex_coord_index < vertex_tex_coords.size()) )
        {
            new_triangle.m_v1.m_tex_coords = vertex_tex_coords[v1_pos_tex_coord_index];
        }
        if( (v1_normal_index >= 0) && (v1_normal_index < vertex_normals.size()) )
        {
            new_triangle.m_v1.m_normal = vertex_normals[v1_normal_index];
        }
        if( (v1_color_index >= 0) && (v1_color_index < vertex_positions_and_colors.size()) )
        {
            new_triangle.m_v1.m_color = vertex_positions_and_colors[v1_color_index].second;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        int v2_pos_index = face_vertices[i + 1].m_position_and_color;
        int v2_pos_tex_coord_index = face_vertices[i + 1].m_tex_coord;
        int v2_normal_index = face_vertices[i + 1].m_normal;
        int v2_color_index = face_vertices[i + 1].m_position_and_color;

        if( (v2_pos_index >= 0) && (v2_pos_index < vertex_positions_and_colors.size()) )
        {
            new_triangle.m_v2.m_position = vertex_positions_and_colors[v2_pos_index].first;
        }
        if( (v2_pos_tex_coord_index >= 0) && (v2_pos_tex_coord_index < vertex_tex_coords.size()) )
        {
            new_triangle.m_v2.m_tex_coords = vertex_tex_coords[v2_pos_tex_coord_index];
        }
        if( (v2_normal_index >= 0) && (v2_normal_index < vertex_normals.size()) )
        {
            new_triangle.m_v2.m_normal = vertex_normals[v2_normal_index];
        }
        if( (v2_color_index >= 0) && (v2_color_index < vertex_positions_and_colors.size()) )
        {
            new_triangle.m_v2.m_color = vertex_positions_and_colors[v2_color_index].second;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        new_triangles.push_back(new_triangle);
    }

    return new_triangles;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Called after mtl file(s) have been loaded.
void Mesh::loadObjFile(const std::string& file_folder, const std::string& filename)
{
    //---------------------------------------------------------------------------------------------------------------------//
    std::vector<std::pair<Math::Vec4_f, Math::Vec4_f>> vertex_positions_and_colors;
    std::vector<Math::Vec2_f> vertex_tex_coords;
    std::vector<Math::Vec3_f> vertex_normals;

    std::ifstream file(file_folder + filename);
    if(!file.is_open()) { return; }
    //---------------------------------------------------------------------------------------------------------------------//

    Mesh::SubMesh curr_sub_mesh;
    curr_sub_mesh.m_triangles.clear();
    curr_sub_mesh.m_material_index = -1;
    
    std::string current_material_name = std::string("NULL");

    std::string line;
    while(std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string prefix;
        ss >> prefix;

        //-----------------------------------------------------------------------------------------------------------------//
        // Comment.
        //-----------------------------------------------------------------------------------------------------------------//
        if(prefix == "#") { continue; }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex position.
        //-----------------------------------------------------------------------------------------------------------------//
        if(prefix == "v")
        {
            vertex_positions_and_colors.push_back(parseVertexPositionAndColor(ss));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex tex coord.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "vt")
        {
            vertex_tex_coords.push_back(parseVertexTexCoord(ss));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex normal.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "vn")
        {
            vertex_normals.push_back(parseVertexNormal(ss));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // New material name to be used with the following triangles.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "usemtl")
        {
            ss >> current_material_name;

            if(curr_sub_mesh.m_triangles.empty() == false)
            {
                m_sub_meshes.push_back(curr_sub_mesh);
            }

            curr_sub_mesh.m_triangles.clear();
            curr_sub_mesh.m_material_index = -1;
            if(m_material_name_to_index.find(current_material_name) != m_material_name_to_index.end())
            {
                curr_sub_mesh.m_material_index = m_material_name_to_index[current_material_name];
            }
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Triangle.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "f")
        {
            std::vector<ObjVertexInfo> face_indices = parseFace(ss);

            std::vector<Math::Triangle> new_triangles = createTriangles
            (
                face_indices,
                vertex_positions_and_colors,
                vertex_tex_coords,
                vertex_normals
            );

            for(const Math::Triangle& new_triangle : new_triangles)
            {
                curr_sub_mesh.m_triangles.push_back(new_triangle);
            }
        }
        //-----------------------------------------------------------------------------------------------------------------//
    }

    if(curr_sub_mesh.m_triangles.empty() == false)
    {
        m_sub_meshes.push_back(curr_sub_mesh);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
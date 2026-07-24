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
ObjFile::ObjVertexInfo parseVertexInfo(const std::string& token)
{
    ObjFile::ObjVertexInfo vertex_info{ -1, -1, -1 };

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
std::vector<ObjFile::ObjVertexInfo> parseFace(std::stringstream& stream)
{
    std::vector<ObjFile::ObjVertexInfo> vertices;

    std::string token;

    while(stream >> token)
    {
        vertices.push_back(parseVertexInfo(token));
    }

    return vertices;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<ObjFile::ObjTriangleInfo> createTriangles(const std::vector<ObjFile::ObjVertexInfo>& face_vertices)
{
    std::vector<ObjFile::ObjTriangleInfo> triangles;

    for(size_t i = 1; i + 1 < face_vertices.size(); i++)
    {
        ObjFile::ObjTriangleInfo triangle_info;
        triangle_info.m_v0 = face_vertices[0];
        triangle_info.m_v1 = face_vertices[i];
        triangle_info.m_v2 = face_vertices[i + 1];
        triangles.push_back(triangle_info);
    }

    return triangles;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void ObjFile::loadObjFile(const std::string& file_folder, const std::string& filename)
{
    //---------------------------------------------------------------------------------------------------------------------//
    m_vertex_positions_and_colors.clear();
    m_vertex_tex_coords.clear();
    m_vertex_normals.clear();

    m_material_triangles.clear();

    std::ifstream file(file_folder + filename);
    if(!file.is_open()) { return; }
    //---------------------------------------------------------------------------------------------------------------------//

    std::string current_material_name = std::string("DEFAULT");

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
            m_vertex_positions_and_colors.push_back(parseVertexPositionAndColor(ss));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex tex coord.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "vt")
        {
            m_vertex_tex_coords.push_back(parseVertexTexCoord(ss));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex normal.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "vn")
        {
            m_vertex_normals.push_back(parseVertexNormal(ss));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // New material name to be used with the following triangles.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "usemtl")
        {
            ss >> current_material_name;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Triangle.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "f")
        {
            std::vector<ObjFile::ObjVertexInfo> face_indices = parseFace(ss);

            std::vector<ObjFile::ObjTriangleInfo> new_triangles = createTriangles(face_indices);

            for(const ObjFile::ObjTriangleInfo& triangle : new_triangles)
            {
                ObjFile::ObjMaterialTriangleInfo material_triangle;
                material_triangle.m_triangle = triangle;
                material_triangle.m_material_name = current_material_name;

                m_material_triangles.push_back(material_triangle);
            }
        }
        //-----------------------------------------------------------------------------------------------------------------//
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
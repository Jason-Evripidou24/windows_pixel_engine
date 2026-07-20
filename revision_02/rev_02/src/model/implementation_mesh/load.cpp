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
Math::Vec4_f parseVertexPosition(std::stringstream& stream)
{
    float x;
    float y;
    float z;

    // Invalid position coordinate.
    if(!(stream >> x >> y >> z)) { return Math::Vec4_f(0.0f, 0.0f, 0.0f, 1.0f); }

    return Math::Vec4_f(x, y, z, 1.0f);
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
struct OBJIndex
{
    int position;
    int texcoord;
    int normal;
};
OBJIndex parseOBJVertex(const std::string& token)
{
    OBJIndex index{ -1, -1, -1 };

    std::stringstream ss(token);

    std::string value;

    // position
    std::getline(ss, value, '/');
    if(!value.empty())
    {
        index.position = std::stoi(value) - 1;
    }

    // texcoord
    if(std::getline(ss, value, '/'))
    {
        if(!value.empty())
        {
            index.texcoord = std::stoi(value) - 1;
        }
    }

    // normal
    if(std::getline(ss, value, '/'))
    {
        if(!value.empty())
        {
            index.normal = std::stoi(value) - 1;
        }
    }

    return index;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<OBJIndex> parseFace(std::stringstream& stream)
{
    std::vector<OBJIndex> indices;

    std::string token;

    while(stream >> token)
    {
        indices.push_back(parseOBJVertex(token));
    }

    return indices;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<Math::Triangle> createTriangles
(
    const std::vector<OBJIndex>& face_indices,
    const std::vector<Math::Vec4_f>& vertex_positions,
    const std::vector<Math::Vec2_f>& vertex_tex_coords,
    const std::vector<Math::Vec3_f>& vertex_normals
)
{
    std::vector<Math::Triangle> triangles;

    for(size_t i = 1; i + 1 < face_indices.size(); i++)
    {
        const OBJIndex& i0 = face_indices[0];
        const OBJIndex& i1 = face_indices[i];
        const OBJIndex& i2 = face_indices[i + 1];

        Math::Vertex vertex0;
        vertex0.m_position = vertex_positions[i0.position];
        vertex0.m_tex_coords = vertex_tex_coords[i0.texcoord];
        vertex0.m_normal = vertex_normals[i0.normal];
        vertex0.m_color = 0xFFFFFFFF; // White default.

        Math::Vertex vertex1;
        vertex1.m_position = vertex_positions[i1.position];
        vertex1.m_tex_coords = vertex_tex_coords[i1.texcoord];
        vertex1.m_normal = vertex_normals[i1.normal];
        vertex1.m_color = 0xFFFFFFFF; // White default.

        Math::Vertex vertex2;
        vertex2.m_position = vertex_positions[i2.position];
        vertex2.m_tex_coords = vertex_tex_coords[i2.texcoord];
        vertex2.m_normal = vertex_normals[i2.normal];
        vertex2.m_color = 0xFFFFFFFF; // White default.

        triangles.push_back(Math::Triangle(vertex0, vertex1, vertex2));
    }

    return triangles;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mesh Mesh::loadObjFile(const std::string& file_folder, const std::string& filename)
{
    //---------------------------------------------------------------------------------------------------------------------//
    Mesh mesh;

    std::vector<Math::Triangle> triangles;
    std::vector<Material> materials;

    std::vector<int> triangles_material_index;
    
    std::ifstream file(file_folder + filename);
    if(!file.is_open()) { return mesh; }
    //---------------------------------------------------------------------------------------------------------------------//

    std::vector<Math::Vec4_f> vertex_positions;
    std::vector<Math::Vec2_f> vertex_tex_coords;
    std::vector<Math::Vec3_f> vertex_normals;

    std::string current_material_name;
    std::unordered_map<std::string, int> material_names_to_indexes;

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
            vertex_positions.push_back(parseVertexPosition(ss));
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
        // New material library.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "mtllib")
        {
            std::string mtl_filename;
            ss >> mtl_filename;

            std::vector<Material> new_materials = Mesh::loadMtlFile(file_folder, mtl_filename);

            for(const Material& material : new_materials)
            {
                const std::string& material_name = material.m_name;
                if(material_names_to_indexes.find(material_name) != material_names_to_indexes.end()) { continue; }

                materials.push_back(material);
                material_names_to_indexes[material_name] = static_cast<int>(materials.size()) - 1;
            }
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
            std::vector<OBJIndex> face_indices = parseFace(ss);

            std::vector<Math::Triangle> new_triangles = createTriangles
            (
                face_indices,
                vertex_positions,
                vertex_tex_coords,
                vertex_normals
            );

            for(const Math::Triangle& triangle : new_triangles)
            {
                triangles.push_back(triangle);

                if(material_names_to_indexes.find(current_material_name) != material_names_to_indexes.end())
                {
                    triangles_material_index.push_back(material_names_to_indexes[current_material_name]);
                }
                else
                {
                    triangles_material_index.push_back(0); // In loadMtlFile we set the default/invalid material at index 0.
                }
            }
        }
        //-----------------------------------------------------------------------------------------------------------------//
    }

    mesh.m_triangles = triangles;
    mesh.m_materials = materials;

    mesh.m_triangles_material_index = triangles_material_index;

    return mesh;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
            float x;
            float y;
            float z;

            ss >> x >> y >> z;

            vertex_positions.push_back(Math::Vec4_f(x, y, z, 1.0f));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex tex coord.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "vt")
        {
            float x;
            float y;

            ss >> x >> y;

            vertex_tex_coords.push_back(Math::Vec2_f(x, y));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex normal.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "vn")
        {
            float x;
            float y;
            float z;

            ss >> x >> y >> z;

            vertex_normals.push_back(Math::Vec3_f(x, y, z));
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
                material_names_to_indexes[material_name] = materials.size() - 1;
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
            std::string s0;
            std::string s1;
            std::string s2;

            ss >> s0 >> s1 >> s2;

            OBJIndex i0 = parseOBJVertex(s0);
            OBJIndex i1 = parseOBJVertex(s1);
            OBJIndex i2 = parseOBJVertex(s2);

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

            Math::Triangle triangle(vertex0, vertex1, vertex2);
            triangles.push_back(triangle);

            if(material_names_to_indexes.find(current_material_name) != material_names_to_indexes.end())
            {
                triangles_material_index.push_back(material_names_to_indexes[current_material_name]);
            }
            else
            {
                triangles_material_index.push_back(-1);
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


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<Material> Mesh::loadMtlFile(const std::string& file_folder, const std::string& filename)
{
    //---------------------------------------------------------------------------------------------------------------------//
    std::vector<Material> materials;

    std::ifstream file(file_folder + filename);
    if(!file.is_open()) { return materials; }
    //---------------------------------------------------------------------------------------------------------------------//

    Material curr_material = Material();

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
        // New material.
        //-----------------------------------------------------------------------------------------------------------------//
        if(prefix == "newmtl")
        {
            if(curr_material.m_name.empty() == false) { materials.push_back(curr_material); }

            curr_material = Material();
            ss >> curr_material.m_name;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Diffuse colour.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "Kd")
        {
            float r;
            float g;
            float b;

            ss >> r >> g >> b;

            curr_material.m_diffuse = Math::Vec3_f(r, g, b);
        }
        //-----------------------------------------------------------------------------------------------------------------//
    }

    if(curr_material.m_name.empty() == false) { materials.push_back(curr_material); }

    return materials;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
#include "../../math/vec4_f.hpp"
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
int parseOBJIndex(const std::string& token)
{
    size_t slash = token.find('/');

    if(slash != std::string::npos)
    {
        return std::stoi(token.substr(0, slash));
    }

    return std::stoi(token);
}

Mesh Mesh::loadFileObj(const std::string& filename)
{
    Mesh mesh;

    std::ifstream file(filename);
    if(!file.is_open()) { return mesh; }

    std::vector<Math::Vertex> vertices;
    std::vector<Math::Vec4_f> vertices_positions;
    std::vector<Math::Vec3_i> triangles_indices;

    std::string line;

    while(std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string prefix;
        ss >> prefix;

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex position.
        //-----------------------------------------------------------------------------------------------------------------//
        if(prefix == "v")
        {
            float x;
            float y;
            float z;

            ss >> x >> y >> z;

            vertices_positions.push_back(Math::Vec4_f(x, y, z, 1.0f));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Triangle face.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "f")
        {
            std::string a;
            std::string b;
            std::string c;
            ss >> a >> b >> c;

            // OBJ indices start at 1
            int i0 = parseOBJIndex(a)-1;
            int i1 = parseOBJIndex(b)-1;
            int i2 = parseOBJIndex(c)-1;

            Math::Vec3_i triangle_indices(i0, i1, i2);
            triangles_indices.push_back(triangle_indices);
        }
        //-----------------------------------------------------------------------------------------------------------------//
    }


    for(int i = 0; i < vertices_positions.size(); i++)
    {
        Math::Vertex new_vert;
        new_vert.m_position = vertices_positions[i];
        new_vert.m_color = 0xFF000000; // Black default.
        vertices.push_back(new_vert);
    }

    mesh.m_vertices = vertices;
    mesh.m_triangles_indices = triangles_indices;
    return mesh;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
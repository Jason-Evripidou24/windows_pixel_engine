// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../obj_file_parser.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::pair<Math::Core::Vec4_f, Math::Core::Vec4_f> ObjFileParser::parseVertexPositionAndColor
(
    std::stringstream& line_string_stream
)
{
    float x;
    float y;
    float z;

    // Invalid position coordinate.
    if( !(line_string_stream >> x >> y >> z) )
    {
        return std::pair<Math::Core::Vec4_f, Math::Core::Vec4_f>
        (
            Math::Core::Vec4_f(0.0f, 0.0f, 0.0f, 1.0f),
            Math::Core::Vec4_f(1.0f, 1.0f, 1.0f, 1.0f)
        );
    }

    float r;
    float g;
    float b;

    if( !(line_string_stream >> r >> g >> b) )
    {
        return std::pair<Math::Core::Vec4_f, Math::Core::Vec4_f>
        (
            Math::Core::Vec4_f(x, y, z, 1.0f),
            Math::Core::Vec4_f(1.0f, 1.0f, 1.0f, 1.0f)
        );
    }

    float a;

    if( !(line_string_stream >> a) )
    {
        return std::pair<Math::Core::Vec4_f, Math::Core::Vec4_f>
        (
            Math::Core::Vec4_f(x, y, z, 1.0f),
            Math::Core::Vec4_f(1.0f, r, g, b)
        );
    }

    return std::pair<Math::Core::Vec4_f, Math::Core::Vec4_f>
    (
        Math::Core::Vec4_f(x, y, z, 1.0f),
        Math::Core::Vec4_f(a, r, g, b)
    );
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Core::Vec2_f ObjFileParser::parseVertexTexCoord(std::stringstream& line_string_stream)
{
    float u = 0.0f;
    float v = 0.0f;

    // Invalid texture coordinate.
    if( !(line_string_stream >> u >> v) ) { return Math::Core::Vec2_f(0.0f, 0.0f); }

    return Math::Core::Vec2_f(u, v);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Core::Vec3_f ObjFileParser::parseVertexNormal(std::stringstream& line_string_stream)
{
    float x;
    float y;
    float z;

    // Invalid normal direction.
    if( !(line_string_stream >> x >> y >> z) ) { return Math::Core::Vec3_f(0.0f, 1.0f, 0.0f); }

    return Math::Core::Vec3_f(x, y, z);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
ObjFileParser::ObjVertexInfo ObjFileParser::parseVertexInfo(const std::string& token)
{
    ObjFileParser::ObjVertexInfo vertex_info{ 0, 0, 0 };

    std::stringstream ss(token);

    std::string value;

    // position
    std::getline(ss, value, '/');
    if(!value.empty())
    {
        vertex_info.m_position_and_color = std::stoi(value);
    }

    // texcoord
    std::getline(ss, value, '/');
    if(!value.empty())
    {
        vertex_info.m_tex_coord = std::stoi(value);
    }

    // normal
    std::getline(ss, value, '/');
    if(!value.empty())
    {
        vertex_info.m_normal = std::stoi(value);
    }

    return vertex_info;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<ObjFileParser::ObjVertexInfo> ObjFileParser::parsePolygonInfo(std::stringstream& line_string_stream)
{
    std::vector<ObjFileParser::ObjVertexInfo> polygon_info;

    std::string token;

    while(line_string_stream >> token)
    {
        polygon_info.push_back(ObjFileParser::parseVertexInfo(token));
    }

    return polygon_info;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Geometry::Polygon ObjFileParser::createPolygon
(
    const std::vector<ObjFileParser::ObjVertexInfo>& polygon_vertices_info,
    const std::vector<std::pair<Math::Core::Vec4_f, Math::Core::Vec4_f>>& vertex_positions_and_colors,
    const std::vector<Math::Core::Vec2_f>& vertex_tex_coords,
    const std::vector<Math::Core::Vec3_f>& vertex_normals
)
{
    Math::Geometry::Polygon new_polygon;

    for(size_t i = 0; i < polygon_vertices_info.size(); i++)
    {
        //-----------------------------------------------------------------------------------------------------------------//
        Math::Geometry::Vertex new_vertex;

        int v_pos_index = polygon_vertices_info[i].m_position_and_color;
        int v_tex_coord_index = polygon_vertices_info[i].m_tex_coord;
        int v_normal_index = polygon_vertices_info[i].m_normal;
        int v_color_index = polygon_vertices_info[i].m_position_and_color;

        if( (v_pos_index > 0) && (v_pos_index <= vertex_positions_and_colors.size()) )
        {
            new_vertex.m_position = vertex_positions_and_colors[v_pos_index - 1].first;
        }
        else if( (v_pos_index < 0) && (v_pos_index + vertex_positions_and_colors.size() >= 0) )
        {
            new_vertex.m_position = vertex_positions_and_colors[vertex_positions_and_colors.size() + v_pos_index].first;
        }

        if( (v_tex_coord_index > 0) && (v_tex_coord_index <= vertex_tex_coords.size()) )
        {
            new_vertex.m_tex_coords = vertex_tex_coords[v_tex_coord_index - 1];
        }
        else if( (v_tex_coord_index < 0) && (v_tex_coord_index + vertex_tex_coords.size() >= 0) )
        {
            new_vertex.m_tex_coords = vertex_tex_coords[vertex_tex_coords.size() + v_tex_coord_index];
        }

        if( (v_normal_index > 0) && (v_normal_index <= vertex_normals.size()) )
        {
            new_vertex.m_normal = vertex_normals[v_normal_index - 1];
        }
        else if( (v_normal_index < 0) && (v_normal_index + vertex_normals.size() >= 0) )
        {
            new_vertex.m_normal = vertex_normals[vertex_normals.size() + v_normal_index];
        }

        if( (v_color_index > 0) && (v_color_index <= vertex_positions_and_colors.size()) )
        {
            new_vertex.m_color = vertex_positions_and_colors[v_color_index - 1].second;
        }
        else if( (v_color_index < 0) && (v_color_index + vertex_positions_and_colors.size() >= 0) )
        {
            new_vertex.m_color = vertex_positions_and_colors[vertex_positions_and_colors.size() + v_color_index].second;
        }

        new_polygon.addVertex(new_vertex);
        //-----------------------------------------------------------------------------------------------------------------//
    }

    return new_polygon;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<MeshWireframe> ObjFileParser::loadMeshWireframes
(
    const std::string& file_folder,
    const std::string& filename
)
{
    std::vector<MeshWireframe> mesh_wireframes;

    //---------------------------------------------------------------------------------------------------------------------//
    std::vector<std::pair<Math::Core::Vec4_f, Math::Core::Vec4_f>> vertex_positions_and_colors;
    std::vector<Math::Core::Vec2_f> vertex_tex_coords;
    std::vector<Math::Core::Vec3_f> vertex_normals;

    std::ifstream file(file_folder + filename);
    if(!file.is_open()) { return mesh_wireframes; }
    //---------------------------------------------------------------------------------------------------------------------//

    MeshWireframe curr_mesh_wireframe;
    curr_mesh_wireframe.m_wireframe.clear();
    curr_mesh_wireframe.m_wireframe_material_name.clear();

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
            vertex_positions_and_colors.push_back(ObjFileParser::parseVertexPositionAndColor(ss));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex tex coord.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "vt")
        {
            vertex_tex_coords.push_back(ObjFileParser::parseVertexTexCoord(ss));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Vertex normal.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "vn")
        {
            vertex_normals.push_back(ObjFileParser::parseVertexNormal(ss));
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // New material name to be used with the following triangles.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "usemtl")
        {
            if(curr_mesh_wireframe.m_wireframe.m_num_polygons > 0)
            {
                mesh_wireframes.push_back(curr_mesh_wireframe);
            }

            curr_mesh_wireframe.m_wireframe.clear();
            curr_mesh_wireframe.m_wireframe_material_name.clear();
            ss >> curr_mesh_wireframe.m_wireframe_material_name;
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Triangle.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "f")
        {
            std::vector<ObjFileParser::ObjVertexInfo> face_indices = ObjFileParser::parsePolygonInfo(ss);

            Math::Geometry::Polygon new_polygon = ObjFileParser::createPolygon
            (
                face_indices,
                vertex_positions_and_colors,
                vertex_tex_coords,
                vertex_normals
            );

            curr_mesh_wireframe.m_wireframe.addPolygon(new_polygon);
        }
        //-----------------------------------------------------------------------------------------------------------------//
    }

    if(curr_mesh_wireframe.m_wireframe.m_num_polygons > 0)
    {
        mesh_wireframes.push_back(curr_mesh_wireframe);
    }

    return mesh_wireframes;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
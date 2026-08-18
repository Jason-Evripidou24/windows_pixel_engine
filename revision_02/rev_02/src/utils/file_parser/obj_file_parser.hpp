// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef OBJ_FILE_PARSER_HPP
#define OBJ_FILE_PARSER_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


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
#include "../../math/core/math_core.hpp"
#include "../../math/geometry/math_geometry.hpp"

#include "../../model/mesh/mesh_polygon.hpp"
#include "../../model/mesh/mesh_wireframe.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
struct ObjFileParser
{
    static std::pair<Math::Core::Vec4_f, Math::Core::Vec4_f> parseVertexPositionAndColor
    (
        std::stringstream& line_string_stream
    );

    static Math::Core::Vec2_f parseVertexTexCoord(std::stringstream& line_string_stream);

    static Math::Core::Vec3_f parseVertexNormal(std::stringstream& line_string_stream);

    struct ObjVertexInfo
    {
        int m_position_and_color = 0;
        int m_tex_coord          = 0;
        int m_normal             = 0;
    };
    static ObjVertexInfo parseVertexInfo(const std::string& token);

    static std::vector<ObjFileParser::ObjVertexInfo> parsePolygonInfo(std::stringstream& line_string_stream);

    static Math::Geometry::Polygon createPolygon
    (
        const std::vector<ObjFileParser::ObjVertexInfo>&                      polygon_vertices_info,
        const std::vector<std::pair<Math::Core::Vec4_f, Math::Core::Vec4_f>>& vertex_positions_and_colors,
        const std::vector<Math::Core::Vec2_f>&                                vertex_tex_coords,
        const std::vector<Math::Core::Vec3_f>&                                vertex_normals
    );

    //static std::vector<MeshWireframe> loadMeshWireframes(const std::string& file_folder, const std::string& filename);

    static std::vector<MeshPolygon> loadMeshPolygons(const std::string& file_folder, const std::string& filename);
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
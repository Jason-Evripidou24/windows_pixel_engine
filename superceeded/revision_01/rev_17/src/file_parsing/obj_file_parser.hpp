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
#include "../math/math.hpp"
#include "../geometry/polygon.hpp"
#include "../geometry/wireframe.hpp"

#include "../material/multi_wireframe_and_material_names.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
struct ObjFileParser
{
    static std::pair<Math::Vec4_f, Math::Vec4_f> parseVertexPositionAndColor(std::stringstream& line_string_stream);

    static Math::Vec2_f parseVertexTexCoord(std::stringstream& line_string_stream);

    static Math::Vec3_f parseVertexNormal(std::stringstream& line_string_stream);

    struct ObjVertexInfo
    {
        int m_position_and_color = 0;
        int m_tex_coord          = 0;
        int m_normal             = 0;
    };
    static ObjVertexInfo parseVertexInfo(const std::string& token);

    static std::vector<ObjFileParser::ObjVertexInfo> parsePolygonInfo(std::stringstream& line_string_stream);

    static Geometry::Polygon createPolygon
    (
        const std::vector<ObjFileParser::ObjVertexInfo>&          polygon_vertices_info,
        const std::vector<std::pair<Math::Vec4_f, Math::Vec4_f>>& vertex_positions_and_colors,
        const std::vector<Math::Vec2_f>&                          vertex_tex_coords,
        const std::vector<Math::Vec3_f>&                          vertex_normals
    );

    static Geometry::MultiWireframe loadMultiWireframe(const std::string& file_folder, const std::string& filename);

    static MultiWireframeAndMaterialNames loadMultiWireframeAndMaterialNames
    (
        const std::string& file_folder,
        const std::string& filename
    );
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
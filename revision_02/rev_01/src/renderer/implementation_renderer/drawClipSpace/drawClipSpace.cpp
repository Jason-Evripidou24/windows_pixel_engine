// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cmath>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../../renderer.hpp"

#include "../../../math/core/math_core.hpp"
#include "../../../math/geometry/math_geometry.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawClipSpacePolygon
(
    std::shared_ptr<Backbuffer>    target     ,
    const Math::Geometry::Polygon& polygon    ,
    std::shared_ptr<Material>      material   ,
    const bool                     draw_filled
)
{
    Math::Geometry::Polygon polygon_clipped;
    Math::Geometry::Polygon buffer = polygon;

    Math::Geometry::clipPolygonAgainstPlaneMinXClipSpace(polygon_clipped, buffer);
    std::swap(buffer, polygon_clipped);
    Math::Geometry::clipPolygonAgainstPlaneMaxXClipSpace(polygon_clipped, buffer);
    std::swap(buffer, polygon_clipped);
    Math::Geometry::clipPolygonAgainstPlaneMinYClipSpace(polygon_clipped, buffer);
    std::swap(buffer, polygon_clipped);
    Math::Geometry::clipPolygonAgainstPlaneMaxYClipSpace(polygon_clipped, buffer);
    std::swap(buffer, polygon_clipped);
    Math::Geometry::clipPolygonAgainstPlaneMinZClipSpace(polygon_clipped, buffer);
    std::swap(buffer, polygon_clipped);
    Math::Geometry::clipPolygonAgainstPlaneMaxZClipSpace(polygon_clipped, buffer);

    polygon_clipped.perspectiveDivide();

    for(size_t i = 0; i < polygon_clipped.m_num_vertices; i++)
    {
        if( std::abs(polygon_clipped.m_vertices[i].m_position.m_data[3]) < 0.0001f )
        {
            polygon_clipped.clear();
            break;
        }
    }
    if(polygon_clipped.m_num_vertices < 3) { return; }

    this->sendNDCSpacePolygonToTileRenderers(target, polygon_clipped, material, draw_filled);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
#include "../../tile_renderer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void TileRenderer::drawNDCSpacePolygon
(
    Backbuffer*                    target     ,
    const Math::Geometry::Polygon* polygon    ,
    const Material*                material   ,
    const bool                     draw_filled
)
{
    if(draw_filled == true)
    {
        this->drawNDCSpacePolygonFill(target, polygon, material);
    }
    else
    {
        this->drawNDCSpacePolygonWireframe(target, polygon, material);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void TileRenderer::drawNDCSpacePolygonFill
(
    Backbuffer*                    target  ,
    const Math::Geometry::Polygon* polygon ,
    const Material*                material
)
{
    size_t num_vertices = polygon->m_num_vertices;
    if(num_vertices < 3) { return; }

    const Math::Geometry::Vertex* v0 = &(polygon->m_vertices[0]);
    for(size_t i = 1; i < num_vertices - 1; i++)
    {
        const Math::Geometry::Vertex* v1 = &(polygon->m_vertices[i]);
        const Math::Geometry::Vertex* v2 = &(polygon->m_vertices[i + 1]);
        this->drawNDCSpaceTriangleFill(target, v0, v1, v2, material);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void TileRenderer::drawNDCSpacePolygonWireframe
(
    Backbuffer*                    target  ,
    const Math::Geometry::Polygon* polygon ,
    const Material*                material
)
{
    size_t num_vertices = polygon->m_num_vertices;
    if(num_vertices < 3) { return; }

    const Math::Geometry::Vertex* v0 = &(polygon->m_vertices[0]);
    for(size_t i = 1; i < num_vertices - 1; i++)
    {
        const Math::Geometry::Vertex* v1 = &(polygon->m_vertices[i]);
        const Math::Geometry::Vertex* v2 = &(polygon->m_vertices[i + 1]);
        this->drawNDCSpaceTriangleWireframe(target, v0, v1, v2, material);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
#include "../math_geometry.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMinXClipSpace
(
    Math::Geometry::Polygon&       output ,
    const Math::Geometry::Polygon& polygon
)
{
    output.clear();

    size_t polygon_num_vertices = polygon.m_num_vertices;
    if(polygon_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon_num_vertices - 1) % polygon_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMinXClipSpace(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMinXClipSpace(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinXClipSpace(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinXClipSpace(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMaxXClipSpace
(
    Math::Geometry::Polygon&       output ,
    const Math::Geometry::Polygon& polygon
)
{
    output.clear();

    size_t polygon_num_vertices = polygon.m_num_vertices;
    if(polygon_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon_num_vertices - 1) % polygon_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMaxXClipSpace(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMaxXClipSpace(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxXClipSpace(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxXClipSpace(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMinYClipSpace
(
    Math::Geometry::Polygon&       output ,
    const Math::Geometry::Polygon& polygon
)
{
    output.clear();

    size_t polygon_num_vertices = polygon.m_num_vertices;
    if(polygon_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon_num_vertices - 1) % polygon_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMinYClipSpace(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMinYClipSpace(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinYClipSpace(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinYClipSpace(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMaxYClipSpace
(
    Math::Geometry::Polygon&       output ,
    const Math::Geometry::Polygon& polygon
)
{
    output.clear();

    size_t polygon_num_vertices = polygon.m_num_vertices;
    if(polygon_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon_num_vertices - 1) % polygon_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMaxYClipSpace(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMaxYClipSpace(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxYClipSpace(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxYClipSpace(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMinZClipSpace
(
    Math::Geometry::Polygon&       output ,
    const Math::Geometry::Polygon& polygon
)
{
    output.clear();

    size_t polygon_num_vertices = polygon.m_num_vertices;
    if(polygon_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon_num_vertices - 1) % polygon_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMinZClipSpace(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMinZClipSpace(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinZClipSpace(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinZClipSpace(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMaxZClipSpace
(
    Math::Geometry::Polygon&       output ,
    const Math::Geometry::Polygon& polygon
)
{
    output.clear();

    size_t polygon_num_vertices = polygon.m_num_vertices;
    if(polygon_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon_num_vertices - 1) % polygon_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMaxZClipSpace(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMaxZClipSpace(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxZClipSpace(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxZClipSpace(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Same Module.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../math_geometry.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMinX(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon)
{
    output.clear();

    if(polygon.m_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon.m_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon.m_num_vertices - 1) % polygon.m_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMinX(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMinX(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinX(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinX(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMaxX(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon)
{
    output.clear();

    if(polygon.m_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon.m_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon.m_num_vertices - 1) % polygon.m_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMaxX(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMaxX(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxX(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxX(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMinY(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon)
{
    output.clear();

    if(polygon.m_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon.m_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon.m_num_vertices - 1) % polygon.m_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMinY(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMinY(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinY(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinY(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMaxY(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon)
{
    output.clear();

    if(polygon.m_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon.m_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon.m_num_vertices - 1) % polygon.m_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMaxY(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMaxY(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxY(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxY(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMinZ(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon)
{
    output.clear();

    if(polygon.m_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon.m_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon.m_num_vertices - 1) % polygon.m_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMinZ(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMinZ(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinZ(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMinZ(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::Geometry::clipPolygonAgainstPlaneMaxZ(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon)
{
    output.clear();

    if(polygon.m_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon.m_num_vertices; i++)
    {
        const Math::Geometry::Vertex& current  = polygon.m_vertices[i];
        const Math::Geometry::Vertex& previous = polygon.m_vertices[(i + polygon.m_num_vertices - 1) % polygon.m_num_vertices];

        bool current_inside = Math::Geometry::checkVertexInsidePlaneMaxZ(current);
        bool previous_inside = Math::Geometry::checkVertexInsidePlaneMaxZ(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxZ(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::Geometry::lineSegmentIntersectionWithPlaneMaxZ(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
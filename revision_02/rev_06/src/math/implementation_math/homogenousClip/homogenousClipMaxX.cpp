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
#include "../../math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Vertex is in Homogenous Space.
float Math::getVertexDistanceToPlaneMaxX(const Math::Vertex& v)
{
    // x - w
    return v.m_position.m_data[0] - v.m_position.m_data[3];
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Vertex is in Homogenous Space.
bool Math::checkVertexInsidePlaneMaxX(const Math::Vertex& v)
{
    // (x <= w) => (x - w <= 0)
    return Math::getVertexDistanceToPlaneMaxX(v) <= 0.0f;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Vertex Math::lineIntersectionWithPlaneMaxX(const Math::Vertex& start, const Math::Vertex& end)
{
    float d0 = Math::getVertexDistanceToPlaneMaxX(start);
    float d1 = Math::getVertexDistanceToPlaneMaxX(end);

    float t = d0 / (d0 - d1);

    Math::Vertex result;
    Math::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::clipPolygonAgainstPlaneMaxX(Math::Polygon& output, const Math::Polygon& polygon)
{
    output.clear();

    if(polygon.m_num_vertices == 0) { return; }

    for(size_t i = 0; i < polygon.m_num_vertices; i++)
    {
        const Math::Vertex& current  = polygon.m_vertices[i];
        const Math::Vertex& previous = polygon.m_vertices[(i + polygon.m_num_vertices - 1) % polygon.m_num_vertices];

        bool current_inside = Math::checkVertexInsidePlaneMaxX(current);
        bool previous_inside = Math::checkVertexInsidePlaneMaxX(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.addVertex(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.addVertex( Math::lineIntersectionWithPlaneMaxX(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.addVertex( Math::lineIntersectionWithPlaneMaxX(previous, current) );
            output.addVertex(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
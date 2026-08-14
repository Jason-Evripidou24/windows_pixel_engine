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
#include "../math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Vertex is in Homogenous Space.
float Math::getVertexDistanceToPlaneMinY(const Math::Vertex& v)
{
    // y + w
    return v.m_position.m_data[1] + v.m_position.m_data[3];
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Vertex is in Homogenous Space.
bool Math::checkVertexInsidePlaneMinY(const Math::Vertex& v)
{
    // (y >= -w) => (y + w >= 0)
    return Math::getVertexDistanceToPlaneMinY(v) >= 0.0f;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Vertex Math::lineIntersectionWithPlaneMinY(const Math::Vertex& start, const Math::Vertex& end)
{
    float d0 = Math::getVertexDistanceToPlaneMinY(start);
    float d1 = Math::getVertexDistanceToPlaneMinY(end);

    float t = d0 / (d0 - d1);

    Math::Vertex result;
    Math::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<Math::Vertex> Math::clipPolygonAgainstPlaneMinY(std::vector<Math::Vertex>& polygon)
{
    std::vector<Math::Vertex> clipped_polygon;
    if(polygon.empty() == true) { return clipped_polygon; }

    for(size_t i = 0; i < polygon.size(); i++)
    {
        const Math::Vertex& current  = polygon[i];
        const Math::Vertex& previous = polygon[(i + polygon.size() - 1) % polygon.size()];

        bool current_inside = Math::checkVertexInsidePlaneMinY(current);
        bool previous_inside = Math::checkVertexInsidePlaneMinY(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            clipped_polygon.push_back(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            clipped_polygon.push_back( Math::lineIntersectionWithPlaneMinY(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            clipped_polygon.push_back( Math::lineIntersectionWithPlaneMinY(previous, current) );
            clipped_polygon.push_back(current);
        }
    }

    return clipped_polygon;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
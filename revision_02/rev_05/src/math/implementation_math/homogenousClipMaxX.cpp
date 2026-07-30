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
void Math::clipPolygonAgainstPlaneMaxX(std::vector<Math::Vertex>& output, const std::vector<Math::Vertex>& polygon)
{
    output.clear();

    if(polygon.empty() == true) { return; }

    for(size_t i = 0; i < polygon.size(); i++)
    {
        const Math::Vertex& current  = polygon[i];
        const Math::Vertex& previous = polygon[(i + polygon.size() - 1) % polygon.size()];

        bool current_inside = Math::checkVertexInsidePlaneMaxX(current);
        bool previous_inside = Math::checkVertexInsidePlaneMaxX(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.push_back(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.push_back( Math::lineIntersectionWithPlaneMaxX(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.push_back( Math::lineIntersectionWithPlaneMaxX(previous, current) );
            output.push_back(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
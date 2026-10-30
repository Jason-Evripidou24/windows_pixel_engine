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
float Math::getVertexDistanceToPlaneMinX(const Math::Vertex& v)
{
    // x + w
    return v.m_position.m_data[0] + v.m_position.m_data[3];
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Vertex is in Homogenous Space.
bool Math::checkVertexInsidePlaneMinX(const Math::Vertex& v)
{
    // (x >= -w) => (x + w >= 0)
    return Math::getVertexDistanceToPlaneMinX(v) >= 0.0f;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Vertex Math::lineIntersectionWithPlaneMinX(const Math::Vertex& start, const Math::Vertex& end)
{
    float d0 = Math::getVertexDistanceToPlaneMinX(start);
    float d1 = Math::getVertexDistanceToPlaneMinX(end);

    float t = d0 / (d0 - d1);

    Math::Vertex result;
    Math::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Math::clipPolygonAgainstPlaneMinX(std::vector<Math::Vertex>& output, const std::vector<Math::Vertex>& polygon)
{
    output.clear();

    if(polygon.empty() == true) { return; }

    for(size_t i = 0; i < polygon.size(); i++)
    {
        const Math::Vertex& current  = polygon[i];
        const Math::Vertex& previous = polygon[(i + polygon.size() - 1) % polygon.size()];

        bool current_inside = Math::checkVertexInsidePlaneMinX(current);
        bool previous_inside = Math::checkVertexInsidePlaneMinX(previous);

        if( (current_inside == true) && (previous_inside == true) )
        {
            output.push_back(current);
        }
        else if( (current_inside == false) && (previous_inside == true) )
        {
            output.push_back( Math::lineIntersectionWithPlaneMinX(previous, current) );
        }
        else if( (current_inside == true) && (previous_inside == false) )
        {
            output.push_back( Math::lineIntersectionWithPlaneMinX(previous, current) );
            output.push_back(current);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
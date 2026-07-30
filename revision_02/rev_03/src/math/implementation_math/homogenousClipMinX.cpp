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

// Vertex is in Homogenous Space.
bool Math::checkVertexInsidePlaneMinX(const Math::Vertex& v)
{
    // (x >= -w) => (x + w >= 0)
    return Math::getVertexDistanceToPlaneMinX(v) >= 0.0f;
}

/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Vertex Math::lineIntersectionWithPlaneMinX(const Math::Vertex& start, const Math::Vertex& end)
{
    float d0 = Math::getVertexDistanceToPlaneMinX(start);
    float d1 = Math::getVertexDistanceToPlaneMinX(end);

    float t = d0 / (d0 - d1);

    Math::Vertex result = Math::interpolateVertex(start, end, t);
    return result;
}

// Triangle is in Homogenous Space.
std::vector<Math::Triangle> Math::clipAgainstPlaneMinX(const Math::Triangle& triangle)
{
    std::vector<Math::Triangle> output;

    const Math::Vertex& v0 = triangle.m_v0;
    const Math::Vertex& v1 = triangle.m_v1;
    const Math::Vertex& v2 = triangle.m_v2;

    bool checkInsideV0 = Math::checkVertexInsidePlaneMinX(v0);
    bool checkInsideV1 = Math::checkVertexInsidePlaneMinX(v1);
    bool checkInsideV2 = Math::checkVertexInsidePlaneMinX(v2);

    // Case 1: All vertices are outside.
    if( (checkInsideV0 == false) && (checkInsideV1 == false) && (checkInsideV2 == false) )
    {
        return output;
    }

    // Case 2: All vertices are inside.
    if( (checkInsideV0 == true) && (checkInsideV1 == true) && (checkInsideV2 == true) )
    {
        output.push_back(triangle);
        return output;
    }

    // Case 3: One vertex inside and Two vertices outside, One new triangle is created.
    if( (checkInsideV0 == true) && (checkInsideV1 == false) && (checkInsideV2 == false) )
    {
        const Math::Vertex new_vert_0 = Math::lineIntersectionWithPlaneMinX(v0, v1);
        const Math::Vertex new_vert_1 = Math::lineIntersectionWithPlaneMinX(v0, v2);
        output.push_back(Math::Triangle(v0, new_vert_0, new_vert_1));
        return output;
    }
    if( (checkInsideV0 == false) && (checkInsideV1 == true) && (checkInsideV2 == false) )
    {
        const Math::Vertex new_vert_0 = Math::lineIntersectionWithPlaneMinX(v1, v0);
        const Math::Vertex new_vert_1 = Math::lineIntersectionWithPlaneMinX(v1, v2);
        output.push_back(Math::Triangle(v1, new_vert_0, new_vert_1));
        return output;
    }
    if( (checkInsideV0 == false) && (checkInsideV1 == false) && (checkInsideV2 == true) )
    {
        const Math::Vertex new_vert_0 = Math::lineIntersectionWithPlaneMinX(v2, v0);
        const Math::Vertex new_vert_1 = Math::lineIntersectionWithPlaneMinX(v2, v1);
        output.push_back(Math::Triangle(v2, new_vert_0, new_vert_1));
        return output;
    }

    // Case 4: Two vertices inside and One vertex outside, Two new triangles are created.
    if( (checkInsideV0 == true) && (checkInsideV1 == true) && (checkInsideV2 == false) )
    {
        const Math::Vertex new_vert_0 = Math::lineIntersectionWithPlaneMinX(v0, v2);
        const Math::Vertex new_vert_1 = Math::lineIntersectionWithPlaneMinX(v1, v2);

        output.push_back(Math::Triangle(v0, v1, new_vert_0));
        output.push_back(Math::Triangle(v1, new_vert_1, new_vert_0));
        return output;
    }
    if( (checkInsideV0 == true) && (checkInsideV1 == false) && (checkInsideV2 == true) )
    {
        const Math::Vertex new_vert_0 = Math::lineIntersectionWithPlaneMinX(v0, v1);
        const Math::Vertex new_vert_1 = Math::lineIntersectionWithPlaneMinX(v2, v1);

        output.push_back(Math::Triangle(v0, v2, new_vert_0));
        output.push_back(Math::Triangle(v2, new_vert_1, new_vert_0));
        return output;
    }
    if( (checkInsideV0 == false) && (checkInsideV1 == true) && (checkInsideV2 == true) )
    {
        const Math::Vertex new_vert_0 = Math::lineIntersectionWithPlaneMinX(v1, v0);
        const Math::Vertex new_vert_1 = Math::lineIntersectionWithPlaneMinX(v2, v0);

        output.push_back(Math::Triangle(v1, v2, new_vert_0));
        output.push_back(Math::Triangle(v2, new_vert_1, new_vert_0));
        return output;
    }

    return output; // Should not get here
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
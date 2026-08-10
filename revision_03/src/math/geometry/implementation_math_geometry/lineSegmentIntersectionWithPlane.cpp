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
/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMinX
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMinX(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMinX(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMaxX
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMaxX(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMaxX(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMinY
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMinY(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMinY(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMaxY
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMaxY(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMaxY(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMinZ
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMinZ(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMinZ(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertices are in Homogenous Space.
-   Assumed the line between start and end cross min plane x.
*/
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMaxZ
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMaxZ(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMaxZ(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
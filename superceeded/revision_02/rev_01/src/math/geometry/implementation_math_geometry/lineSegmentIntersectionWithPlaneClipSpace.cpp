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
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMinXClipSpace
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMinXClipSpace(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMinXClipSpace(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMaxXClipSpace
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMaxXClipSpace(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMaxXClipSpace(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMinYClipSpace
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMinYClipSpace(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMinYClipSpace(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMaxYClipSpace
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMaxYClipSpace(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMaxYClipSpace(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMinZClipSpace
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMinZClipSpace(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMinZClipSpace(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Geometry::Vertex Math::Geometry::lineSegmentIntersectionWithPlaneMaxZClipSpace
(
    const Math::Geometry::Vertex& start,
    const Math::Geometry::Vertex& end
)
{
    float d0 = Math::Geometry::getVertexDistanceToPlaneMaxZClipSpace(start);
    float d1 = Math::Geometry::getVertexDistanceToPlaneMaxZClipSpace(end);

    float t = d0 / (d0 - d1);

    Math::Geometry::Vertex result;
    Math::Geometry::interpolateVertex(result, start, end, t);
    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
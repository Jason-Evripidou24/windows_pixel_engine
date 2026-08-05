// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cstdint>
#include <vector>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "polygon.hpp"
#include "wireframe.hpp"

#include "../math/math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Geometry
{
    //---------------------------------------------------------------------------------------------------------------------//
    // World Space collision detection.
    //---------------------------------------------------------------------------------------------------------------------//
    bool checkLineSegmentIntersectsTriangle
    (
        const Math::Vec3_f& line_start_pos,
        const Math::Vec3_f& line_end_pos,
        const Math::Vec3_f& v0_pos,
        const Math::Vec3_f& v1_pos,
        const Math::Vec3_f& v2_pos
    );

    bool checkLineSegmentIntersectsMultiWireframe
    (
        const Math::Vec3_f& line_start_pos,
        const Math::Vec3_f& line_end_pos,
        const Geometry::MultiWireframe& multi_wireframe
    );
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Homogenous Space clipping of polygons.
    //---------------------------------------------------------------------------------------------------------------------//
    void clipPolygonAgainstPlaneMinX(Geometry::Polygon& output, const Geometry::Polygon& polygon);
    void clipPolygonAgainstPlaneMaxX(Geometry::Polygon& output, const Geometry::Polygon& polygon);
    void clipPolygonAgainstPlaneMinY(Geometry::Polygon& output, const Geometry::Polygon& polygon);
    void clipPolygonAgainstPlaneMaxY(Geometry::Polygon& output, const Geometry::Polygon& polygon);
    void clipPolygonAgainstPlaneMinZ(Geometry::Polygon& output, const Geometry::Polygon& polygon);
    void clipPolygonAgainstPlaneMaxZ(Geometry::Polygon& output, const Geometry::Polygon& polygon);
    //---------------------------------------------------------------------------------------------------------------------//

    void transformPolygon(Geometry::Polygon& output, const Geometry::Polygon& polygon, const Math::Mat4_f& matrix);
    void transformWireframe(Geometry::Wireframe& output, const Geometry::Wireframe& wireframe, const Math::Mat4_f& matrix);
    void transformMultiWireframe(Geometry::MultiWireframe& output, const Geometry::MultiWireframe& multi_wireframe, const Math::Mat4_f& matrix);
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
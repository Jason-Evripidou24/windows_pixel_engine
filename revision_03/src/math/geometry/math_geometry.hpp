// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef MATH_GEOMETRY_HPP
#define MATH_GEOMETRY_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   NOTE: Maths in this program is done ROW MAJOR!!
    -   Since we are not using opengl and rendering by our own methods this is easier for us to visualiase mathematically.
*/
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


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
#include "../core/math_core.hpp"
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Same Module.
//-------------------------------------------------------------------------------------------------------------------------//
#include "polygon.hpp"
#include "vertex.hpp"
#include "wireframe.hpp"
#include "multi_wireframe.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Math
{
    namespace Geometry
    {
        //-----------------------------------------------------------------------------------------------------------------//
        // Clipping.
        //-----------------------------------------------------------------------------------------------------------------//
        void clipPolygonAgainstPlaneMinX
        (
            Geometry::Polygon& output,
            const Geometry::Polygon& polygon
        );

        void clipPolygonAgainstPlaneMaxX
        (
            Geometry::Polygon& output,
            const Geometry::Polygon& polygon
        );

        void clipPolygonAgainstPlaneMinY
        (
            Geometry::Polygon& output,
            const Geometry::Polygon& polygon
        );

        void clipPolygonAgainstPlaneMaxY
        (
            Geometry::Polygon& output,
            const Geometry::Polygon& polygon
        );

        void clipPolygonAgainstPlaneMinZ
        (
            Geometry::Polygon& output,
            const Geometry::Polygon& polygon
        );

        void clipPolygonAgainstPlaneMaxZ
        (
            Geometry::Polygon& output,
            const Geometry::Polygon& polygon
        );
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Intersections.
        //-----------------------------------------------------------------------------------------------------------------//
        float getVertexDistanceToPlaneMinX(const Math::Geometry::Vertex& v);
        float getVertexDistanceToPlaneMaxX(const Math::Geometry::Vertex& v);
        float getVertexDistanceToPlaneMinY(const Math::Geometry::Vertex& v);
        float getVertexDistanceToPlaneMaxY(const Math::Geometry::Vertex& v);
        float getVertexDistanceToPlaneMinZ(const Math::Geometry::Vertex& v);
        float getVertexDistanceToPlaneMaxZ(const Math::Geometry::Vertex& v);

        bool checkVertexInsidePlaneMinX(const Math::Geometry::Vertex& v);
        bool checkVertexInsidePlaneMaxX(const Math::Geometry::Vertex& v);
        bool checkVertexInsidePlaneMinY(const Math::Geometry::Vertex& v);
        bool checkVertexInsidePlaneMaxY(const Math::Geometry::Vertex& v);
        bool checkVertexInsidePlaneMinZ(const Math::Geometry::Vertex& v);
        bool checkVertexInsidePlaneMaxZ(const Math::Geometry::Vertex& v);

        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMinX
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );

        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMaxX
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );

        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMinY
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );

        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMaxY
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );

        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMinZ
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );

        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMaxZ
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );

        bool checkLineSegmentIntersectsPlaneX
        (
            const Math::Core::Vec3_f& line_start_pos,
            const Math::Core::Vec3_f& line_end_pos,
            const float plane_x
        );
        bool checkLineSegmentIntersectsPlaneY
        (
            const Math::Core::Vec3_f& line_start_pos,
            const Math::Core::Vec3_f& line_end_pos,
            const float plane_y
        );
        bool checkLineSegmentIntersectsPlaneZ
        (
            const Math::Core::Vec3_f& line_start_pos,
            const Math::Core::Vec3_f& line_end_pos,
            const float plane_z
        );

        bool checkLineSegmentIntersectsTriangle
        (
            const Math::Core::Vec3_f& line_start_pos,
            const Math::Core::Vec3_f& line_end_pos,
            const Math::Core::Vec3_f& v0_pos,
            const Math::Core::Vec3_f& v1_pos,
            const Math::Core::Vec3_f& v2_pos
        );

        bool checkLineSegmentIntersectsWireframe
        (
            const Math::Core::Vec3_f& line_start_pos,
            const Math::Core::Vec3_f& line_end_pos,
            const Math::Geometry::Wireframe& wireframe
        );

        bool checkLineSegmentIntersectsMultiWireframe
        (
            const Math::Core::Vec3_f& line_start_pos,
            const Math::Core::Vec3_f& line_end_pos,
            const Math::Geometry::MultiWireframe& multi_wireframe
        );
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Transformations.
        //-----------------------------------------------------------------------------------------------------------------//
        void transformVertex
        (
            Math::Geometry::Vertex& output,
            const Math::Geometry::Vertex& vertex,
            const Math::Core::Mat4_f& matrix
        );

        void transformPolygon
        (
            Math::Geometry::Polygon& output,
            const Math::Geometry::Polygon& polygon,
            const Math::Core::Mat4_f& matrix
        );

        void transformWireframe
        (
            Math::Geometry::Wireframe& output,
            const Math::Geometry::Wireframe& wireframe,
            const Math::Core::Mat4_f& matrix
        );

        void transformMultiWireframe
        (
            Math::Geometry::MultiWireframe& output,
            const Math::Geometry::MultiWireframe& multi_wireframe,
            const Math::Core::Mat4_f& matrix
        );
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Interpolations.
        //-----------------------------------------------------------------------------------------------------------------//
        void interpolateVertex
        (
            Math::Geometry::Vertex& output,
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end,
            float t
        );
        //-----------------------------------------------------------------------------------------------------------------//
    };
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
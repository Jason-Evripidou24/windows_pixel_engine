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
#include "multi_wireframe.hpp"
#include "polygon.hpp"
#include "vertex.hpp"
#include "wireframe.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Math
{
    namespace Geometry
    {
        //-----------------------------------------------------------------------------------------------------------------//
        // Transformations.
        //-----------------------------------------------------------------------------------------------------------------//
        inline void transformVertex
        (
            Math::Geometry::Vertex&       output,
            const Math::Geometry::Vertex& vertex,
            const Math::Core::Mat4_f&     matrix
        )
        {
            output = vertex;
            output.m_position = matrix * vertex.m_position;
        }

        inline void transformPolygon
        (
            Math::Geometry::Polygon&       output,
            const Math::Geometry::Polygon& polygon,
            const Math::Core::Mat4_f&      matrix
        )
        {
            size_t num_vertices = polygon.m_num_vertices;

            output.resize(num_vertices);
            for(size_t i = 0; i < num_vertices; i++)
            {
                Math::Geometry::transformVertex(output.m_vertices[i], polygon.m_vertices[i], matrix);
            }
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Functions for clipping polygons within homogeneous clip space.
        //-----------------------------------------------------------------------------------------------------------------//
        inline float getVertexDistanceToPlaneMinXClipSpace(const Math::Geometry::Vertex& v)
        {
            return v.m_position.m_data[0] + v.m_position.m_data[3];
        }
        inline float getVertexDistanceToPlaneMaxXClipSpace(const Math::Geometry::Vertex& v)
        {
            return v.m_position.m_data[0] - v.m_position.m_data[3];
        }
        inline float getVertexDistanceToPlaneMinYClipSpace(const Math::Geometry::Vertex& v)
        {
            return v.m_position.m_data[1] + v.m_position.m_data[3];
        }
        inline float getVertexDistanceToPlaneMaxYClipSpace(const Math::Geometry::Vertex& v)
        {
            return v.m_position.m_data[1] - v.m_position.m_data[3];
        }
        inline float getVertexDistanceToPlaneMinZClipSpace(const Math::Geometry::Vertex& v)
        {
            return v.m_position.m_data[2] + v.m_position.m_data[3];
        }
        inline float getVertexDistanceToPlaneMaxZClipSpace(const Math::Geometry::Vertex& v)
        {
            return v.m_position.m_data[2] - v.m_position.m_data[3];
        }

        inline bool checkVertexInsidePlaneMinXClipSpace(const Math::Geometry::Vertex& v)
        {
            return Math::Geometry::getVertexDistanceToPlaneMinXClipSpace(v) >= 0.0f;
        }
        inline bool checkVertexInsidePlaneMaxXClipSpace(const Math::Geometry::Vertex& v)
        {
            return Math::Geometry::getVertexDistanceToPlaneMaxXClipSpace(v) <= 0.0f;
        }
        inline bool checkVertexInsidePlaneMinYClipSpace(const Math::Geometry::Vertex& v)
        {
            return Math::Geometry::getVertexDistanceToPlaneMinYClipSpace(v) >= 0.0f;
        }
        inline bool checkVertexInsidePlaneMaxYClipSpace(const Math::Geometry::Vertex& v)
        {
            return Math::Geometry::getVertexDistanceToPlaneMaxYClipSpace(v) <= 0.0f;
        }
        inline bool checkVertexInsidePlaneMinZClipSpace(const Math::Geometry::Vertex& v)
        {
            return Math::Geometry::getVertexDistanceToPlaneMinZClipSpace(v) >= 0.0f;
        }
        inline bool checkVertexInsidePlaneMaxZClipSpace(const Math::Geometry::Vertex& v)
        {
            return Math::Geometry::getVertexDistanceToPlaneMaxZClipSpace(v) <= 0.0f;
        }

        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMinXClipSpace
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );
        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMaxXClipSpace
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );
        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMinYClipSpace
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );
        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMaxYClipSpace
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );
        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMinZClipSpace
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );
        Math::Geometry::Vertex lineSegmentIntersectionWithPlaneMaxZClipSpace
        (
            const Math::Geometry::Vertex& start,
            const Math::Geometry::Vertex& end
        );

        void clipPolygonAgainstPlaneMinXClipSpace(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon);
        void clipPolygonAgainstPlaneMaxXClipSpace(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon);
        void clipPolygonAgainstPlaneMinYClipSpace(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon);
        void clipPolygonAgainstPlaneMaxYClipSpace(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon);
        void clipPolygonAgainstPlaneMinZClipSpace(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon);
        void clipPolygonAgainstPlaneMaxZClipSpace(Math::Geometry::Polygon& output, const Math::Geometry::Polygon& polygon);
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Interpolations.
        //-----------------------------------------------------------------------------------------------------------------//
        inline void interpolateVertex
        (
            Math::Geometry::Vertex&       output,
            const Math::Geometry::Vertex& start ,
            const Math::Geometry::Vertex& end   ,
            float t
        )
        {
            if(t <= 0.0f) { t = 0.0f; }
            if(t >= 1.0f) { t = 1.0f; }

            Math::Core::interpolateVec4f(output.m_position, start.m_position, end.m_position, t);
            Math::Core::interpolateVec2f(output.m_tex_coords, start.m_tex_coords, end.m_tex_coords, t);
            Math::Core::interpolateVec3f(output.m_normal, start.m_normal, end.m_normal, t);
            Math::Core::interpolateVec4f(output.m_color, start.m_color, end.m_color, t);
        }
        //-----------------------------------------------------------------------------------------------------------------//
    };
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
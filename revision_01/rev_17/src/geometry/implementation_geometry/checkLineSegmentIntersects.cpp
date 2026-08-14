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
#include "../geometry.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
bool Geometry::checkLineSegmentIntersectsTriangle
(
    const Math::Vec3_f& line_start_pos,
    const Math::Vec3_f& line_end_pos,
    const Math::Vec3_f& v0_pos,
    const Math::Vec3_f& v1_pos,
    const Math::Vec3_f& v2_pos
)
{
    float epsilon = 0.00001f;

    Math::Vec3_f line_direction = line_end_pos - line_start_pos;

    Math::Vec3_f edge1 = v1_pos - v0_pos; // Direction vector v0_pos to v1_pos.
    Math::Vec3_f edge2 = v2_pos - v0_pos; // Direction vector v0_pos to v2_pos.

    Math::Vec3_f h;
    Math::crossProduct(h, line_direction, edge2);

    float determinant = Math::dotProduct(edge1, h);
    if(std::abs(determinant) < epsilon) { return false; }

    Math::Vec3_f s = line_start_pos - v0_pos;

    float u = Math::dotProduct(s, h) / determinant;
    if( (u < 0.0f) || (u > 1.0f) ) { return false; }

    Math::Vec3_f q;
    Math::crossProduct(q, s, edge1);

    float v = Math::dotProduct(line_direction, q) / determinant;
    if( (v < 0.0f) || ((u + v) > 1.0f) ) { return false; }

    float t = Math::dotProduct(edge2, q) / determinant;
    if( (t < 0.0f) || (t > 1.0f) ) { return false; }

    return true;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
bool Geometry::checkLineSegmentIntersectsMultiWireframe
(
    const Math::Vec3_f& line_start_pos,
    const Math::Vec3_f& line_end_pos,
    const Geometry::MultiWireframe& multi_wireframe
)
{
    size_t num_wireframes = multi_wireframe.m_num_wireframes;

    for(size_t i = 0; i < num_wireframes; i++)
    {
        const Geometry::Wireframe& wireframe = multi_wireframe.m_wireframes[i];
        size_t num_polygons = wireframe.m_num_polygons;
        
        for(size_t j = 0; j < num_polygons; j++)
        {
            const Geometry::Polygon& polygon = wireframe.m_polygons[j];
            size_t num_vertices = polygon.m_num_vertices;

            for(size_t k = 1; k < num_vertices - 1; k++)
            {
                const Math::Vec4_f& v0 = polygon.m_vertices[0].m_position;
                const Math::Vec4_f& v1 = polygon.m_vertices[k].m_position;
                const Math::Vec4_f& v2 = polygon.m_vertices[k + 1].m_position;

                bool check = Geometry::checkLineSegmentIntersectsTriangle
                (
                    line_start_pos,
                    line_end_pos,
                    Math::Vec3_f(v0.m_data[0], v0.m_data[1], v0.m_data[2]),
                    Math::Vec3_f(v1.m_data[0], v1.m_data[1], v1.m_data[2]),
                    Math::Vec3_f(v2.m_data[0], v2.m_data[1], v2.m_data[2])
                );

                if(check == true) { return true; }
            }
        }
    }

    return false;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
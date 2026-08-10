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
bool Math::Geometry::checkLineSegmentIntersectsPlaneX
(
    const Math::Core::Vec3_f& line_start_pos,
    const Math::Core::Vec3_f& line_end_pos,
    const float plane_x
)
{
    float x_start = line_start_pos.m_data[0];
    float x_end = line_end_pos.m_data[0];
    return ((x_start >= plane_x) && (x_end <= plane_x)) || ((x_start <= plane_x) && (x_end >= plane_x));
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
bool Math::Geometry::checkLineSegmentIntersectsPlaneY
(
    const Math::Core::Vec3_f& line_start_pos,
    const Math::Core::Vec3_f& line_end_pos,
    const float plane_y
)
{
    float y_start = line_start_pos.m_data[1];
    float y_end = line_end_pos.m_data[1];
    return ((y_start >= plane_y) && (y_end <= plane_y)) || ((y_start <= plane_y) && (y_end >= plane_y));
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
bool Math::Geometry::checkLineSegmentIntersectsPlaneZ
(
    const Math::Core::Vec3_f& line_start_pos,
    const Math::Core::Vec3_f& line_end_pos,
    const float plane_z
)
{
    float z_start = line_start_pos.m_data[2];
    float z_end = line_end_pos.m_data[2];
    return ((z_start >= plane_z) && (z_end <= plane_z)) || ((z_start <= plane_z) && (z_end >= plane_z));
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
bool Math::Geometry::checkLineSegmentIntersectsTriangle
(
    const Math::Core::Vec3_f& line_start_pos,
    const Math::Core::Vec3_f& line_end_pos,
    const Math::Core::Vec3_f& v0_pos,
    const Math::Core::Vec3_f& v1_pos,
    const Math::Core::Vec3_f& v2_pos
)
{
    float epsilon = 0.00001f;

    Math::Core::Vec3_f line_direction = line_end_pos - line_start_pos;

    Math::Core::Vec3_f edge1 = v1_pos - v0_pos; // Direction vector v0_pos to v1_pos.
    Math::Core::Vec3_f edge2 = v2_pos - v0_pos; // Direction vector v0_pos to v2_pos.

    Math::Core::Vec3_f h;
    Math::Core::crossProduct(h, line_direction, edge2);

    float determinant = Math::Core::dotProduct(edge1, h);
    if(std::abs(determinant) < epsilon) { return false; }

    Math::Core::Vec3_f s = line_start_pos - v0_pos;

    float u = Math::Core::dotProduct(s, h) / determinant;
    if( (u < 0.0f) || (u > 1.0f) ) { return false; }

    Math::Core::Vec3_f q;
    Math::Core::crossProduct(q, s, edge1);

    float v = Math::Core::dotProduct(line_direction, q) / determinant;
    if( (v < 0.0f) || ((u + v) > 1.0f) ) { return false; }

    float t = Math::Core::dotProduct(edge2, q) / determinant;
    if( (t < 0.0f) || (t > 1.0f) ) { return false; }

    return true;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
bool Math::Geometry::checkLineSegmentIntersectsWireframe
(
    const Math::Core::Vec3_f& line_start_pos,
    const Math::Core::Vec3_f& line_end_pos,
    const Math::Geometry::Wireframe& wireframe
)
{
    size_t num_polygons = wireframe.m_num_polygons;

    for(size_t j = 0; j < num_polygons; j++)
    {
        const Math::Geometry::Polygon& polygon = wireframe.m_polygons[j];
        size_t num_vertices = polygon.m_num_vertices;

        for(size_t k = 1; k < num_vertices - 1; k++)
        {
            const Math::Core::Vec4_f& v0 = polygon.m_vertices[0].m_position;
            const Math::Core::Vec4_f& v1 = polygon.m_vertices[k].m_position;
            const Math::Core::Vec4_f& v2 = polygon.m_vertices[k + 1].m_position;

            bool check = Math::Geometry::checkLineSegmentIntersectsTriangle
            (
                line_start_pos,
                line_end_pos,
                Math::Core::Vec3_f(v0.m_data[0], v0.m_data[1], v0.m_data[2]),
                Math::Core::Vec3_f(v1.m_data[0], v1.m_data[1], v1.m_data[2]),
                Math::Core::Vec3_f(v2.m_data[0], v2.m_data[1], v2.m_data[2])
            );

            if(check == true) { return true; }
        }
    }

    return false;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
bool Math::Geometry::checkLineSegmentIntersectsMultiWireframe
(
    const Math::Core::Vec3_f& line_start_pos,
    const Math::Core::Vec3_f& line_end_pos,
    const Math::Geometry::MultiWireframe& multi_wireframe
)
{
    size_t num_wireframes = multi_wireframe.m_num_wireframes;

    for(size_t i = 0; i < num_wireframes; i++)
    {
        const Math::Geometry::Wireframe& wireframe = multi_wireframe.m_wireframes[i];
        bool check = Math::Geometry::checkLineSegmentIntersectsWireframe(line_start_pos, line_end_pos, wireframe);
        if(check == true) { return true; }
    }

    return false;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
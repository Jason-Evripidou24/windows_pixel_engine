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
#include "../math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertexes are (should be) within clip space.
-   This function returns the vertex that the line made by v_0 to v_1 intersects the three dimensional plane plane_x.
-   Assumes:
    -   There is an intersection between line v_0 -> v_1 and plane_x.
*/
Math::Vertex Math::intersectionWithPlaneX(const Math::Vertex& v_0, const Math::Vertex& v_1, const float plane_x)
{
    float v_0_x = v_0.m_position.m_data[0];
    float v_1_x = v_1.m_position.m_data[0];
    float t = (plane_x - v_0_x) / (v_1_x - v_0_x);

    return Math::interpolateVertex(v_0, v_1, t);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertexes are (should be) within clip space.
-   This function returns the vertex that the line made by v_0 to v_1 intersects the three dimensional plane plane_y.
-   Assumes:
    -   There is an intersection between line v_0 -> v_1 and plane_y.
*/
Math::Vertex Math::intersectionWithPlaneY(const Math::Vertex& v_0, const Math::Vertex& v_1, const float plane_y)
{
    float v_0_y = v_0.m_position.m_data[1];
    float v_1_y = v_1.m_position.m_data[1];
    float t = (plane_y - v_0_y) / (v_1_y - v_0_y);

    return Math::interpolateVertex(v_0, v_1, t);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Vertexes are (should be) within clip space.
-   This function returns the vertex that the line made by v_0 to v_1 intersects the three dimensional plane plane_z.
-   Assumes:
    -   There is an intersection between line v_0 -> v_1 and plane_z.
*/
Math::Vertex Math::intersectionWithPlaneZ(const Math::Vertex& v_0, const Math::Vertex& v_1, const float plane_z)
{
    float v_0_z = v_0.m_position.m_data[2];
    float v_1_z = v_1.m_position.m_data[2];
    float t = (plane_z - v_0_z) / (v_1_z - v_0_z);

    return Math::interpolateVertex(v_0, v_1, t);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
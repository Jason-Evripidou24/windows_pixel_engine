// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef MATH_HPP
#define MATH_HPP
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
#include "mat4_f.hpp"
#include "triangle.hpp"
#include "vec2_f.hpp"
#include "vec3_f.hpp"
#include "vec3_i.hpp"
#include "vec4_f.hpp"
#include "vec4_i.hpp"
#include "vertex.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
namespace Math
{
    //---------------------------------------------------------------------------------------------------------------------//
    static const float  PI_f                 = 3.14159265358979323846f;
    static const double PI_d                 = 3.14159265358979323846;

    static const float  TWO_PI_f             = 2.0f * 3.14159265358979323846f;
    static const double TWO_PI_d             = 2.0 * 3.14159265358979323846;

    static const float  DEGREES_PER_RADIAN_f = 180.0f / PI_f;
    static const double DEGREES_PER_RADIAN_d = 180.0  / PI_d;
    static const float  RADIANS_PER_DEGREE_f = PI_f   / 180.0f;
    static const double RADIANS_PER_DEGREE_d = PI_d   / 180.0;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Mat4_f.
    //---------------------------------------------------------------------------------------------------------------------//
    Mat4_f identityMat4_f();
    Mat4_f translationMat4_f(const float x, const float y, const float z);
    Mat4_f rotationMat4_f(const float axis_x, const float axis_y, const float axis_z, const float theta_rad);
    Mat4_f scaleMat4_f(const float x, const float y, const float z);
    Mat4_f perspectiveMat4_f(const float fov_radians, const float aspect_ratio, const float near, const float far);
    Mat4_f lookAtMat4_f(const Vec3_f& cam_pos, const Vec3_f& cam_direction, const Vec3_f& cam_right, const Vec3_f& cam_up);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Dot product.
    //---------------------------------------------------------------------------------------------------------------------//
    float dotProduct(const Vec3_f& vec_l, const Vec3_f& vec_r);
    float dotProduct(const Vec4_f& vec_l, const Vec4_f& vec_r);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Cross product.
    //---------------------------------------------------------------------------------------------------------------------//
    Vec3_f crossProduct(const Vec3_f& vec_l, const Vec3_f& vec_r);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Normalise.
    //---------------------------------------------------------------------------------------------------------------------//
    Vec2_f normalise(const Vec2_f& vec);
    Vec3_f normalise(const Vec3_f& vec);
    Vec4_f normalise(const Vec4_f& vec);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Interpolations.
    //---------------------------------------------------------------------------------------------------------------------//
    Vec2_f interpolateVec2f(const Vec2_f& start, const Vec2_f& end, float t);
    Vec3_f interpolateVec3f(const Vec3_f& start, const Vec3_f& end, float t);
    Vec4_f interpolateVec4f(const Vec4_f& start, const Vec4_f& end, float t);

    Vertex interpolateVertex(const Vertex& start, const Vertex& end, float t);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Intersections.
    //---------------------------------------------------------------------------------------------------------------------//
    Vertex intersectionWithPlaneX(const Vertex& v_0, const Vertex& v_1, const float plane_x);
    Vertex intersectionWithPlaneY(const Vertex& v_0, const Vertex& v_1, const float plane_y);
    Vertex intersectionWithPlaneZ(const Vertex& v_0, const Vertex& v_1, const float plane_z);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Triangle transform, perspective divide and clipping between the geometric planes.
    //---------------------------------------------------------------------------------------------------------------------//
    Triangle transformTriangle(const Triangle& triangle, const Mat4_f& matrix);

    Triangle perspectiveDivideTriangle(const Triangle& triangle);

    std::vector<Triangle> clipTriangleMinX(const Triangle& triangle, const float min_x_plane);
    std::vector<Triangle> clipTriangleMaxX(const Triangle& triangle, const float max_x_plane);
    std::vector<Triangle> clipTriangleBetweenX(const Triangle& triangle, const float min_x_plane, const float max_x_plane);

    std::vector<Triangle> clipTriangleMinY(const Triangle& triangle, const float min_y_plane);
    std::vector<Triangle> clipTriangleMaxY(const Triangle& triangle, const float max_y_plane);
    std::vector<Triangle> clipTriangleBetweenY(const Triangle& triangle, const float min_y_plane, const float max_y_plane);

    std::vector<Triangle> clipTriangleMinZ(const Triangle& triangle, const float min_z_plane);
    std::vector<Triangle> clipTriangleMaxZ(const Triangle& triangle, const float max_z_plane);
    std::vector<Triangle> clipTriangleBetweenZ(const Triangle& triangle, const float min_z_plane, const float max_z_plane);

    std::vector<Triangle> clipTriangleBetweenXYZ
    (
        const Triangle& triangle,
        const float min_x_plane,
        const float max_x_plane,
        const float min_y_plane,
        const float max_y_plane,
        const float min_z_plane,
        const float max_z_plane
    );
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Misc.
    //---------------------------------------------------------------------------------------------------------------------//
    float convertDegreesToRadians(const float degrees);
    uint32_t convertVec3fToColor(const Vec3_f& color);
    uint32_t convertVec4fToColor(const Vec4_f& color);

    uint32_t interpolateUint32(const uint32_t start, const uint32_t end, float t);
    float interpolateFloat(const float start, const float end, float t);
    //---------------------------------------------------------------------------------------------------------------------//
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
#include "vec2_f.hpp"
#include "vec3_f.hpp"
#include "vec3_i.hpp"
#include "vec4_f.hpp"
#include "vec4_i.hpp"
#include "vertex.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
enum class ClipPlane
{
    MIN_X,
    MAX_X,
    MIN_Y,
    MAX_Y,
    MIN_Z,
    MAX_Z
};


namespace Math
{
    //---------------------------------------------------------------------------------------------------------------------//
    // Homogenous Space maths.
    //---------------------------------------------------------------------------------------------------------------------//
    float getVertexDistanceToPlaneMinX(const Math::Vertex& v);
    bool checkVertexInsidePlaneMinX(const Math::Vertex& v);
    Math::Vertex lineIntersectionWithPlaneMinX(const Math::Vertex& start, const Math::Vertex& end);
    void clipPolygonAgainstPlaneMinX(std::vector<Math::Vertex>& output, const std::vector<Math::Vertex>& polygon);

    float getVertexDistanceToPlaneMaxX(const Math::Vertex& v);
    bool checkVertexInsidePlaneMaxX(const Math::Vertex& v);
    Math::Vertex lineIntersectionWithPlaneMaxX(const Math::Vertex& start, const Math::Vertex& end);
    void clipPolygonAgainstPlaneMaxX(std::vector<Math::Vertex>& output, const std::vector<Math::Vertex>& polygon);

    float getVertexDistanceToPlaneMinY(const Math::Vertex& v);
    bool checkVertexInsidePlaneMinY(const Math::Vertex& v);
    Math::Vertex lineIntersectionWithPlaneMinY(const Math::Vertex& start, const Math::Vertex& end);
    void clipPolygonAgainstPlaneMinY(std::vector<Math::Vertex>& output, const std::vector<Math::Vertex>& polygon);

    float getVertexDistanceToPlaneMaxY(const Math::Vertex& v);
    bool checkVertexInsidePlaneMaxY(const Math::Vertex& v);
    Math::Vertex lineIntersectionWithPlaneMaxY(const Math::Vertex& start, const Math::Vertex& end);
    void clipPolygonAgainstPlaneMaxY(std::vector<Math::Vertex>& output, const std::vector<Math::Vertex>& polygon);

    float getVertexDistanceToPlaneMinZ(const Math::Vertex& v);
    bool checkVertexInsidePlaneMinZ(const Math::Vertex& v);
    Math::Vertex lineIntersectionWithPlaneMinZ(const Math::Vertex& start, const Math::Vertex& end);
    void clipPolygonAgainstPlaneMinZ(std::vector<Math::Vertex>& output, const std::vector<Math::Vertex>& polygon);

    float getVertexDistanceToPlaneMaxZ(const Math::Vertex& v);
    bool checkVertexInsidePlaneMaxZ(const Math::Vertex& v);
    Math::Vertex lineIntersectionWithPlaneMaxZ(const Math::Vertex& start, const Math::Vertex& end);
    void clipPolygonAgainstPlaneMaxZ(std::vector<Math::Vertex>& output, const std::vector<Math::Vertex>& polygon);
    //---------------------------------------------------------------------------------------------------------------------//
    
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
    // Dot product.
    //---------------------------------------------------------------------------------------------------------------------//
    float dotProduct(const Vec3_f& vec_l, const Vec3_f& vec_r);
    float dotProduct(const Vec4_f& vec_l, const Vec4_f& vec_r);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Cross product.
    //---------------------------------------------------------------------------------------------------------------------//
    void crossProduct(Vec3_f& output, const Vec3_f& vec_l, const Vec3_f& vec_r);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Interpolations.
    //---------------------------------------------------------------------------------------------------------------------//
    void interpolateVec2f(Vec2_f& output, const Vec2_f& start, const Vec2_f& end, float t);
    void interpolateVec3f(Vec3_f& output, const Vec3_f& start, const Vec3_f& end, float t);
    void interpolateVec4f(Vec4_f& output, const Vec4_f& start, const Vec4_f& end, float t);

    void interpolateVertex(Vertex& output, const Vertex& start, const Vertex& end, float t);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Triangle transform, perspective divide and clipping between the geometric planes.
    //---------------------------------------------------------------------------------------------------------------------//
    void transformVertex(Vertex& output, const Vertex& vertex, const Mat4_f& matrix);
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
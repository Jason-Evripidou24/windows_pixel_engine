// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef RENDERER_HPP
#define RENDERER_HPP
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
#include "../backbuffer/backbuffer.hpp"

#include "../math/math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Renderer pipeline:
    1.  Local/Object Space (Vec3, Vec4 with 1.0f as the homogenious coordinate)
    |   Model Matrix
    2.  World Space (Vec4)
    |   View Matrix
    3.  View Space
    |   Projection Matrix
    4.  Clip Space (Vec4)
    |   Homogeneous Clipping
    |   Perspective Divide
    5.  Normalized Device Coordinates (NDC)
    |   Viewport Transform
    6.  Screen Space
    |   Rasterization, Depth Test, Framebuffer
*/
struct Renderer
{
    //---------------------------------------------------------------------------------------------------------------------//
    // Functions.
    //---------------------------------------------------------------------------------------------------------------------//
    Math::Triangle transformTriangle(const Math::Triangle& triangle, const Math::Mat4_f& matrix);

    Math::Vertex intersectionWithPlaneX(const Math::Vertex& v_0, const Math::Vertex& v_1, const float plane_x);
    Math::Vertex intersectionWithPlaneY(const Math::Vertex& v_0, const Math::Vertex& v_1, const float plane_y);
    Math::Vertex intersectionWithPlaneZ(const Math::Vertex& v_0, const Math::Vertex& v_1, const float plane_z);

    std::vector<Math::Triangle> clipTriangleMinX(const Math::Triangle& triangle, const float min_x_plane);
    std::vector<Math::Triangle> clipTriangleMaxX(const Math::Triangle& triangle, const float max_x_plane);
    std::vector<Math::Triangle> clipTriangleBetweenX(const Math::Triangle& triangle, const float min_x_plane, const float max_x_plane);

    std::vector<Math::Triangle> clipTriangleMinY(const Math::Triangle& triangle, const float min_y_plane);
    std::vector<Math::Triangle> clipTriangleMaxY(const Math::Triangle& triangle, const float max_y_plane);
    std::vector<Math::Triangle> clipTriangleBetweenY(const Math::Triangle& triangle, const float min_y_plane, const float max_y_plane);

    std::vector<Math::Triangle> clipTriangleMinZ(const Math::Triangle& triangle, const float min_z_plane);
    std::vector<Math::Triangle> clipTriangleMaxZ(const Math::Triangle& triangle, const float max_z_plane);
    std::vector<Math::Triangle> clipTriangleBetweenZ(const Math::Triangle& triangle, const float min_z_plane, const float max_z_plane);

    std::vector<Math::Triangle> clipTriangleBetweenXYZ
    (
        const Math::Triangle& triangle,
        const float min_x_plane,
        const float max_x_plane,
        const float min_y_plane,
        const float max_y_plane,
        const float min_z_plane,
        const float max_z_plane
    );
    
    Math::Triangle perspectiveDivideTriangle(const Math::Triangle& triangle);
    
    void drawTriangle(Backbuffer& backbuffer, const Math::Triangle& triangle, const bool draw_filled);
    void fillTriangle(Backbuffer& backbuffer, const Math::Triangle& triangle);

    void drawLine(Backbuffer& backbuffer, const Math::Vertex& v_0, const Math::Vertex& v_1);
    void drawPixel(Backbuffer& backbuffer, const Math::Vertex& vertex);
    //---------------------------------------------------------------------------------------------------------------------//
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
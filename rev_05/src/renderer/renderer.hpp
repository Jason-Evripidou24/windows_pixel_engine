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

#include "../math/vec3_f.hpp"
#include "../math/vertex.hpp"
#include "../math/triangle.hpp"
#include "../model/model.hpp"
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

    Math::Vertex clipIntersectionZ(const Math::Vertex& v_0, const Math::Vertex& v_1, const float plane_z);
    std::vector<Math::Triangle> clipTriangleMaxZ(const Math::Triangle& triangle, const float max_z_plane);
    
    void perspectiveDivideTriangle(Math::Triangle& triangle);

    void drawWireframeTriangle(Backbuffer& backbuffer, const Math::Triangle& triangle);
    void drawLine(Backbuffer& backbuffer, const Math::Vertex& v_0, const Math::Vertex& v_1);
    void drawPixel(Backbuffer& backbuffer, const Math::Vertex& vertex);

    void drawPixel
    (
        Backbuffer&    backbuffer,
        const float    x,
        const float    y,
        const float    depth,
        const uint32_t color
    );

    void drawLine
    (
        Backbuffer&    backbuffer,
        Math::Vec3_f   pos_0,
        const uint32_t color_0,
        Math::Vec3_f   pos_1,
        const uint32_t color_1
    );

    void drawWireframeTriangle
    (
        Backbuffer&    backbuffer,
        Math::Vec3_f   pos_0,
        const uint32_t color_0,
        Math::Vec3_f   pos_1,
        const uint32_t color_1,
        Math::Vec3_f   pos_2,
        const uint32_t color_2
    );

    void drawModel
    (
        Backbuffer&  backbuffer,
        Model& model,
        Math::Mat4_f proj_view_matrix
    );
    //---------------------------------------------------------------------------------------------------------------------//
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
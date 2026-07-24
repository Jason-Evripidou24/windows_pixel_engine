// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef RENDERER_HPP
#define RENDERER_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <thread>
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
#include "../model/model.hpp"
#include "../model/material_triangle.hpp"
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

-   All Draw methods assume that triangles, vertices, ... have been transformed to clip space. i.e. They have undergone
    transformation from loacl to clip space and perspective divide.
-   Draw methods of the renderer will clip triangles to be within -1 and 1 in the x,y,z view frustum.
*/
struct Renderer
{
    Backbuffer* m_backbuffer;

    //---------------------------------------------------------------------------------------------------------------------//
    // Constructor and destructor.
    //---------------------------------------------------------------------------------------------------------------------//
    Renderer(Backbuffer* backbuffer);
    ~Renderer();
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Functions.
    //---------------------------------------------------------------------------------------------------------------------//
    void drawModel(const Model& model, const Math::Mat4_f& projection_view_matrix, bool draw_filled, float color_mix);
    void drawTriangle(const Math::Triangle& triangle, const Material& material, bool draw_filled, float color_mix);
    void fillTriangle(const Math::Triangle& triangle, const Material& material, float color_mix);
    void drawLine(const Math::Vertex& v_0, const Math::Vertex& v_1, const Material& material, float color_mix);
    void drawPixel(const Math::Vertex& vertex, const Material& material, float color_mix);
    //---------------------------------------------------------------------------------------------------------------------//
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
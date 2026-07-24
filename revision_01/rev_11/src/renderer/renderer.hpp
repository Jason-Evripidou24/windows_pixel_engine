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

struct TileRendererJob
{
    MaterialTriangle* m_material_triangle = nullptr;
    bool              m_draw_filled;
    float             m_color_mix;
    bool*             m_parent_job_complete;
};

struct TileRenderer
{
    //---------------------------------------------------------------------------------------------------------------------//
    // The backbuffer that the TileRenderer object draws to.
    Backbuffer* m_backbuffer;

    // The bounding box in clip space that the TileRenderer object is responsible for drawing within.
    float m_x_min;
    float m_x_max;
    float m_y_min;
    float m_y_max;
    float m_z_min;
    float m_z_max;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Multithreading.
    //---------------------------------------------------------------------------------------------------------------------//
    std::thread              m_worker_thread;

    std::mutex               m_object_mutex;
    std::condition_variable  m_object_condition_variable;

    bool                     m_running;
    bool                     m_has_job;

    std::mutex*              m_parent_object_mutex;
    std::condition_variable* m_parent_condition_variable;

    TileRendererJob          m_tile_renderer_job;

    void start();
    void stop();

    void workerFunction();
    void parentRequestDrawMaterialTriangle
    (
        MaterialTriangle* material_triangle,
        bool draw_filled,
        float color_mix,
        bool* parent_job_complete
    );
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Constructor and Destructor.
    //---------------------------------------------------------------------------------------------------------------------//
    TileRenderer
    (
        std::mutex*              parent_object_mutex,
        std::condition_variable* parent_condition_variable,
        Backbuffer*              backbuffer,
        float                    x_min,
        float                    x_max,
        float                    y_min,
        float                    y_max,
        float                    z_min,
        float                    z_max
    );
    ~TileRenderer();
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Drawing functions. Each drawing function only draws within the bounding box of the TileRenderer object.
    //---------------------------------------------------------------------------------------------------------------------//
    void drawMaterialTriangle(MaterialTriangle* material_triangle, bool draw_filled, float color_mix);
    void fillTriangle(const Math::Triangle& triangle, const Material& material, float color_mix);
    void fillFlatBottomTriangle
    (
        const Math::Vertex& top,
        const Math::Vertex& left,
        const Math::Vertex& right,
        const Material& material,
        float color_mix
    );
    void fillFlatTopTriangle
    (
        const Math::Vertex& top_left,
        const Math::Vertex& top_right,
        const Math::Vertex& bottom,
        const Material& material,
        float color_mix
    );
    void drawLine(const Math::Vertex& v_0, const Math::Vertex& v_1, const Material& material, float color_mix);
    void drawPixel(const Math::Vertex& vertex, const Material& material, float color_mix);
    //---------------------------------------------------------------------------------------------------------------------//
};


struct Renderer
{
    //---------------------------------------------------------------------------------------------------------------------//
    /*
    -   TileRenderer objects to split up the drawing into seperate tiles within the backbuffer. Will extend to
        multithreading by having each TileRenderer contain a thread. For now no multithreading.
    */
    //---------------------------------------------------------------------------------------------------------------------//
    // Each pair contains a TileRenderer object and its associated job_complete check.
    std::vector<std::pair<std::unique_ptr<TileRenderer>, bool>> m_tile_renderers;

    std::mutex              m_renderer_mutex;
    std::condition_variable m_renderer_condition_variable;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Constructor and destructor.
    //---------------------------------------------------------------------------------------------------------------------//
    Renderer(Backbuffer* backbuffer);
    ~Renderer();
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Functions.
    //---------------------------------------------------------------------------------------------------------------------//
    void drawMaterialTriangles(std::queue<MaterialTriangle>& material_triangles_queue, bool draw_filled, float color_mix);
    //---------------------------------------------------------------------------------------------------------------------//
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef TILE_RENDERER_HPP
#define TILE_RENDERER_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <queue>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../backbuffer/backbuffer.hpp"
#include "../material/material.hpp"

#include "../math/core/math_core.hpp"
#include "../math/geometry/math_geometry.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
struct TileRendererJob
{
    std::shared_ptr<const Math::Geometry::Polygon> m_polygon;
    const Material*                                m_material;
    bool                                           m_draw_filled;
    float                                          m_color_mix;
    std::atomic<int>*                              m_extern_pending_jobs;
    std::mutex*                                    m_extern_pending_jobs_mutex;
    std::condition_variable*                       m_extern_pending_jobs_condition_variable;

    TileRendererJob()
    {
        m_polygon = nullptr;
        m_material = nullptr;
        m_draw_filled = false;
        m_color_mix = 0.0f;
        m_extern_pending_jobs = nullptr;
        m_extern_pending_jobs_mutex = nullptr;
        m_extern_pending_jobs_condition_variable = nullptr;
    }

    TileRendererJob
    (
        std::shared_ptr<const Math::Geometry::Polygon> polygon,
        const Material*                                material,
        bool                                           draw_filled,
        float                                          color_mix,
        std::atomic<int>*                              extern_pending_jobs,
        std::mutex*                                    extern_pending_jobs_mutex,
        std::condition_variable*                       extern_pending_jobs_condition_variable
    )
    :
    m_polygon(polygon),
    m_material(material),
    m_draw_filled(draw_filled),
    m_color_mix(color_mix),
    m_extern_pending_jobs(extern_pending_jobs),
    m_extern_pending_jobs_mutex(extern_pending_jobs_mutex),
    m_extern_pending_jobs_condition_variable(extern_pending_jobs_condition_variable)
    {
    }
};

struct TileRenderer
{
    //---------------------------------------------------------------------------------------------------------------------//
    // The backbuffer that the TileRenderer object draws to.
    Backbuffer* m_backbuffer;

    // The bounding box (tile) in screen space that the TileRenderer object is responsible for drawing within.
    int m_tile_x_min;
    int m_tile_x_max;
    int m_tile_y_min;
    int m_tile_y_max;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Multithreading.
    //---------------------------------------------------------------------------------------------------------------------//
    std::thread                 m_worker_thread;

    std::atomic<bool>           m_running;

    std::queue<TileRendererJob> m_jobs;
    std::mutex                  m_jobs_mutex;
    std::condition_variable     m_jobs_condition_variable;

    void start();
    void stop();

    void workerFunction();
    void submitJob
    (
        std::shared_ptr<const Math::Geometry::Polygon> polygon,
        const Material*                                material,
        bool                                           draw_filled,
        float                                          color_mix,
        std::atomic<int>*                              extern_pending_jobs,
        std::mutex*                                    extern_pending_jobs_mutex,
        std::condition_variable*                       extern_pending_jobs_condition_variable
    );
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Constructor and Destructor.
    //---------------------------------------------------------------------------------------------------------------------//
    TileRenderer
    (
        Backbuffer* backbuffer,
        int         tile_x_min,
        int         tile_x_max,
        int         tile_y_min,
        int         tile_y_max
    );
    ~TileRenderer();
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Drawing functions. Each drawing function only draws within the bounding box of the TileRenderer object.
    //---------------------------------------------------------------------------------------------------------------------//
    void drawPolygon
    (
        std::shared_ptr<const Math::Geometry::Polygon> polygon,
        const Material*                                material,
        bool                                           draw_filled,
        float                                          color_mix
    );

    void fillTriangle
    (
        const Math::Geometry::Vertex* v0,
        const Math::Geometry::Vertex* v1,
        const Math::Geometry::Vertex* v2,
        const Material*               material,
        float                         color_mix
    );

    void drawLine
    (
        const Math::Geometry::Vertex* v0,
        const Math::Geometry::Vertex* v1,
        const Material* material,
        float color_mix
    );

    void drawPixel
    (
        const Math::Geometry::Vertex* vertex,
        const Material* material,
        float color_mix
    );
    //---------------------------------------------------------------------------------------------------------------------//
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
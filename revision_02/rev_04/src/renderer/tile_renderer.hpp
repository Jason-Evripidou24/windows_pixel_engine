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
#include <cstdint>
#include <mutex>
#include <thread>
#include <queue>
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
struct TileRendererJob
{
    const Math::Vertex*            m_v0;
    const Math::Vertex*            m_v1;
    const Math::Vertex*            m_v2;
    const Material*                m_material;
    float                          m_color_mix;
    std::atomic<int>*        m_extern_pending_jobs;
    std::mutex*              m_extern_pending_jobs_mutex;
    std::condition_variable* m_extern_pending_jobs_condition_variable;

    TileRendererJob()
    {
        m_v0 = nullptr;
        m_v1 = nullptr;
        m_v2 = nullptr;
        m_material = nullptr;
        m_color_mix = 0.0f;
        m_extern_pending_jobs = nullptr;
        m_extern_pending_jobs_mutex = nullptr;
        m_extern_pending_jobs_condition_variable = nullptr;
    }

    TileRendererJob
    (
        const Math::Vertex*      v0,
        const Math::Vertex*      v1,
        const Math::Vertex*      v2,
        const Material*          material,
        float                    color_mix,
        std::atomic<int>*        extern_pending_jobs,
        std::mutex*              extern_pending_jobs_mutex,
        std::condition_variable* extern_pending_jobs_condition_variable
    )
    :
    m_v0(v0),
    m_v1(v1),
    m_v2(v2),
    m_material(material),
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
        const Math::Vertex*      v0,
        const Math::Vertex*      v1,
        const Math::Vertex*      v2,
        const Material*          material,
        float                    color_mix,
        std::atomic<int>*        extern_pending_jobs,
        std::mutex*              extern_pending_jobs_mutex,
        std::condition_variable* extern_pending_jobs_condition_variable
    );
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Constructor and Destructor.
    //---------------------------------------------------------------------------------------------------------------------//
    TileRenderer
    (
        Backbuffer*              backbuffer,
        int                      tile_x_min,
        int                      tile_x_max,
        int                      tile_y_min,
        int                      tile_y_max
    );
    ~TileRenderer();
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Drawing functions. Each drawing function only draws within the bounding box of the TileRenderer object.
    //---------------------------------------------------------------------------------------------------------------------//
    void fillTriangle
    (
        const Math::Vertex* v0,
        const Math::Vertex* v1,
        const Math::Vertex* v2,
        const Material* material,
        float color_mix
    );
    //---------------------------------------------------------------------------------------------------------------------//
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
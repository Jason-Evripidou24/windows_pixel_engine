// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef TRANSFORMER_WORKER_HPP
#define TRANSFORMER_WORKER_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <thread>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "transformation_system_system_total_jobs_counter.hpp"
#include "transformation_job_queue.hpp"
#include "transformation_job.hpp"
#include "transformer.hpp"

#include "../tile_renderer_system/tile_renderer_system.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
struct TransformerWorker
{
    TileRendererSystem& m_tile_renderer_system;

    TransformationSystemTotalJobsCounter& m_total_jobs_counter;
    TransformationJobQueue& m_job_queue;

    Transformer m_transformer;

    std::thread m_worker_thread;

    //---------------------------------------------------------------------------------------------------------------------//
    // Constructor and Destructor.
    //---------------------------------------------------------------------------------------------------------------------//
    TransformerWorker
    (
        TileRendererSystem&                   tile_renderer_system,
        TransformationJobQueue&               job_queue           ,
        TransformationSystemTotalJobsCounter& total_jobs_counter
    )
        :   m_job_queue(job_queue)
        ,   m_total_jobs_counter(total_jobs_counter)
        ,   m_tile_renderer_system(tile_renderer_system)
    {
    }

    ~TransformerWorker()
    {
        this->stop();
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    inline void start()
    {
        if(m_worker_thread.joinable()) { return; }

        m_worker_thread = std::thread(&TransformerWorker::workerFunction, this);
    }

    inline void stop()
    {
        m_job_queue.shutdown();

        if(m_worker_thread.joinable()) { m_worker_thread.join(); }
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    inline void workerFunction()
    {
        TransformationJob transformation_job(nullptr, nullptr, 0, 0, Math::Core::Mat4_f(), nullptr, false);

        while(true)
        {
            if(m_job_queue.getTransformationJob(transformation_job) == false) { break; }

            if
            (
                (transformation_job.m_target    != nullptr) &&
                (transformation_job.m_wireframe != nullptr) &&
                (transformation_job.m_material  != nullptr)
            )
            {
                m_transformer.drawLocalSpaceWireframe
                (
                    &m_tile_renderer_system,
                    transformation_job.m_target,
                    transformation_job.m_wireframe,
                    transformation_job.m_start_polygon,
                    transformation_job.m_end_polygon,
                    &(transformation_job.m_proj_view_model_matrix),
                    transformation_job.m_material,
                    transformation_job.m_draw_filled
                );
            }

            m_total_jobs_counter.decrement();
        }
    }
    //---------------------------------------------------------------------------------------------------------------------//
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
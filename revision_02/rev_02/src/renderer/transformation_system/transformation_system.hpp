// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef TRANSFORMATION_SYSTEM_HPP
#define TRANSFORMATION_SYSTEM_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <memory>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "transformation_system_system_total_jobs_counter.hpp"
#include "transformer_worker.hpp"
#include "transformation_job_queue.hpp"

#include "../tile_renderer_system/tile_renderer_system.hpp"

#include "../../math/core/math_core.hpp"
#include "../../math/geometry/math_geometry.hpp"
#include "../../model/material/material_library.hpp"
#include "../../model/mesh/mesh_polygon.hpp"
#include "../../window/backbuffer/backbuffer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
struct TransformationSystem
{
    TransformationSystemTotalJobsCounter m_transformation_system_total_jobs_counter;

    int m_num_transformer_workers;
    std::vector<std::unique_ptr<TransformerWorker>> m_transformer_workers;

    //---------------------------------------------------------------------------------------------------------------------//
    // Constructor and destructor.
    //---------------------------------------------------------------------------------------------------------------------//
    TransformationSystem(TileRendererSystem& tile_renderer_system, int num_transformer_workers)
    {
        m_transformation_system_total_jobs_counter.resetCount();

        m_num_transformer_workers = num_transformer_workers;
        m_transformer_workers.resize(num_transformer_workers);
        for(int i = 0; i < num_transformer_workers; i++)
        {
            m_transformer_workers[i] = std::make_unique<TransformerWorker>
            (
                tile_renderer_system,
                m_transformation_system_total_jobs_counter
            );
            m_transformer_workers[i]->start();
        }
    }
    ~TransformationSystem() = default;
    //---------------------------------------------------------------------------------------------------------------------//

    void sendLocalSpaceWireframeToTransformers
    (
        Backbuffer*                     target                ,
        const std::vector<MeshPolygon>* mesh_polygons         ,
        size_t                          polygon_max_chunk_size,
        const Math::Core::Mat4_f&       proj_view_model_matrix,
        const MaterialLibrary*          material_library      ,
        const bool                      draw_filled
    );
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
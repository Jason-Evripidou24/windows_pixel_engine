// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../transformation_system.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void TransformationSystem::sendLocalSpaceWireframeToTransformers
(
    Backbuffer*                     target                ,
    const std::vector<MeshPolygon>* mesh_polygons         ,
    size_t                          polygon_max_chunk_size,
    const Math::Core::Mat4_f&       proj_view_model_matrix,
    const MaterialLibrary*          material_library      ,
    const bool                      draw_filled
)
{
    const size_t num_polygons = mesh_polygons->size();

    if( (num_polygons == 0) || (polygon_max_chunk_size == 0) ) { return; }

    for(size_t start_polygon = 0; start_polygon < num_polygons; start_polygon += polygon_max_chunk_size)
    {
        size_t end_polygon = start_polygon + polygon_max_chunk_size - 1;
        if(end_polygon >= num_polygons) { end_polygon = num_polygons - 1; }

        m_transformation_system_total_jobs_counter.increment();

        static int send_to_transformer_worker = 0;
        m_transformer_workers[send_to_transformer_worker]->m_job_queue.insertTransformationJob
        (
            TransformationJob
            (
                target                ,
                mesh_polygons         ,
                start_polygon         ,
                end_polygon           ,
                proj_view_model_matrix,
                material_library      ,
                draw_filled
            )
        );
        send_to_transformer_worker = (send_to_transformer_worker + 1) % m_num_transformer_workers;
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
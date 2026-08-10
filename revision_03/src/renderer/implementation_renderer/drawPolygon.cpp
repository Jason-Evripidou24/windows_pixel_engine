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
#include "../renderer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawPolygon
(
    std::shared_ptr<Math::Geometry::Polygon> polygon,
    const Material*                          material,
    bool                                     draw_filled,
    float                                    color_mix,
    std::atomic<int>*                        pending_jobs,
    std::mutex*                              pending_jobs_mutex,
    std::condition_variable*                 pending_jobs_condition_variable
)
{
    Math::Geometry::Polygon buffer;

    Math::Geometry::clipPolygonAgainstPlaneMinX(buffer, (*polygon));
    Math::Geometry::clipPolygonAgainstPlaneMaxX((*polygon), buffer);
    Math::Geometry::clipPolygonAgainstPlaneMinY(buffer, (*polygon));
    Math::Geometry::clipPolygonAgainstPlaneMaxY((*polygon), buffer);
    Math::Geometry::clipPolygonAgainstPlaneMinZ(buffer, (*polygon));
    Math::Geometry::clipPolygonAgainstPlaneMaxZ((*polygon), buffer);

    size_t num_vertices = polygon->m_num_vertices;

    for(size_t i = 0; i < num_vertices; i++)
    {
        if(Math::Core::checkFloatEquals(polygon->m_vertices[i].m_position.m_data[3], 0.0f))
        {
            polygon->clear();
            break;
        }
        polygon->m_vertices[i].perspectiveDivide();
    }
    if(polygon->m_num_vertices < 3) { return; }

    this->sendPolygonToTiles
    (
        polygon,
        material,
        draw_filled,
        color_mix,
        pending_jobs,
        pending_jobs_mutex,
        pending_jobs_condition_variable
    );
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
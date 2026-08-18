// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cmath>
#include <memory>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../transformer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Transformer::drawLocalSpaceWireframe
(
    TileRendererSystem*              m_tile_renderer_system,
    Backbuffer*                      target                ,
    const Math::Geometry::Wireframe* wireframe             ,
    size_t                           start_polygon         ,
    size_t                           end_polygon           ,
    const Math::Core::Mat4_f*        proj_view_model_matrix,
    const Material*                  material              ,
    const bool                       draw_filled
)
{
    for(size_t i = start_polygon; i <= end_polygon; i++)
    {
        Math::Geometry::Polygon polygon_transform_and_clip;
        Math::Geometry::transformPolygon(polygon_transform_and_clip, wireframe->m_polygons[i], *proj_view_model_matrix);

        Math::Geometry::Polygon buffer = polygon_transform_and_clip;

        Math::Geometry::clipPolygonAgainstPlaneMinXClipSpace(polygon_transform_and_clip, buffer);
        std::swap(buffer, polygon_transform_and_clip);
        Math::Geometry::clipPolygonAgainstPlaneMaxXClipSpace(polygon_transform_and_clip, buffer);
        std::swap(buffer, polygon_transform_and_clip);
        Math::Geometry::clipPolygonAgainstPlaneMinYClipSpace(polygon_transform_and_clip, buffer);
        std::swap(buffer, polygon_transform_and_clip);
        Math::Geometry::clipPolygonAgainstPlaneMaxYClipSpace(polygon_transform_and_clip, buffer);
        std::swap(buffer, polygon_transform_and_clip);
        Math::Geometry::clipPolygonAgainstPlaneMinZClipSpace(polygon_transform_and_clip, buffer);
        std::swap(buffer, polygon_transform_and_clip);
        Math::Geometry::clipPolygonAgainstPlaneMaxZClipSpace(polygon_transform_and_clip, buffer);

        polygon_transform_and_clip.perspectiveDivide();

        for(size_t i = 0; i < polygon_transform_and_clip.m_num_vertices; i++)
        {
            if( std::abs(polygon_transform_and_clip.m_vertices[i].m_position.m_data[3]) < 0.0001f )
            {
                polygon_transform_and_clip.clear();
                break;
            }
        }
        if(polygon_transform_and_clip.m_num_vertices < 3) { continue; }

        m_tile_renderer_system->sendNDCSpacePolygonToTileRenderers(target, polygon_transform_and_clip, material, draw_filled);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
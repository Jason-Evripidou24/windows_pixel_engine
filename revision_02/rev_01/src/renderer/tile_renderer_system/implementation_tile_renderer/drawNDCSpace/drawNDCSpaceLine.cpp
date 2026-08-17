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
#include "../../tile_renderer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void TileRenderer::drawNDCSpaceLine
(
    Backbuffer&                   target  ,
    const Math::Geometry::Vertex& v0      ,
    const Math::Geometry::Vertex& v1      ,
    const Material&               material
)
{
    //---------------------------------------------------------------------------------------------------------------------//
    // Calculate the backbuffer pixel width and height that will be required.
    //---------------------------------------------------------------------------------------------------------------------//
    int backbuffer_x0 = target.toBackbufferCoordX(v0.m_position.m_data[0]);
    int backbuffer_y0 = target.toBackbufferCoordY(v0.m_position.m_data[1]);

    int backbuffer_x1 = target.toBackbufferCoordX(v1.m_position.m_data[0]);
    int backbuffer_y1 = target.toBackbufferCoordY(v1.m_position.m_data[1]);

    int dx = backbuffer_x1 - backbuffer_x0;
    int dy = backbuffer_y1 - backbuffer_y0;

    int abs_dx = dx; if(abs_dx < 0) { abs_dx *= -1; }
    int abs_dy = dy; if(abs_dy < 0) { abs_dy *= -1; }

    int steps = abs_dx; if(abs_dy > steps) { steps = abs_dy; }

    if(steps == 0)
    {
        uint32_t tex_color = material.calcMaterialColor(v0.m_tex_coords.m_data[0], v0.m_tex_coords.m_data[1]);
        target.setPixel(backbuffer_x0, backbuffer_y0, v0.m_position.m_data[2], tex_color);
        return;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    for(int i = 0; i <= steps; i++)
    {
        float t = (1.0f) - (static_cast<float>(i) / static_cast<float>(steps));

        Math::Geometry::Vertex vertex_interpolated;
        Math::Geometry::interpolateVertex(vertex_interpolated, v0, v1, t);

        int x = target.toBackbufferCoordX(vertex_interpolated.m_position.m_data[0]);
        int y = target.toBackbufferCoordY(vertex_interpolated.m_position.m_data[1]);
        float z = vertex_interpolated.m_position.m_data[2];

        Math::Core::Vec2_f tex_coord = (v0.m_tex_coords * t) + (v1.m_tex_coords * (1.0f - t));
        uint32_t tex_color = material.calcMaterialColor(tex_coord.m_data[0], tex_coord.m_data[1]);

        target.setPixel(x, y, z, tex_color);
    }
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
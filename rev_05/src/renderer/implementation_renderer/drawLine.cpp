// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cstdint>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../renderer.hpp"

#include "../../backbuffer/backbuffer.hpp"
#include "../../math/line3d.hpp"
#include "../../math/vec3_f.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawLine
(
    Backbuffer&    backbuffer,
    Math::Vec3_f   pos_0,
    const uint32_t color_0,
    Math::Vec3_f   pos_1,
    const uint32_t color_1
)
{
    Math::Line3d line;
    line.m_start = pos_0;
    line.m_end = pos_1;
    uint32_t line_color_start = color_0;
    uint32_t line_color_end = color_1;

    //---------------------------------------------------------------------------------------------------------------------//
    if
    (
        (line.checkAnyPartOfLineWithinBounds(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f) == false)
    )
    {
        return;
    }
    line.cutToBounds(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    int backbuffer_x0 = (line.m_start.m_data[0] + 1.0f) * (backbuffer.m_width - 1) * 0.5f;
    int backbuffer_y0 = (1.0f - line.m_start.m_data[1]) * (backbuffer.m_height - 1) * 0.5f;

    float colA_0 = (float)((line_color_start >> 0)  & 0xFF);
    float colR_0 = (float)((line_color_start >> 8)  & 0xFF);
    float colG_0 = (float)((line_color_start >> 16) & 0xFF);
    float colB_0 = (float)((line_color_start >> 24) & 0xFF);

    
    int backbuffer_x1 = (line.m_end.m_data[0] + 1.0f) * (backbuffer.m_width - 1) * 0.5f;
    int backbuffer_y1 = (1.0f - line.m_end.m_data[1]) * (backbuffer.m_height - 1) * 0.5f;

    float colA_1 = (float)((line_color_end >> 0)  & 0xFF);
    float colR_1 = (float)((line_color_end >> 8)  & 0xFF);
    float colG_1 = (float)((line_color_end >> 16) & 0xFF);
    float colB_1 = (float)((line_color_end >> 24) & 0xFF);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Amount of backbuffer pixels width and height.
    //---------------------------------------------------------------------------------------------------------------------//
    int dx = backbuffer_x1 - backbuffer_x0;
    int dy = backbuffer_y1 - backbuffer_y0;

    int abs_dx = dx; if(abs_dx < 0) { abs_dx *= -1; }
    int abs_dy = dy; if(abs_dy < 0) { abs_dy *= -1; }

    int steps = abs_dx; if(abs_dy > steps) { steps = abs_dy; }

    if(steps == 0)
    {
        backbuffer.setPixel(backbuffer_x0, backbuffer_y0, (line.m_start.m_data[2] + line.m_end.m_data[2]) * 0.5f, line_color_start);
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    for(int i = 0; i <= steps; i++)
    {
        float t = static_cast<float>(i) / static_cast<float>(steps);

        int curr_backbuffer_x = int(backbuffer_x0 + dx * t);
        int curr_backbuffer_y = int(backbuffer_y0 + dy * t);
        float curr_backbuffer_depth = (line.m_start.m_data[2] * (1.0f - t)) + (line.m_end.m_data[2] * t);

        uint8_t curr_col_a = (uint8_t)((colA_0 * (1.0f - t)) + (colA_1 * t));
        uint8_t curr_col_r = (uint8_t)((colR_0 * (1.0f - t)) + (colR_1 * t));
        uint8_t curr_col_g = (uint8_t)((colG_0 * (1.0f - t)) + (colG_1 * t));
        uint8_t curr_col_b = (uint8_t)((colB_0 * (1.0f - t)) + (colB_1 * t));

        uint32_t curr_col_argb =
            (uint32_t(curr_col_a) << 0)  |
            (uint32_t(curr_col_r) << 8)  |
            (uint32_t(curr_col_g) << 16) |
            (uint32_t(curr_col_b) << 24);

        backbuffer.setPixel(curr_backbuffer_x, curr_backbuffer_y, curr_backbuffer_depth, curr_col_argb);
    }
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawLine(Backbuffer& backbuffer, const Math::Vertex& v_0, const Math::Vertex& v_1)
{
    //---------------------------------------------------------------------------------------------------------------------//
    int backbuffer_x0 = (v_0.m_position.m_data[0] + 1.0f) * (backbuffer.m_width - 1) * 0.5f;
    int backbuffer_y0 = (1.0f - v_0.m_position.m_data[1]) * (backbuffer.m_height - 1) * 0.5f;

    float colA_0 = (float)((v_0.m_color >> 0)  & 0xFF);
    float colR_0 = (float)((v_0.m_color >> 8)  & 0xFF);
    float colG_0 = (float)((v_0.m_color >> 16) & 0xFF);
    float colB_0 = (float)((v_0.m_color >> 24) & 0xFF);
    
    int backbuffer_x1 = (v_1.m_position.m_data[0] + 1.0f) * (backbuffer.m_width - 1) * 0.5f;
    int backbuffer_y1 = (1.0f - v_1.m_position.m_data[1]) * (backbuffer.m_height - 1) * 0.5f;

    float colA_1 = (float)((v_1.m_color >> 0)  & 0xFF);
    float colR_1 = (float)((v_1.m_color >> 8)  & 0xFF);
    float colG_1 = (float)((v_1.m_color >> 16) & 0xFF);
    float colB_1 = (float)((v_1.m_color >> 24) & 0xFF);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Amount of backbuffer pixels width and height.
    //---------------------------------------------------------------------------------------------------------------------//
    int dx = backbuffer_x1 - backbuffer_x0;
    int dy = backbuffer_y1 - backbuffer_y0;

    int abs_dx = dx; if(abs_dx < 0) { abs_dx *= -1; }
    int abs_dy = dy; if(abs_dy < 0) { abs_dy *= -1; }

    int steps = abs_dx; if(abs_dy > steps) { steps = abs_dy; }

    if(steps == 0)
    {
        backbuffer.setPixel(backbuffer_x0, backbuffer_y0, (v_0.m_position.m_data[2] + v_1.m_position.m_data[2]) * 0.5f, v_0.m_color);
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    for(int i = 0; i <= steps; i++)
    {
        float t = static_cast<float>(i) / static_cast<float>(steps);

        int curr_backbuffer_x = int(backbuffer_x0 + dx * t);
        int curr_backbuffer_y = int(backbuffer_y0 + dy * t);
        float curr_backbuffer_depth = (v_0.m_position.m_data[2] * (1.0f - t)) + (v_1.m_position.m_data[2] * t);

        uint8_t curr_col_a = (uint8_t)((colA_0 * (1.0f - t)) + (colA_1 * t));
        uint8_t curr_col_r = (uint8_t)((colR_0 * (1.0f - t)) + (colR_1 * t));
        uint8_t curr_col_g = (uint8_t)((colG_0 * (1.0f - t)) + (colG_1 * t));
        uint8_t curr_col_b = (uint8_t)((colB_0 * (1.0f - t)) + (colB_1 * t));

        uint32_t curr_col_argb =
            (uint32_t(curr_col_a) << 0)  |
            (uint32_t(curr_col_r) << 8)  |
            (uint32_t(curr_col_g) << 16) |
            (uint32_t(curr_col_b) << 24);

        backbuffer.setPixel(curr_backbuffer_x, curr_backbuffer_y, curr_backbuffer_depth, curr_col_argb);
    }
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
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
uint32_t mixColor(uint32_t color_a, float alpha, uint32_t color_b, float beta, uint32_t color_c, float gamma)
{
    float a0 = static_cast<float>((color_a >> 0) & 0xFF);
    float a1 = static_cast<float>((color_a >> 8) & 0xFF);
    float a2 = static_cast<float>((color_a >> 16) & 0xFF);
    float a3 = static_cast<float>((color_a >> 24) & 0xFF);

    float b0 = static_cast<float>((color_b >> 0) & 0xFF);
    float b1 = static_cast<float>((color_b >> 8) & 0xFF);
    float b2 = static_cast<float>((color_b >> 16) & 0xFF);
    float b3 = static_cast<float>((color_b >> 24) & 0xFF);

    float c0 = static_cast<float>((color_c >> 0) & 0xFF);
    float c1 = static_cast<float>((color_c >> 8) & 0xFF);
    float c2 = static_cast<float>((color_c >> 16) & 0xFF);
    float c3 = static_cast<float>((color_c >> 24) & 0xFF);

    uint8_t mix0 = static_cast<uint8_t>( (a0 * alpha) + (b0 * beta) + (c0 * gamma) );
    uint8_t mix1 = static_cast<uint8_t>( (a1 * alpha) + (b1 * beta) + (c1 * gamma) );
    uint8_t mix2 = static_cast<uint8_t>( (a2 * alpha) + (b2 * beta) + (c2 * gamma) );
    uint8_t mix3 = static_cast<uint8_t>( (a3 * alpha) + (b3 * beta) + (c3 * gamma) );

    uint32_t result =
        (static_cast<uint32_t>(mix0) << 0)  |
        (static_cast<uint32_t>(mix1) << 8)  |
        (static_cast<uint32_t>(mix2) << 16) |
        (static_cast<uint32_t>(mix3) << 24);

    return result;
}

void Renderer::drawTriangle
(
    Backbuffer& backbuffer_target,
    float       v0_x,
    float       v0_y,
    float       v0_z,
    uint32_t    v0_color,
    float       v1_x,
    float       v1_y,
    float       v1_z,
    uint32_t    v1_color,
    float       v2_x,
    float       v2_y,
    float       v2_z,
    uint32_t    v2_color
)
{
    //---------------------------------------------------------------------------------------------------------------------//
    // Screen coordinates.
    //---------------------------------------------------------------------------------------------------------------------//
    int v0_x_screen = backbuffer_target.toBackbufferCoordX(v0_x);
    int v0_y_screen = backbuffer_target.toBackbufferCoordY(v0_y);

    int v1_x_screen = backbuffer_target.toBackbufferCoordX(v1_x);
    int v1_y_screen = backbuffer_target.toBackbufferCoordY(v1_y);

    int v2_x_screen = backbuffer_target.toBackbufferCoordX(v2_x);
    int v2_y_screen = backbuffer_target.toBackbufferCoordY(v2_y);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Bounding box.
    //---------------------------------------------------------------------------------------------------------------------//
    int min_x = v0_x_screen;
    if(v1_x_screen < min_x) { min_x = v1_x_screen; }
    if(v2_x_screen < min_x) { min_x = v2_x_screen; }
    if(min_x < 0) { min_x = 0; }

    int max_x = v0_x_screen;
    if(v1_x_screen > max_x) { max_x = v1_x_screen; }
    if(v2_x_screen > max_x) { max_x = v2_x_screen; }
    if(max_x >= backbuffer_target.m_width) { max_x = backbuffer_target.m_width - 1; }

    int min_y = v0_y_screen;
    if(v1_y_screen < min_y) { min_y = v1_y_screen; }
    if(v2_y_screen < min_y) { min_y = v2_y_screen; }
    if(min_y < 0) { min_y = 0; }

    int max_y = v0_y_screen;
    if(v1_y_screen > max_y) { max_y = v1_y_screen; }
    if(v2_y_screen > max_y) { max_y = v2_y_screen; }
    if(max_y >= backbuffer_target.m_height) { max_y = backbuffer_target.m_height - 1; }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Draw pixels within bounding box.
    //---------------------------------------------------------------------------------------------------------------------//
    float bx_minus_ax = (float)(v1_x_screen - v0_x_screen);
    float by_minus_ay = (float)(v1_y_screen - v0_y_screen);

    float cx_minus_ax = (float)(v2_x_screen - v0_x_screen);
    float cy_minus_ay = (float)(v2_y_screen - v0_y_screen);

    for(int y = min_y; y <= max_y; y++)
    {
        for(int x = min_x; x <= max_x; x++)
        {
            //-------------------------------------------------------------------------------------------------------------//
            float ay_minus_py = (float)(v0_y_screen - y);
            float px_minus_ax = (float)(x - v0_x_screen);

            float w1_denominator = (bx_minus_ax * cy_minus_ay) - (by_minus_ay * cx_minus_ax);
            if(w1_denominator == 0.0f) { continue; }

            float w1 = ( (cx_minus_ax * ay_minus_py) + (cy_minus_ay * px_minus_ax) ) / w1_denominator;
            if(w1 < 0.0f) { continue; }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            float ax_minus_px = (float)(v0_x_screen - x);
            float py_minus_ay = (float)(y - v0_y_screen);

            float w2_denominator = (by_minus_ay * cx_minus_ax) - (bx_minus_ax * cy_minus_ay);
            if(w2_denominator == 0.0f) { continue; }

            float w2 = ( (ay_minus_py * bx_minus_ax) + (px_minus_ax * by_minus_ay) ) / w2_denominator;
            if(w2 < 0.0f) { continue; }
            //-------------------------------------------------------------------------------------------------------------//

            //-------------------------------------------------------------------------------------------------------------//
            float w0 = 1.0f - w1 - w2;
            if(w0 < 0.0f) { continue; }
            //-------------------------------------------------------------------------------------------------------------//

            float z = (w0 * v0_z) + (w1 * v1_z) + (w2 * v2_z);
            uint32_t color = mixColor(v0_color, w0, v1_color, w1, v2_color, w2);
            backbuffer_target.setPixel(x, y, z, color);
        }
    }
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
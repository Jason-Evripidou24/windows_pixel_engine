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
    // Triangle edges.
    //---------------------------------------------------------------------------------------------------------------------//
    struct Vec3f
    {
        float m_data[3];
        Vec3f(float x, float y, float z) { m_data[0] = x; m_data[1] = y; m_data[2] = z; }
    };
    struct Vec2f
    {
        float m_data[2];
        Vec2f(float x, float y) { m_data[0] = x; m_data[1] = y; }
    };

    auto dotProduct = [](const Vec2f& a, const Vec2f& b)
    {
        return (a.m_data[0] * b.m_data[0]) + (a.m_data[1] * b.m_data[1]);
    };

    // Point = (x, y) + w1(edge0to1) + w2(edge0to2)
    // PointX = x + w1(v1_x_screen - v0_x_screen) + w2(v1_y_screen - v0_y_screen)
    // PointY = y + w1(v2_x_screen - v0_x_screen) + w2(v2_y_screen - v0_y_screen)

    Vec2f edge0to1(v1_x_screen - v0_x_screen, v1_y_screen - v0_y_screen);
    Vec2f edge0to2(v2_x_screen - v0_x_screen, v2_y_screen - v0_y_screen);


    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Draw pixels within bounding box.
    //---------------------------------------------------------------------------------------------------------------------//
    for(int y = min_y; y <= max_y; y++)
    {
        for(int x = min_x; x <= max_x; x++)
        {
            //-------------------------------------------------------------------------------------------------------------//
            float ay_minus_py = (float)(v0_y_screen - y);

            float bx_minus_ax = (float)(v1_x_screen - v0_x_screen);
            float by_minus_ay = (float)(v1_y_screen - v0_y_screen);

            float cx_minus_ax = (float)(v2_x_screen - v0_x_screen);
            float cy_minus_ay = (float)(v2_y_screen - v0_y_screen);

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

            if((w1 + w2) > 1.0f) { continue; }

            backbuffer_target.setPixel(x, y, 0.0f, 0xFF000000);
        }
    }
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
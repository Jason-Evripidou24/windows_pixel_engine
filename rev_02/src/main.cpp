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
#include "00_types/level_00/pixel/pixel.hpp"
#include "00_types/level_00/mat4/mat4_f.hpp"
#include "00_types/level_00/vec2/vec2_f.hpp"
#include "00_types/level_00/vec2/vec2_i.hpp"
#include "00_types/level_00/vec3/vec3_f.hpp"
#include "00_types/level_00/vec4/vec4_f.hpp"

#include "00_types/level_01/vertex3_f/vertex3_f.hpp"

#include "01_window/window.hpp"
#include "01_window/backbuffer/backbuffer.hpp"
#include "01_window/input/input.hpp"

#include "02_rendering/renderer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Window window;
    if(!window.create(L"Pixel Engine", 800, 600, 4, hInstance))
    {
        return -1;
    }

    Renderer renderer;

    while(window.processMessages())
    {
        Vertex3_f square_top_left;
        square_top_left.m_position = Vec3_f(-0.5f, 0.5f, 0.0f);
        square_top_left.m_color = Pixel(255, 255, 0, 255);

        Vertex3_f square_top_right;
        square_top_right.m_position = Vec3_f(0.5f, 0.5f, 0.0f);
        square_top_right.m_color = Pixel(0, 255, 255, 255);

        Vertex3_f square_bot_left;
        square_bot_left.m_position = Vec3_f(-0.5f, -0.5f, 0.0f);
        square_bot_left.m_color = Pixel(255, 0, 255, 255);

        Vertex3_f square_bot_right;
        square_bot_right.m_position = Vec3_f(0.5f, -0.5f, 0.0f);
        square_bot_right.m_color = Pixel(255, 255, 255, 255);

        renderer.clear(&(window.m_backbuffer), Pixel(0, 0, 0, 0));

        renderer.drawWireframeTriangle(&(window.m_backbuffer), square_top_left, square_top_right, square_bot_left);
        renderer.drawWireframeTriangle(&(window.m_backbuffer), square_bot_left, square_top_right, square_bot_right);

        window.present();
    }

    window.destroy();
    return EXIT_SUCCESS;
}
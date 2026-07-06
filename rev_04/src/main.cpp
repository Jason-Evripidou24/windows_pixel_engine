// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <string>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
#include <windows.h>
#include <windowsx.h>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "backbuffer/backbuffer.hpp"
#include "math/vec3_f.hpp"
#include "math/line3d.hpp"
#include "renderer/renderer.hpp"
#include "window/window.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Window window;
    if(!window.create(L"Pixel Engine", 600, 600, hInstance))
    {
        return -1;
    }

    Backbuffer backbuffer;
    backbuffer.resize(window.m_width, window.m_height);

    Renderer renderer;

    while(window.processMessages())
    {
        backbuffer.clear(0x00000000);

        //-----------------------------------------------------------------------------------------------------------------//
        // Draw lines at x = {-1.0, -0.8, -0.6, ..., 0.0, 0.2, 0.4, ..., 1.0}
        //-----------------------------------------------------------------------------------------------------------------//
        renderer.drawLine(&backbuffer, -1.0f, 1.0f, 0.0f, 0x99FFFF0000, -1.0f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, -0.8f, 1.0f, 0.0f, 0x99FFFF0000, -0.8f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, -0.6f, 1.0f, 0.0f, 0x99FFFF0000, -0.6f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, -0.4f, 1.0f, 0.0f, 0x99FFFF0000, -0.4f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, -0.2f, 1.0f, 0.0f, 0x99FFFF0000, -0.2f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, 0.0f, 1.0f, 0.0f, 0x99FFFF0000, 0.0f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, 0.2f, 1.0f, 0.0f, 0x99FFFF0000, 0.2f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, 0.4f, 1.0f, 0.0f, 0x99FFFF0000, 0.4f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, 0.6f, 1.0f, 0.0f, 0x99FFFF0000, 0.6f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, 0.8f, 1.0f, 0.0f, 0x99FFFF0000, 0.8f, -1.0f, 0.0f, 0x99FFFF0000);
        renderer.drawLine(&backbuffer, 1.0f, 1.0f, 0.0f, 0x99FFFF0000, 1.0f, -1.0f, 0.0f, 0x99FFFF0000);
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Draw lines at y = {-1.0, -0.8, -0.6, ..., 0.0, 0.2, 0.4, ..., 1.0}
        //-----------------------------------------------------------------------------------------------------------------//
        renderer.drawLine(&backbuffer, -1.0f, -1.0f, 0.0f, 0x99FF00FF00, 1.0f, -1.0f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, -0.8f, 0.0f, 0x99FF00FF00, 1.0f, -0.8f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, -0.6f, 0.0f, 0x99FF00FF00, 1.0f, -0.6f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, -0.4f, 0.0f, 0x99FF00FF00, 1.0f, -0.4f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, -0.2f, 0.0f, 0x99FF00FF00, 1.0f, -0.2f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, 0.0f, 0.0f, 0x99FF00FF00, 1.0f, 0.0f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, 0.2f, 0.0f, 0x99FF00FF00, 1.0f, 0.2f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, 0.4f, 0.0f, 0x99FF00FF00, 1.0f, 0.4f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, 0.6f, 0.0f, 0x99FF00FF00, 1.0f, 0.6f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, 0.8f, 0.0f, 0x99FF00FF00, 1.0f, 0.8f, 0.0f, 0x99FF00FF00);
        renderer.drawLine(&backbuffer, -1.0f, 1.0f, 0.0f, 0x99FF00FF00, 1.0f, 1.0f, 0.0f, 0x99FF00FF00);
        //-----------------------------------------------------------------------------------------------------------------//

        renderer.drawLine
        (
            &backbuffer,
            -0.5f,
            0.5f,
            0.0f,
            0x99FF0000,
            0.5f,
            -0.5f,
            0.9f,
            0x990000FF
        );

        Math::Line3d test_line;
        test_line.m_start = Math::Vec3_f(-0.8f, -0.7f, -1.0f);
        uint32_t test_line_start_color = 0x99FFFF00;
        test_line.m_end = Math::Vec3_f(0.8f, -0.7f, 1.0f);
        uint32_t test_line_end_color = 0x9900FFFF;
        renderer.drawLine(&backbuffer, test_line, test_line_start_color, test_line_end_color);

        renderer.drawWireframeTriangle
        (
            &backbuffer,
            Math::Vec3_f(0.0f, 0.8f, 0.8f),
            0xFFFFFF00,
            Math::Vec3_f(-0.7f, -0.8f, 0.8f),
            0xFFFFFF00,
            Math::Vec3_f(0.7f, -0.8f, 0.8f),
            0xFFFFFF00
        );

        Math::Vec3_f test_vec3_f(1.03424f, 123.1342f, -4.387456435);
        std::string test_string_01 = test_vec3_f.toString(6, 2);
        backbuffer.setText(0, 150, test_string_01.c_str(), test_string_01.size(), 0x99FFFFFFFF);

        std::string test_string_02 = std::string("Hello Everybody, \nit's jason!!!");
        backbuffer.setText(10, 5, test_string_02.c_str(), test_string_02.size(), 0x99FFFFFFFF);

        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
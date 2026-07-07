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
    if(!window.create(L"Pixel Engine", 1000, 600, hInstance)) { return -1; }

    Backbuffer backbuffer;
    backbuffer.resize(window.m_width, window.m_height);

    Renderer renderer;

    while(window.processMessages())
    {
        backbuffer.clear(0x00000000);

        //-----------------------------------------------------------------------------------------------------------------//
        // Draw lines at x = {-1.0, -0.8, -0.6, ..., 0.0, 0.2, 0.4, ..., 1.0}
        //-----------------------------------------------------------------------------------------------------------------//
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(-1.0f, -1.0f, 0.0f), 0xFFFFFF0000);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-0.8f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(-0.8f, -1.0f, 0.0f), 0xFFFFFF0000);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-0.6f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(-0.6f, -1.0f, 0.0f), 0xFFFFFF0000);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-0.4f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(-0.4f, -1.0f, 0.0f), 0xFFFFFF0000);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-0.2f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(-0.2f, -1.0f, 0.0f), 0xFFFFFF0000);
        renderer.drawLine(&backbuffer, Math::Vec3_f(0.0f, 1.0f, 0.0f), 0xFFFFFFFFFF, Math::Vec3_f(0.0f, -1.0f, 0.0f), 0xFFFFFFFFFF);
        renderer.drawLine(&backbuffer, Math::Vec3_f(0.2f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(0.2f, -1.0f, 0.0f), 0xFFFFFF0000);
        renderer.drawLine(&backbuffer, Math::Vec3_f(0.4f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(0.4f, -1.0f, 0.0f), 0xFFFFFF0000);
        renderer.drawLine(&backbuffer, Math::Vec3_f(0.6f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(0.6f, -1.0f, 0.0f), 0xFFFFFF0000);
        renderer.drawLine(&backbuffer, Math::Vec3_f(0.8f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(0.8f, -1.0f, 0.0f), 0xFFFFFF0000);
        renderer.drawLine(&backbuffer, Math::Vec3_f(1.0f, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(1.0f, -1.0f, 0.0f), 0xFFFFFF0000);
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Draw lines at y = {-1.0, -0.8, -0.6, ..., 0.0, 0.2, 0.4, ..., 1.0}
        //-----------------------------------------------------------------------------------------------------------------//
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, -1.0f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, -1.0f, 0.0f), 0xFFFF00FF00);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, -0.8f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, -0.8f, 0.0f), 0xFFFF00FF00);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, -0.6f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, -0.6f, 0.0f), 0xFFFF00FF00);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, -0.4f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, -0.4f, 0.0f), 0xFFFF00FF00);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, -0.2f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, -0.2f, 0.0f), 0xFFFF00FF00);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, 0.0f, 0.0f), 0xFFFFFFFFFF, Math::Vec3_f(1.0f, 0.0f, 0.0f), 0xFFFFFFFFFF);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, 0.2f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, 0.2f, 0.0f), 0xFFFF00FF00);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, 0.4f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, 0.4f, 0.0f), 0xFFFF00FF00);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, 0.6f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, 0.6f, 0.0f), 0xFFFF00FF00);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, 0.8f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, 0.8f, 0.0f), 0xFFFF00FF00);
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, 1.0f, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, 1.0f, 0.0f), 0xFFFF00FF00);
        //-----------------------------------------------------------------------------------------------------------------//

        Math::Vec3_f rectangle_p0 = Math::Vec3_f(-0.7f, 0.7f, 0.1f);
        Math::Vec3_f rectangle_p1 = Math::Vec3_f(-0.7f, -0.7f, 0.1f);
        Math::Vec3_f rectangle_p2 = Math::Vec3_f(0.7f, -0.7f, 0.1f);
        Math::Vec3_f rectangle_p3 = Math::Vec3_f(0.7f, 0.7f, 0.1f);

        renderer.drawWireframeTriangle(&backbuffer, rectangle_p0, 0xFFFFFF00, rectangle_p1, 0xFFFFFF00, rectangle_p2, 0xFFFFFF00);
        renderer.drawWireframeTriangle(&backbuffer, rectangle_p0, 0xFFFFFF00, rectangle_p2, 0xFFFFFF00, rectangle_p3, 0xFFFFFF00);

        std::string info_string = std::string("Point 0: ");
        backbuffer.setText(10, 10, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);
        info_string = rectangle_p0.toString(10, 4);
        backbuffer.setText(100, 10, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);

        info_string = std::string("Point 1: ");
        backbuffer.setText(10, 20, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);
        info_string = rectangle_p1.toString(10, 4);
        backbuffer.setText(100, 20, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);

        info_string = std::string("Point 2: ");
        backbuffer.setText(10, 30, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);
        info_string = rectangle_p2.toString(10, 4);
        backbuffer.setText(100, 30, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);

        info_string = std::string("Point 3: ");
        backbuffer.setText(10, 40, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);
        info_string = rectangle_p3.toString(10, 4);
        backbuffer.setText(100, 40, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);

        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
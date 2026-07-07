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
#include "math/math.hpp"
#include "renderer/renderer.hpp"
#include "window/window.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Window window;
    if(!window.create(L"Pixel Engine", 1600, 900, hInstance)) { return -1; }

    Backbuffer backbuffer;
    backbuffer.resize(window.m_width, window.m_height);

    Renderer renderer;

    while(window.processMessages())
    {
        backbuffer.clear(0x00000000);

        //-----------------------------------------------------------------------------------------------------------------//
        // Draw lines at x = {-1.0, -0.8, -0.6, ..., 0.0, 0.2, 0.4, ..., 1.0}
        //-----------------------------------------------------------------------------------------------------------------//
        float x = 0.5f;
        renderer.drawLine(&backbuffer, Math::Vec3_f(x, 1.0f, 0.0f), 0xFFFFFF0000, Math::Vec3_f(x, -1.0f, 0.0f), 0xFFFFFF0000);
        /*
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
        */
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Draw lines at y = {-1.0, -0.8, -0.6, ..., 0.0, 0.2, 0.4, ..., 1.0}
        //-----------------------------------------------------------------------------------------------------------------//
        float y = -0.5f;
        renderer.drawLine(&backbuffer, Math::Vec3_f(-1.0f, y, 0.0f), 0xFFFF00FF00, Math::Vec3_f(1.0f, y, 0.0f), 0xFFFF00FF00);
        /*
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
        */
        //-----------------------------------------------------------------------------------------------------------------//
        
        Math::Vec4_f rectangle_p0 = Math::Vec4_f(-0.5f, 0.5f, 0.0f, 1.0f);
        Math::Vec4_f rectangle_p1 = Math::Vec4_f(-0.5f, -0.5f, 0.0f, 1.0f);
        Math::Vec4_f rectangle_p2 = Math::Vec4_f(0.5f, -0.5f, 0.0f, 1.0f);
        Math::Vec4_f rectangle_p3 = Math::Vec4_f(0.5f, 0.5f, 0.0f, 1.0f);

        Math::Mat4_f translate = Math::translationMat4_f(0.5f, -0.5f, 0.0f);
        static float scale_factor = 1.0f;
        static float increasing = -1.0f;
        if(scale_factor < 0.8f) { increasing = 1.0f; }
        if(scale_factor > 1.0f) { increasing = -1.0f; }
        scale_factor += (0.0001f * increasing);
        Math::Mat4_f scale = Math::scaleMat4_f(scale_factor, scale_factor, scale_factor);
        static float angle = 0.0f;
        angle += 0.005f;   // radians per frame
        Math::Mat4_f rotate = Math::rotationMat4_f(1.0f, 1.0f, 1.0f, angle);
        Math::Mat4_f model = translate * rotate * scale;

        rectangle_p0 = model * rectangle_p0;
        rectangle_p1 = model * rectangle_p1;
        rectangle_p2 = model * rectangle_p2;
        rectangle_p3 = model * rectangle_p3;

        Math::Vec3_f p0_clip = Math::Vec3_f(rectangle_p0.m_data[0], rectangle_p0.m_data[1], rectangle_p0.m_data[2]);
        Math::Vec3_f p1_clip = Math::Vec3_f(rectangle_p1.m_data[0], rectangle_p1.m_data[1], rectangle_p1.m_data[2]);
        Math::Vec3_f p2_clip = Math::Vec3_f(rectangle_p2.m_data[0], rectangle_p2.m_data[1], rectangle_p2.m_data[2]);
        Math::Vec3_f p3_clip = Math::Vec3_f(rectangle_p3.m_data[0], rectangle_p3.m_data[1], rectangle_p3.m_data[2]);

        renderer.drawWireframeTriangle(&backbuffer, p0_clip, 0xFFFFFF00, p1_clip, 0xFFFFFF00, p2_clip, 0xFFFFFF00);
        renderer.drawWireframeTriangle(&backbuffer, p0_clip, 0xFFFFFF00, p2_clip, 0xFFFFFF00, p3_clip, 0xFFFFFF00);

        std::string info_string = std::string("Point 0: ");
        backbuffer.setText(10, 10, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);
        info_string = rectangle_p0.toStringRow(10, 4);
        backbuffer.setText(100, 10, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);

        info_string = std::string("Point 1: ");
        backbuffer.setText(10, 20, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);
        info_string = rectangle_p1.toStringRow(10, 4);
        backbuffer.setText(100, 20, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);

        info_string = std::string("Point 2: ");
        backbuffer.setText(10, 30, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);
        info_string = rectangle_p2.toStringRow(10, 4);
        backbuffer.setText(100, 30, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);

        info_string = std::string("Point 3: ");
        backbuffer.setText(10, 40, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);
        info_string = rectangle_p3.toStringRow(10, 4);
        backbuffer.setText(100, 40, info_string.c_str(), info_string.size(), 0x99FFFFFFFF);

        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
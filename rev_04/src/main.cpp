// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <string>
#include <vector>
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
        float x = 0.0f;
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
        float y = 0.0f;
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

        static std::vector<Math::Vec4_f> cube_verts(8);
        cube_verts[0] = Math::Vec4_f(-0.5f, 0.5f, 0.5f, 1.0f);
        cube_verts[1] = Math::Vec4_f(-0.5f, -0.5f, 0.5f, 1.0f);
        cube_verts[2] = Math::Vec4_f(0.5f, -0.5f, 0.5f, 1.0f);
        cube_verts[3] = Math::Vec4_f(0.5f, 0.5f, 0.5f, 1.0f);
        cube_verts[4] = Math::Vec4_f(-0.5f, 0.5f, -0.5f, 1.0f);
        cube_verts[5] = Math::Vec4_f(-0.5f, -0.5f, -0.5f, 1.0f);
        cube_verts[6] = Math::Vec4_f(0.5f, -0.5f, -0.5f, 1.0f);
        cube_verts[7] = Math::Vec4_f(0.5f, 0.5f, -0.5f, 1.0f);

        static std::vector<Math::Vec3_i> cube_triangles(12);
        // Front Face.
        cube_triangles[0] = Math::Vec3_i(0, 1, 2);
        cube_triangles[1] = Math::Vec3_i(0, 2, 3);
        // Rear Face.
        cube_triangles[2] = Math::Vec3_i(7, 6, 5);
        cube_triangles[3] = Math::Vec3_i(7, 5, 4);
        // Top Face.
        cube_triangles[4] = Math::Vec3_i(4, 0, 3);
        cube_triangles[5] = Math::Vec3_i(4, 3, 7);
        // Bottom Face.
        cube_triangles[6] = Math::Vec3_i(1, 5, 6);
        cube_triangles[7] = Math::Vec3_i(1, 6, 2);
        // Left Face.
        cube_triangles[8] = Math::Vec3_i(4, 5, 1);
        cube_triangles[9] = Math::Vec3_i(4, 1, 0);
        // Right Face.
        cube_triangles[10] = Math::Vec3_i(3, 2, 6);
        cube_triangles[11] = Math::Vec3_i(3, 6, 7);


        Math::Mat4_f translate = Math::translationMat4_f(0.0f, 0.0f, 0.0f);
        static float scale_factor = 1.0f;
        static float increasing = -1.0f;
        if(scale_factor < 0.8f) { increasing = 1.0f; }
        if(scale_factor > 1.0f) { increasing = -1.0f; }
        scale_factor += (0.0001f * increasing);
        Math::Mat4_f scale = Math::scaleMat4_f(0.2f, 0.2f, 0.2f);
        static float angle = 0.0f;
        angle += 0.002f;   // radians per frame
        Math::Mat4_f rotate = Math::rotationMat4_f(0.0f, 1.0f, 1.0f, angle);
        Math::Mat4_f model = translate * rotate * scale;

        static std::vector<Math::Vec4_f> transformed_cube_verts(8);
        for(int i = 0; i < 8; i++)
        {
            transformed_cube_verts[i] = model * cube_verts[i];
        }

        for(int i = 0; i < 12; i++)
        {
            int index_0 = cube_triangles[i].m_data[0];
            Math::Vec4_f& transformed_vertex_0 = transformed_cube_verts[index_0];
            Math::Vec3_f p0_clip = Math::Vec3_f(transformed_vertex_0.m_data[0], transformed_vertex_0.m_data[1], transformed_vertex_0.m_data[2]);

            int index_1 = cube_triangles[i].m_data[1];
            Math::Vec4_f& transformed_vertex_1 = transformed_cube_verts[index_1];
            Math::Vec3_f p1_clip = Math::Vec3_f(transformed_vertex_1.m_data[0], transformed_vertex_1.m_data[1], transformed_vertex_1.m_data[2]);

            int index_2 = cube_triangles[i].m_data[2];
            Math::Vec4_f& transformed_vertex_2 = transformed_cube_verts[index_2];
            Math::Vec3_f p2_clip = Math::Vec3_f(transformed_vertex_2.m_data[0], transformed_vertex_2.m_data[1], transformed_vertex_2.m_data[2]);

            renderer.drawWireframeTriangle(&backbuffer, p0_clip, 0xFFFFFF00, p1_clip, 0xFFFFFF00, p2_clip, 0xFFFFFF00);
        }

        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
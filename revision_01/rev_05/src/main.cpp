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
#include "camera/camera.hpp"
#include "math/math.hpp"
#include "renderer/renderer.hpp"
#include "window/window.hpp"
#include "model/mesh.hpp"
#include "model/model.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
static Camera camera
(
    Math::Vec3_f(0.0f, 0.0f, 2.0f),
    Math::degreesToRadians(0.0f),
    Math::degreesToRadians(180.0f),
    Math::degreesToRadians(45.0f),
    0.2f,
    5.0f,
    Math::Vec3_f(0.0f, 1.0f, 0.0f)
);

static float mouse_pos_x = 0.0f;
static float mouse_pos_y = 0.0f;

static float camera_move_speed = 0.005f;
static float camera_look_speed = 0.002f;
void processInput(Window& window)
{
    //---------------------------------------------------------------------------------------------------------------------//
    // Keyboard.
    //---------------------------------------------------------------------------------------------------------------------//
    // Move camera along x
    if(window.m_input.isKeyDown('A') == true) { camera.moveRight(-camera_move_speed); }
    if(window.m_input.isKeyDown('D') == true) { camera.moveRight(camera_move_speed); }
    // Move camera along y
    if(window.m_input.isKeyDown('Q') == true) { camera.moveUp(camera_move_speed); }
    if(window.m_input.isKeyDown('E') == true) { camera.moveUp(-camera_move_speed); }
    // Move camera along z
    if(window.m_input.isKeyDown('W') == true) { camera.moveForward(camera_move_speed); }
    if(window.m_input.isKeyDown('S') == true) { camera.moveForward(-camera_move_speed); }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Mouse.
    //---------------------------------------------------------------------------------------------------------------------//
    float curr_mouse_pos_x = (float)window.m_input.m_mouse_x;
    float curr_mouse_pos_y = (float)window.m_input.m_mouse_y;

    if(window.m_input.isMouseDown(0) == true)
    {
        float mouse_dx = mouse_pos_x - curr_mouse_pos_x;
        float mouse_dy = mouse_pos_y - curr_mouse_pos_y;

        camera.lookRight(mouse_dx * camera_look_speed);
        camera.lookUp(mouse_dy * camera_look_speed);
    }
    mouse_pos_x = curr_mouse_pos_x;
    mouse_pos_y = curr_mouse_pos_y;
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    //---------------------------------------------------------------------------------------------------------------------//
    Math::Vec4_f triangle_0_pos = Math::Vec4_f(0.0f, 0.5f, -2.0f, 1.0f);
    uint32_t triangle_0_col = 0xFF000000;

    Math::Vec4_f triangle_1_pos = Math::Vec4_f(-0.5f, -0.5f, -2.0f, 1.0f);
    uint32_t triangle_1_col = 0xFF000000;

    Math::Vec4_f triangle_2_pos = Math::Vec4_f(0.5f, -0.5f, -2.0f, 1.0f);
    uint32_t triangle_2_col = 0xFF000000;

    Math::Triangle triangle;
    triangle.m_vertices[0].m_position = triangle_0_pos;
    triangle.m_vertices[0].m_color = triangle_0_col;
    triangle.m_vertices[1].m_position = triangle_1_pos;
    triangle.m_vertices[1].m_color = triangle_1_col;
    triangle.m_vertices[2].m_position = triangle_2_pos;
    triangle.m_vertices[2].m_color = triangle_2_col;
    //---------------------------------------------------------------------------------------------------------------------//

    Window window;
    if(!window.create(L"Pixel Engine", 1600, 900, hInstance)) { return -1; }

    Backbuffer backbuffer;
    backbuffer.resize(window.m_width, window.m_height);

    Renderer renderer;

    while(window.processMessages())
    {
        backbuffer.clear(0xFF87CEFA);

        processInput(window);

        Math::Mat4_f cam_projection = camera.calcProjectionMatrix((float)backbuffer.m_width / (float)backbuffer.m_height);
        Math::Mat4_f cam_view = camera.calcViewMatrix();
        Math::Mat4_f cam_proj_cam_view = cam_projection * cam_view;

        Math::Triangle triangle_transform = renderer.transformTriangle(triangle, cam_proj_cam_view);
        renderer.perspectiveDivideTriangle(triangle_transform);
        std::vector<Math::Triangle> triangles = renderer.clipTriangleMaxZ(triangle_transform, 0.5f);

        std::string info_string ="NUM TRIANGLES: " + std::to_string(triangles.size());
        backbuffer.setText(10, 10, info_string.c_str(), info_string.size(), 0xFF000000);

        info_string = triangle_transform.m_vertices[0].m_position.toStringRow(6, 2);
        backbuffer.setText(10, 30, info_string.c_str(), info_string.size(), 0xFF000000);
        info_string = triangle_transform.m_vertices[1].m_position.toStringRow(6, 2);
        backbuffer.setText(10, 40, info_string.c_str(), info_string.size(), 0xFF000000);
        info_string = triangle_transform.m_vertices[2].m_position.toStringRow(6, 2);
        backbuffer.setText(10, 50, info_string.c_str(), info_string.size(), 0xFF000000);

        for(int i = 0; i < triangles.size(); i++)
        {
            info_string = triangles[i].m_vertices[0].m_position.toStringRow(6, 2);
            backbuffer.setText(500, 10 + (i * 50), info_string.c_str(), info_string.size(), 0xFF000000);
            info_string = triangles[i].m_vertices[1].m_position.toStringRow(6, 2);
            backbuffer.setText(500, 20 + (i * 50), info_string.c_str(), info_string.size(), 0xFF000000);
            info_string = triangles[i].m_vertices[2].m_position.toStringRow(6, 2);
            backbuffer.setText(500, 30 + (i * 50), info_string.c_str(), info_string.size(), 0xFF000000);

            renderer.drawWireframeTriangle(backbuffer, triangles[i]);
        }
        
        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
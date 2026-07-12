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
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
static Camera camera
(
    Math::Vec3_f(0.0f, 0.0f, 5.0f),
    Math::degreesToRadians(0.0f),
    Math::degreesToRadians(180.0f),
    Math::degreesToRadians(45.0f),
    0.1f,
    10.0f,
    Math::Vec3_f(0.0f, 1.0f, 0.0f)
);

static float mouse_pos_x = 0.0f;
static float mouse_pos_y = 0.0f;

static float camera_move_speed = 0.002f;
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
    // Apex
    Math::Vertex pyramid_0_vertex;
    pyramid_0_vertex.m_position = Math::Vec4_f(0.0f, 0.5f, 3.0f, 1.0f);
    pyramid_0_vertex.m_color = 0xFFFF00FF; // Magenta
    // Base - Front Left
    Math::Vertex pyramid_1_vertex;
    pyramid_1_vertex.m_position = Math::Vec4_f(-0.5f, -0.5f, 3.5f, 1.0f);
    pyramid_1_vertex.m_color = 0xFFFFA500; // Orange
    // Base - Front Right
    Math::Vertex pyramid_2_vertex;
    pyramid_2_vertex.m_position = Math::Vec4_f(0.5f, -0.5f, 3.5f, 1.0f);
    pyramid_2_vertex.m_color = 0xFF87CEEB; // Sky Blue
    // Base - Back Right
    Math::Vertex pyramid_3_vertex;
    pyramid_3_vertex.m_position = Math::Vec4_f(0.5f, -0.5f, 2.5f, 1.0f);
    pyramid_3_vertex.m_color = 0xFF00FF00; // Green
    // Base - Back Left
    Math::Vertex pyramid_4_vertex;
    pyramid_4_vertex.m_position = Math::Vec4_f(-0.5f, -0.5f, 2.5f, 1.0f);
    pyramid_4_vertex.m_color = 0xFFFFFF00; // Yellow

    std::vector<Math::Triangle> pyramid_triangles(6);
    // Side faces
    pyramid_triangles[0].m_vertices[0] = pyramid_0_vertex;
    pyramid_triangles[0].m_vertices[1] = pyramid_1_vertex;
    pyramid_triangles[0].m_vertices[2] = pyramid_2_vertex;

    pyramid_triangles[1].m_vertices[0] = pyramid_0_vertex;
    pyramid_triangles[1].m_vertices[1] = pyramid_2_vertex;
    pyramid_triangles[1].m_vertices[2] = pyramid_3_vertex;

    pyramid_triangles[2].m_vertices[0] = pyramid_0_vertex;
    pyramid_triangles[2].m_vertices[1] = pyramid_3_vertex;
    pyramid_triangles[2].m_vertices[2] = pyramid_4_vertex;

    pyramid_triangles[3].m_vertices[0] = pyramid_0_vertex;
    pyramid_triangles[3].m_vertices[1] = pyramid_4_vertex;
    pyramid_triangles[3].m_vertices[2] = pyramid_1_vertex;

    // Base
    pyramid_triangles[4].m_vertices[0] = pyramid_1_vertex;
    pyramid_triangles[4].m_vertices[1] = pyramid_4_vertex;
    pyramid_triangles[4].m_vertices[2] = pyramid_3_vertex;

    pyramid_triangles[5].m_vertices[0] = pyramid_1_vertex;
    pyramid_triangles[5].m_vertices[1] = pyramid_3_vertex;
    pyramid_triangles[5].m_vertices[2] = pyramid_2_vertex;
    //---------------------------------------------------------------------------------------------------------------------//

    Window window;
    if(!window.create(L"Pixel Engine", 1600, 900, hInstance)) { return -1; }

    Backbuffer backbuffer;
    backbuffer.resize(window.m_width, window.m_height);

    Renderer renderer;

    while(window.processMessages())
    {
        //backbuffer.clear(0xEBCE87FF); // Sky blue
        backbuffer.clear(0xFF000000); // Black

        processInput(window);

        Math::Mat4_f cam_projection = camera.calcProjectionMatrix((float)backbuffer.m_width / (float)backbuffer.m_height);
        Math::Mat4_f cam_view = camera.calcViewMatrix();
        Math::Mat4_f cam_proj_cam_view = cam_projection * cam_view;

        for(int i = 0; i < pyramid_triangles.size(); i++)
        {
            Math::Triangle& triangle = pyramid_triangles[i];

            Math::Triangle triangle_transform = renderer.transformTriangle(triangle, cam_proj_cam_view);
            renderer.perspectiveDivideTriangle(triangle_transform);

            std::string info_string = triangle_transform.toString(6, 2);
            backbuffer.setText(10, 10 + (i * 100), info_string.c_str(), info_string.size(), 0xFFFFFFFF);

            //renderer.drawWireframeTriangle(backbuffer, triangle_transform);

            std::vector<Math::Triangle> triangles_transformed = renderer.clipTriangleBetweenY(triangle_transform, -1.0f, 1.0f);
            for(int j = 0; j < triangles_transformed.size(); j++)
            {
                renderer.drawWireframeTriangle(backbuffer, triangles_transformed[j]);
            }
        }

        /*
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
        */
        
        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
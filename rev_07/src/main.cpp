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
#include "utils/utils.hpp"
#include "model/mesh.hpp"
#include "model/model.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
static Camera camera
(
    Math::Vec3_f(0.0f, 0.0f, 5.0f),
    Math::convertDegreesToRadians(0.0f),
    Math::convertDegreesToRadians(180.0f),
    Math::convertDegreesToRadians(45.0f),
    0.1f,
    100.0f,
    Math::Vec3_f(0.0f, 1.0f, 0.0f)
);

static bool prev_zero_key = false;

static float mouse_pos_x = 0.0f;
static float mouse_pos_y = 0.0f;

static float camera_move_speed = 0.002f;
static float camera_look_speed = 0.002f;

static bool draw_filled = true;
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

    bool curr_zero_key = window.m_input.isKeyDown('0');
    if( (curr_zero_key == true) && (prev_zero_key == false) )
    {
        draw_filled = !draw_filled;
    }
    prev_zero_key = curr_zero_key;
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
    Mesh loaded_cube_mesh = Mesh::loadObjFile("../assets/cube/", "cube.obj");

    Model cube_model;
    cube_model.m_mesh = &loaded_cube_mesh;
    cube_model.m_position = Math::Vec3_f(0.0f, 0.0f, -5.0f);
    cube_model.m_scale = Math::Vec3_f(0.9f, 0.9f, 0.9f);
    cube_model.m_rotate_rad = Math::convertDegreesToRadians(0.0f);
    cube_model.m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    /*
                          number          number
                            3               2
    multiplier      1       3               2
                    20      60              40
                    100     300             200
                    300     900             600
                    350     1050            700
    */
    //---------------------------------------------------------------------------------------------------------------------//

    Window window;
    if(!window.create(L"Pixel Engine", 1050, 700, hInstance)) { return -1; }

    Backbuffer backbuffer;
    backbuffer.resize(window.m_width / 3, window.m_height / 3);

    Renderer renderer;

    Math::Mat4_f projection_matrix = camera.calcProjectionMatrix((float)backbuffer.m_width / (float)backbuffer.m_height);
    Math::Mat4_f view_matrix;
    Math::Mat4_f proj_view_matrix;

    while(window.processMessages())
    {
        //backbuffer.clear(0xEBCE87FF); // Sky blue
        backbuffer.clear(0xFF000000); // Black
        //backbuffer.clear(0xFFFFFFFF); // White

        processInput(window);
    
        view_matrix = camera.calcViewMatrix();
        proj_view_matrix = projection_matrix * view_matrix;

        renderer.drawModel(backbuffer, cube_model, proj_view_matrix, draw_filled);

        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
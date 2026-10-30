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

    std::vector<Model> cube_models(10);
    for(int i = 0; i < 10; i++)
    {
        cube_models[i].m_mesh = &loaded_cube_mesh;
        cube_models[i].m_scale = Math::Vec3_f(0.5f, 0.5f, 0.5f);
        cube_models[i].m_rotate_rad = Math::convertDegreesToRadians(20.0f * (float)i);
        cube_models[i].m_rotate_axis = Math::Vec3_f(1.0f, 0.3f, 0.5f);
    }
    cube_models[0].m_position = Math::Vec3_f( 0.0f,  0.0f,  0.0f);
    cube_models[1].m_position = Math::Vec3_f( 2.0f,  5.0f, -15.0f);
    cube_models[2].m_position = Math::Vec3_f(-1.5f, -2.2f, -2.5f);
    cube_models[3].m_position = Math::Vec3_f(-3.8f, -2.0f, -12.3f);
    cube_models[4].m_position = Math::Vec3_f( 2.4f, -0.4f, -3.5f);
    cube_models[5].m_position = Math::Vec3_f(-1.7f,  3.0f, -7.5f);
    cube_models[6].m_position = Math::Vec3_f( 1.3f, -2.0f, -2.5f);
    cube_models[7].m_position = Math::Vec3_f( 1.5f,  2.0f, -2.5f);
    cube_models[8].m_position = Math::Vec3_f( 1.5f,  0.2f, -1.5f);
    cube_models[9].m_position = Math::Vec3_f(-1.3f,  1.0f, -1.5f);
    //---------------------------------------------------------------------------------------------------------------------//

    Window window;
    if(!window.create(L"Pixel Engine", 1080, 720, hInstance)) { return -1; }

    Backbuffer backbuffer;
    backbuffer.resize(window.m_width / 2, window.m_height / 2);

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

        for(const Model& model : cube_models)
        {
            renderer.drawModel(backbuffer, model, proj_view_matrix, draw_filled);
        }

        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
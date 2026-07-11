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
#include "model/vertex.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
static Camera camera
(
    Math::Vec3_f(0.0f, 0.0f, 15.0f),
    Math::degreesToRadians(0.0f),
    Math::degreesToRadians(180.0f),
    Math::degreesToRadians(45.0f),
    1.0f,
    100.0f,
    Math::Vec3_f(0.0f, 1.0f, 0.0f)
);

static bool tracking_mouse = false;
static float mouse_pos_x = 0.0f;
static float mouse_pos_y = 0.0f;

static float camera_move_speed = 0.05f;
static float camera_look_speed = 0.002f;
void processInput(Window& window)
{
    // Move camera along x
    if(window.m_input.isKeyDown('A') == true) { camera.moveRight(-camera_move_speed); }
    if(window.m_input.isKeyDown('D') == true) { camera.moveRight(camera_move_speed); }
    // Move camera along y
    if(window.m_input.isKeyDown('Q') == true) { camera.moveUp(camera_move_speed); }
    if(window.m_input.isKeyDown('E') == true) { camera.moveUp(-camera_move_speed); }
    // Move camera along z
    if(window.m_input.isKeyDown('W') == true) { camera.moveForward(camera_move_speed); }
    if(window.m_input.isKeyDown('S') == true) { camera.moveForward(-camera_move_speed); }

    if(tracking_mouse == true)
    {
        // Stop tracking mouse if left mouse button is pressed.
        if(window.m_input.isMousePressed(0) == true)
        {
            tracking_mouse = false;
            mouse_pos_x = 0.0f;
            mouse_pos_y = 0.0f;
        }
        else
        {
            // Pitch camera up and down.
            float curr_mouse_pos_x = window.m_input.m_mouse_x;
            float curr_mouse_pos_y = window.m_input.m_mouse_y;

            float mouse_dx = mouse_pos_x - curr_mouse_pos_x;
            float mouse_dy = mouse_pos_y - curr_mouse_pos_y;

            camera.lookRight(mouse_dx * camera_look_speed);
            camera.lookUp(mouse_dy * camera_look_speed);

            mouse_pos_x = curr_mouse_pos_x;
            mouse_pos_y = curr_mouse_pos_y;
        }
    }
    else
    {
        // Start tracking mouse if left mouse button is pressed.
        if(window.m_input.isMousePressed(0) == true)
        {
            tracking_mouse = true;
            mouse_pos_x = window.m_input.m_mouse_x;
            mouse_pos_y = window.m_input.m_mouse_y;
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    //---------------------------------------------------------------------------------------------------------------------//
    Mesh road_mesh = Mesh::roadMesh(0xFF000000);
    Model road_model = Model();
    road_model.m_mesh = &road_mesh;
    road_model.m_position = Math::Vec3_f(0.0f, 0.0f, 0.0f);
    road_model.m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    road_model.m_rotate_rad = 0.0f;
    road_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    static std::vector<Mesh> cube_meshes(3);
    // Center cube.
    cube_meshes[0] = Mesh::cubeMesh(0xFFFFFF00);
    // Positive color.
    cube_meshes[1] = Mesh::cubeMesh(0xFF000000);
    // Negative color.
    cube_meshes[2] = Mesh::cubeMesh(0xFFFFFFFF);

    static std::vector<Model> cube_models(7);
    // Center cube.
    cube_models[0] = Model();
    cube_models[0].m_mesh = &(cube_meshes[0]);
    cube_models[0].m_position = Math::Vec3_f(0.0f, 0.0f, 0.0f);
    cube_models[0].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[0].m_rotate_rad = 0.0f;
    cube_models[0].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Positive x axis.
    cube_models[1] = Model();
    cube_models[1].m_mesh = &(cube_meshes[1]);
    cube_models[1].m_position = Math::Vec3_f(5.0f, 0.0f, 0.0f);
    cube_models[1].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[1].m_rotate_rad = 0.0f;
    cube_models[1].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Negative x axis.
    cube_models[2] = Model();
    cube_models[2].m_mesh = &(cube_meshes[2]);
    cube_models[2].m_position = Math::Vec3_f(-5.0f, 0.0f, 0.0f);
    cube_models[2].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[2].m_rotate_rad = 0.0f;
    cube_models[2].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Positive y axis.
    cube_models[3] = Model();
    cube_models[3].m_mesh = &(cube_meshes[1]);
    cube_models[3].m_position = Math::Vec3_f(0.0f, 5.0f, 0.0f);
    cube_models[3].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[3].m_rotate_rad = 0.0f;
    cube_models[3].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Negative y axis.
    cube_models[4] = Model();
    cube_models[4].m_mesh = &(cube_meshes[2]);
    cube_models[4].m_position = Math::Vec3_f(0.0f, -5.0f, 0.0f);
    cube_models[4].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[4].m_rotate_rad = 0.0f;
    cube_models[4].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Positive z axis.
    cube_models[5] = Model();
    cube_models[5].m_mesh = &(cube_meshes[1]);
    cube_models[5].m_position = Math::Vec3_f(0.0f, 0.0f, 5.0f);
    cube_models[5].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[5].m_rotate_rad = 0.0f;
    cube_models[5].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Negative z axis.
    cube_models[6] = Model();
    cube_models[6].m_mesh = &(cube_meshes[2]);
    cube_models[6].m_position = Math::Vec3_f(0.0f, 0.0f, -5.0f);
    cube_models[6].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[6].m_rotate_rad = 0.0f;
    cube_models[6].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
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

        static float angle = 0.0f;
        angle += 0.002f;   // radians per frame
        for(int i = 0; i < 7; i++)
        {
            cube_models[i].m_rotate_rad = angle;
            Math::Mat4_f model = cube_models[i].calcModelMatrix();
            renderer.drawModel(backbuffer, cube_models[i], cam_proj_cam_view);

            for(int i = 0; i < 100; i++)
            {
                road_model.m_position.m_data[2] = (float)i;
                renderer.drawModel(backbuffer, road_model, cam_proj_cam_view);
            }
        }

        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
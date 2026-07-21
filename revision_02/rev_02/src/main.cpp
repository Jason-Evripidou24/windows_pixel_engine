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
#include "timer/timer.hpp"
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

std::string controls_string =
    std::string("CONTROLS") + std::string("\n") +
    std::string("W/A                : ") + std::string("MOVE FORWARD/BACKWARD")                        + std::string("\n") +
    std::string("S/D                : ") + std::string("MOVE LEFT/RIGHT")                              + std::string("\n") +
    std::string("Q/E                : ") + std::string("MOVE UP/DOWN")                                 + std::string("\n") +
    std::string("LEFT MOUSE AND DRAG: ") + std::string("LOOK AROUND")                                  + std::string("\n") +
    std::string("0                  : ") + std::string("TOGGLE FILLED/WIREFRAME MODE")                 + std::string("\n") +
    std::string("1                  : ") + std::string("INCREASE MOVE SPEED")                          + std::string("\n") +
    std::string("2                  : ") + std::string("DECREASE MOVE SPEED")                          + std::string("\n") +
    std::string("8/9                : ") + std::string("CHANGE MIX BETWEEN VERTEX AND MATERIAL COLOR");

// Zero key toggles wireframe/filled mode.
static bool prev_zero_key = false;
static bool draw_filled = true;

// Eight and Nine keys change the color mix between vertex color and material color.
static bool prev_eight_key = false;
static bool prev_nine_key = false;
static float vertex_material_color_mix = 0.5f;

static float mouse_pos_x = 0.0f;
static float mouse_pos_y = 0.0f;

static float camera_move_speed = 1.0f;
static float camera_look_speed = 0.002f;

void processInput(Window& window, float delta_time)
{
    //---------------------------------------------------------------------------------------------------------------------//
    // Movement.
    //---------------------------------------------------------------------------------------------------------------------//
    float movement = camera_move_speed * delta_time;

    // Move camera along x
    if(window.m_input.isKeyDown('A') == true) { camera.moveRight(-movement); }
    if(window.m_input.isKeyDown('D') == true) { camera.moveRight(movement); }
    // Move camera along y
    if(window.m_input.isKeyDown('Q') == true) { camera.moveUp(movement); }
    if(window.m_input.isKeyDown('E') == true) { camera.moveUp(-movement); }
    // Move camera along z
    if(window.m_input.isKeyDown('W') == true) { camera.moveForward(movement); }
    if(window.m_input.isKeyDown('S') == true) { camera.moveForward(-movement); }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Wireframe and Filled mode.
    //---------------------------------------------------------------------------------------------------------------------//
    bool curr_zero_key = window.m_input.isKeyDown('0');
    if( (curr_zero_key == true) && (prev_zero_key == false) )
    {
        draw_filled = !draw_filled;
    }
    prev_zero_key = curr_zero_key;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Movement speed.
    //---------------------------------------------------------------------------------------------------------------------//
    if(window.m_input.isKeyDown('1') == true)
    {
        camera_move_speed += 0.1f;
    }
    if(window.m_input.isKeyDown('2') == true)
    {
        camera_move_speed -= 0.1f;
        if(camera_move_speed <= 0.0f) { camera_move_speed = 0.0f; }
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Color mixing between vertex color and material color.
    //---------------------------------------------------------------------------------------------------------------------//
    bool curr_eight_key = window.m_input.isKeyDown('8');
    if( (curr_eight_key == true) && (prev_eight_key == false) )
    {
        vertex_material_color_mix -= 0.1f;
        if(vertex_material_color_mix <= 0.0f) { vertex_material_color_mix = 0.0f; }
    }
    prev_eight_key = curr_eight_key;

    bool curr_nine_key = window.m_input.isKeyDown('9');
    if( (curr_nine_key == true) && (prev_nine_key == false) )
    {
        vertex_material_color_mix += 0.1f;
        if(vertex_material_color_mix >= 1.0f) { vertex_material_color_mix = 1.0f; }
    }
    prev_nine_key = curr_nine_key;
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
    for(size_t i = 0; i < 10; i++)
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

    Timer timer;
    timer.init();

    Window window;
    //if(!window.create(L"Pixel Engine", 1080, 720, hInstance)) { return -1; }
    if(!window.create(L"Pixel Engine", 1350, 900, hInstance)) { return -1; }

    Backbuffer backbuffer;
    int pixel_size = 2;
    int backbuffer_width = window.m_width / pixel_size;
    int backbuffer_height = window.m_height / pixel_size;
    backbuffer.resize(backbuffer_width, backbuffer_height);

    Renderer renderer(&backbuffer);

    Math::Mat4_f projection_matrix = camera.calcProjectionMatrix((float)backbuffer.m_width / (float)backbuffer.m_height);
    Math::Mat4_f view_matrix;
    Math::Mat4_f proj_view_matrix;

    while(window.processMessages())
    {
        timer.tick();

        //backbuffer.clear(0xEBCE87FF); // Sky blue
        backbuffer.clear(0xFF000000); // Black
        //backbuffer.clear(0xFFFFFFFF); // White

        processInput(window, timer.deltaTime);
    
        view_matrix = camera.calcViewMatrix();
        proj_view_matrix = projection_matrix * view_matrix;

        for(const Model& cube_model : cube_models)
        {
            std::queue<MaterialTriangle> model_material_triangles = cube_model.transformModelForRendering(proj_view_matrix);
            renderer.drawMaterialTriangles(model_material_triangles, draw_filled, vertex_material_color_mix);
        }

        std::string info_string = std::string("FPS: ") + std::to_string(timer.fps);
        backbuffer.setText(10, 10, info_string.c_str(), static_cast<int>(info_string.size()), 0xFFFFFFFF);
        backbuffer.setText(10, 360, controls_string.c_str(), static_cast<int>(controls_string.size()), 0xFFFFFFFF);

        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
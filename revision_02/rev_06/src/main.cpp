// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <random>
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
    Math::Vec3_f(0.0f, 1.7f, 5.0f),
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
    std::string("8/9                : ") + std::string("CHANGE VERTEX AND MATERIAL COLOR MIX");

// Zero key toggles wireframe/filled mode.
static bool prev_zero_key = false;
static bool draw_filled = true;

// Eight and Nine keys change the color mix between vertex color and material color.
static bool prev_eight_key = false;
static bool prev_nine_key = false;
static float vertex_material_color_mix = 1.0f;

static float mouse_pos_x = 0.0f;
static float mouse_pos_y = 0.0f;

static float camera_move_speed = 5.0f;
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
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> pos_dist(-19.8f, 19.8f);
    std::uniform_real_distribution<float> scale_dist(0.2f, 0.3f);
    std::uniform_real_distribution<float> rotation_dist(0.0f, 2.0f * 3.1415f);
    Mesh tree_mesh;
    tree_mesh.loadMeshObjAndMtlFiles(1, "tree_mesh", "../assets/tree_001/", "obj.obj");
    std::vector<Model> tree_models(10);

    for (size_t i = 0; i < tree_models.size(); i++)
    {
        tree_models[i] = Model(i, "tree_model", &tree_mesh);

        float scale = scale_dist(rng);

        tree_models[i].m_position = Math::Vec3_f(pos_dist(rng), 0.0f, pos_dist(rng));
        tree_models[i].m_scale = Math::Vec3_f(scale, scale, scale);

        tree_models[i].m_rotate_rad = rotation_dist(rng);
        tree_models[i].m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);
    }

    Mesh ground_mesh;
    ground_mesh.loadMeshObjAndMtlFiles(0, "ground_mesh", "../assets/ground/", "obj.obj");
    Model ground_model(11, "ground_model", &ground_mesh);
    ground_model.m_position = Math::Vec3_f(0.0f, 0.0f, 0.0f);
    ground_model.m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    ground_model.m_rotate_rad = 0.0f;
    ground_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Mesh cube_mesh;
    cube_mesh.loadMeshObjAndMtlFiles(6, "cube_mesh", "../assets/cube/", "obj.obj");
    Model cube_model(16, "cube_model", &cube_mesh);
    cube_model.m_position = Math::Vec3_f(0.0f, 2.0f, 0.0f);
    cube_model.m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_model.m_rotate_rad = 0.0f;
    cube_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Mesh car_001_mesh;
    car_001_mesh.loadMeshObjAndMtlFiles(2, "car_001_mesh", "../assets/car_001/", "obj.obj");
    Model car_model(12, "car_001_model", &car_001_mesh);
    car_model.m_position = Math::Vec3_f(-7.0f, 0.0f, 12.0f);
    car_model.m_scale = Math::Vec3_f(2.0f, 2.0f, 2.0f);
    car_model.m_rotate_rad = 0.0f;
    car_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Mesh house_001_mesh;
    house_001_mesh.loadMeshObjAndMtlFiles(3, "house_001_mesh", "../assets/house_001/", "obj.obj");
    Model house_001_model(13, "house_001_model", &house_001_mesh);
    house_001_model.m_position = Math::Vec3_f(-30.0f, 0.0f, 30.0f);
    house_001_model.m_scale = Math::Vec3_f(2.0f, 2.0f, 2.0f);
    house_001_model.m_rotate_rad = Math::convertDegreesToRadians(310.0f);
    house_001_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Mesh house_002_mesh;
    house_002_mesh.loadMeshObjAndMtlFiles(4, "house_002_mesh", "../assets/house_002/", "obj.obj");
    Model house_002_model(14, "house_002_model", &house_002_mesh);
    house_002_model.m_position = Math::Vec3_f(-30.0f, 0.0f, -30.0f);
    house_002_model.m_scale = Math::Vec3_f(2.0f, 2.0f, 2.0f);
    house_002_model.m_rotate_rad = Math::convertDegreesToRadians(220.0f);
    house_002_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Mesh house_003_mesh;
    house_003_mesh.loadMeshObjAndMtlFiles(5, "house_003_mesh", "../assets/house_003/", "obj.obj");
    Model house_003_model(15, "house_003_model", &house_003_mesh);
    house_003_model.m_position = Math::Vec3_f(20.0f, 1.5f, 20.0f);
    house_003_model.m_scale = Math::Vec3_f(3.0f, 3.0f, 3.0f);
    house_003_model.m_rotate_rad = Math::convertDegreesToRadians(220.0f);
    house_003_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);
    //---------------------------------------------------------------------------------------------------------------------//

    Timer timer;
    timer.init();

    struct presets
    {
        int m_window_width;
        int m_window_height;
        int m_pixel_size;
        int m_tile_split;
        int m_control_string_x;
        int m_control_string_y;
        presets
        (
            int window_width,
            int window_height,
            int pixel_size,
            int tile_split,
            int control_string_x,
            int control_string_y
        )
        :
        m_window_width(window_width),
        m_window_height(window_height),
        m_pixel_size(pixel_size),
        m_tile_split(tile_split),
        m_control_string_x(control_string_x),
        m_control_string_y(control_string_y)
        {}
    };
    presets preset_00(1400, 900, 1, 10, 10, 800);
    presets preset_01(1360, 900, 2, 10, 10, 360);
    presets& preset_to_use = preset_00;

    Window window;
    //if(!window.create(L"Pixel Engine", 1080, 720, hInstance)) { return -1; }
    if(!window.create(L"Pixel Engine", preset_to_use.m_window_width, preset_to_use.m_window_height, hInstance)) { return -1; }

    Backbuffer backbuffer;
    int backbuffer_width = window.m_width / preset_to_use.m_pixel_size;
    int backbuffer_height = window.m_height / preset_to_use.m_pixel_size;
    backbuffer.resize(backbuffer_width, backbuffer_height);

    Renderer renderer(&backbuffer, preset_to_use.m_tile_split); // Must divide backbuffer width and height perfectly.

    Math::Mat4_f projection_matrix = camera.calcProjectionMatrix((float)backbuffer.m_width / (float)backbuffer.m_height);
    Math::Mat4_f view_matrix;
    Math::Mat4_f proj_view_matrix;

    while(window.processMessages())
    {
        timer.tick();

        backbuffer.clear(0xFF87CEEB); // Sky blue
        //backbuffer.clear(0xFFFF0000); // Red
        //backbuffer.clear(0xFF000000); // Black
        //backbuffer.clear(0xFFFFFFFF); // White

        processInput(window, timer.deltaTime);
    
        view_matrix = camera.calcViewMatrix();
        proj_view_matrix = projection_matrix * view_matrix;

        std::thread t_00([&]() { renderer.drawModel(car_model, proj_view_matrix, draw_filled, vertex_material_color_mix); });
        std::thread t_01([&]() { renderer.drawModel(house_001_model, proj_view_matrix, draw_filled, vertex_material_color_mix); });
        std::thread t_02([&]() { renderer.drawModel(house_002_model, proj_view_matrix, draw_filled, vertex_material_color_mix); });
        std::thread t_03([&]() { renderer.drawModel(house_003_model, proj_view_matrix, draw_filled, vertex_material_color_mix); });
        for(size_t i = 0; i < tree_models.size(); i++)
        {
            renderer.drawModel(tree_models[i], proj_view_matrix, draw_filled, vertex_material_color_mix);
        }
        renderer.drawModel(ground_model, proj_view_matrix, draw_filled, vertex_material_color_mix);
        renderer.drawModel(cube_model, proj_view_matrix, draw_filled, vertex_material_color_mix);
        t_00.join();
        t_01.join();
        t_02.join();
        t_03.join();

        std::string info_string = std::string("FPS: ") + std::to_string(timer.fps);
        backbuffer.setText(10, 10, info_string.c_str(), static_cast<int>(info_string.size()), 0xFFFFFFFF);

        backbuffer.setText
        (
            preset_to_use.m_control_string_x,
            preset_to_use.m_control_string_y,
            controls_string.c_str(),
            static_cast<int>(controls_string.size()),
            0xFFFFFFFF
        );

        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
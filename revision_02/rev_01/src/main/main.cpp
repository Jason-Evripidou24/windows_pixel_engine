#include "../math/core/math_core.hpp"
#include "../math/camera/camera.hpp"
#include "../window/window.hpp"
#include "../renderer/renderer.hpp"
#include "../utils/timer/timer.hpp"
#include "../model/mesh/mesh.hpp"
#include "../model/model.hpp"

Math::Camera camera
(
    Math::Core::Vec3_f(0.0f, 1.7f, 0.0f),
    Math::Core::convertDegreesToRadians(0.0f),
    Math::Core::convertDegreesToRadians(180.0f),
    Math::Core::convertDegreesToRadians(45.0f),
    0.1f,
    100.0f,
    Math::Core::Vec3_f(0.0f, 1.0f, 0.0f)
);

static float mouse_pos_x = 0.0f;
static float mouse_pos_y = 0.0f;

static bool g_prev_1_key = false;
static bool g_prev_2_key = false;
static bool g_prev_3_key = false;
static bool g_prev_4_key = false;
static bool g_prev_5_key = false;
static bool g_prev_6_key = false;
static bool g_prev_7_key = false;
static bool g_prev_8_key = false;
static bool g_prev_9_key = false;
static bool g_prev_0_key = false;
static bool g_draw_filled = true;
void processInput(Window& window, float delta_time)
{   
    //---------------------------------------------------------------------------------------------------------------------//
    // Keyboard, rotating object.
    //---------------------------------------------------------------------------------------------------------------------//
    const float camera_speed = 5.0f;
    bool curr_w_key = window.m_input.isKeyDown('W');
    if(curr_w_key == true)
    {
        camera.moveForward(camera_speed * delta_time);
    }
    bool curr_s_key = window.m_input.isKeyDown('S');
    if(curr_s_key == true)
    {
        camera.moveForward(-camera_speed * delta_time);
    }
    bool curr_a_key = window.m_input.isKeyDown('A');
    if(curr_a_key == true)
    {
        camera.moveRight(-camera_speed * delta_time);
    }
    bool curr_d_key = window.m_input.isKeyDown('D');
    if(curr_d_key == true)
    {
        camera.moveRight(camera_speed * delta_time);
    }
    bool curr_q_key = window.m_input.isKeyDown('Q');
    if(curr_q_key == true)
    {
        camera.moveUp(camera_speed * delta_time);
    }
    bool curr_e_key = window.m_input.isKeyDown('E');
    if(curr_e_key == true)
    {
        camera.moveUp(-camera_speed * delta_time);
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Wireframe and Filled mode.
    //---------------------------------------------------------------------------------------------------------------------//
    bool curr_0_key = window.m_input.isKeyDown('0');
    if( (curr_0_key == true) && (g_prev_0_key == false) )
    {
        g_draw_filled = !g_draw_filled;
    }
    g_prev_0_key = curr_0_key;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Pixel size.
    //---------------------------------------------------------------------------------------------------------------------//
    bool curr_8_key = window.m_input.isKeyDown('8');
    if( (curr_8_key == true) && (g_prev_8_key == false) )
    {
        if(window.m_pixel_size > 1)
        {
            window.resizePixel(window.m_pixel_size - 1);
        }
    }
    g_prev_8_key = curr_8_key;

    bool curr_9_key = window.m_input.isKeyDown('9');
    if( (curr_9_key == true) && (g_prev_9_key == false) )
    {
        if( (window.m_pixel_size < window.m_width) && (window.m_pixel_size < window.m_height) )
        {
            window.resizePixel(window.m_pixel_size + 1);
        }
    }
    g_prev_9_key = curr_9_key;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Mouse.
    //---------------------------------------------------------------------------------------------------------------------//
    float camera_look_speed = 0.002f;

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Window window;
    if(!window.create(L"Pixel Engine", 1200, 800, 1, hInstance)) { return EXIT_FAILURE; }

    Timer timer;
    timer.init();

    //---------------------------------------------------------------------------------------------------------------------//
    std::shared_ptr<Mesh> backpack_mesh = std::make_shared<Mesh>(0, "backpack_mesh");
    backpack_mesh->loadMesh("../assets/backpack/", "obj.obj", "mtl.mtl", "");

    std::shared_ptr<Mesh> cube_mesh = std::make_shared<Mesh>(1, "cube_mesh");
    cube_mesh->loadMesh("../assets/cube/", "obj.obj", "mtl.mtl", "obj.obj");

    std::shared_ptr<Mesh> ground_mesh = std::make_shared<Mesh>(2, "ground_mesh");
    ground_mesh->loadMesh("../assets/ground/", "obj.obj", "mtl.mtl", "obj.obj");

    std::shared_ptr<Mesh> house_001_mesh = std::make_shared<Mesh>(3, "house_001_mesh");
    house_001_mesh->loadMesh("../assets/house_001/", "obj.obj", "mtl.mtl", "");

    std::shared_ptr<Mesh> house_002_mesh = std::make_shared<Mesh>(4, "house_002_mesh");
    house_002_mesh->loadMesh("../assets/house_002/", "obj.obj", "Bambo_House.mtl", "");

    std::shared_ptr<Mesh> house_003_mesh = std::make_shared<Mesh>(5, "house_003_mesh");
    house_003_mesh->loadMesh("../assets/house_003/", "obj.obj", "building_04.mtl", "");

    std::shared_ptr<Mesh> tree_mesh = std::make_shared<Mesh>(6, "tree_mesh");
    tree_mesh->loadMesh("../assets/tree_001/", "obj.obj", "Lowpoly_tree_sample.mtl", "obj.obj");

    std::shared_ptr<Mesh> truck_001_mesh = std::make_shared<Mesh>(7, "truck_001_mesh");
    truck_001_mesh->loadMesh("../assets/truck_001/", "rig.obj", "rig.mtl", "rig.obj");
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    Model ground_model
    (
        0,
        "ground_model",
        ground_mesh,
        Math::Core::Vec3_f(0.0f, 0.0f, 0.0f),
        Math::Core::Quaternion::fromAxisAngle(0.0f, 1.0f, 0.0f, 0.0f),
        Math::Core::Vec3_f(1.0f, 1.0f, 1.0f)
    );

    Model house_001_model
    (
        1,
        "house_001_model",
        house_001_mesh,
        Math::Core::Vec3_f(-30.0f, 0.0f, 30.0f),
        Math::Core::Quaternion::fromAxisAngle(0.0f, 1.0f, 0.0f, Math::Core::convertDegreesToRadians(310.0f)),
        Math::Core::Vec3_f(2.0f, 2.0f, 2.0f)
    );

    Model house_002_model
    (
        2,
        "house_002_model",
        house_002_mesh,
        Math::Core::Vec3_f(-30.0f, 0.0f, -30.0f),
        Math::Core::Quaternion::fromAxisAngle(0.0f, 1.0f, 0.0f, Math::Core::convertDegreesToRadians(220.0f)),
        Math::Core::Vec3_f(2.0f, 2.0f, 2.0f)
    );

    Model house_003_model
    (
        3,
        "house_003_model",
        house_003_mesh,
        Math::Core::Vec3_f(20.0f, 1.5f, 20.0f),
        Math::Core::Quaternion::fromAxisAngle(0.0f, 1.0f, 0.0f, Math::Core::convertDegreesToRadians(220.0f)),
        Math::Core::Vec3_f(3.0f, 3.0f, 3.0f)
    );
    //---------------------------------------------------------------------------------------------------------------------//

    Renderer renderer(20);

    while(window.processMessages())
    {
        timer.tick();
        processInput(window, timer.deltaTime);

        window.m_backbuffer->clear(0xFF87CEEB); // Sky blue

        float aspect_ratio = static_cast<float>(window.m_backbuffer->m_width) / static_cast<float>(window.m_backbuffer->m_height);
        Math::Core::Mat4_f proj_view_matrix = camera.calcProjectionMatrix(aspect_ratio) * camera.calcViewMatrix();

        //-----------------------------------------------------------------------------------------------------------------//
        // Render time.
        //-----------------------------------------------------------------------------------------------------------------//
        renderer.m_tile_renderer_system.m_tile_renderer_system_total_jobs_counter.resetCount();

        renderer.drawLocalSpaceModel(window.m_backbuffer, ground_model, proj_view_matrix, g_draw_filled);
        renderer.drawLocalSpaceModel(window.m_backbuffer, house_001_model, proj_view_matrix, g_draw_filled);
        renderer.drawLocalSpaceModel(window.m_backbuffer, house_002_model, proj_view_matrix, g_draw_filled);
        renderer.drawLocalSpaceModel(window.m_backbuffer, house_003_model, proj_view_matrix, g_draw_filled);

        std::string info_string = std::to_string(timer.fps);
        window.m_backbuffer->setText(10, 10, info_string.c_str(), static_cast<int>(info_string.size()), 0xFFFFFFFF);

        renderer.m_tile_renderer_system.m_tile_renderer_system_total_jobs_counter.waitUntilZero();
        //-----------------------------------------------------------------------------------------------------------------//
        
        window.presentBackbuffer();
    }

    return EXIT_SUCCESS;
}
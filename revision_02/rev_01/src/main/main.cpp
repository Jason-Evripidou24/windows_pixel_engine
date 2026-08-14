#include "../math/core/math_core.hpp"
#include "../window/window.hpp"
#include "../renderer/renderer.hpp"
#include "../utils/timer/timer.hpp"

static Math::Core::Quaternion rotation;

static float rotate_angle_axis_x = 0.0f;
static float rotate_angle_axis_y = 0.0f;
static float rotate_angle_axis_z = 0.0f;

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
void processInput(Window& window, float delta_time)
{
    //---------------------------------------------------------------------------------------------------------------------//
    //---------------------------------------------------------------------------------------------------------------------//
    const float speed = 1.0f;
    bool curr_w_key = window.m_input.isKeyDown('W');
    if(curr_w_key == true)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle(1.0f, 0.0f, 0.0f, speed * delta_time);
        rotation = rotation * delta;
    }
    bool curr_s_key = window.m_input.isKeyDown('S');
    if(curr_s_key == true)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle(1.0f, 0.0f, 0.0f, -speed * delta_time);
        rotation = rotation * delta;
    }

    bool curr_a_key = window.m_input.isKeyDown('A');
    if(curr_a_key == true)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle(0.0f, 0.0f, 1.0f, speed * delta_time);
        rotation = rotation * delta;
    }
    bool curr_d_key = window.m_input.isKeyDown('D');
    if(curr_d_key == true)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle(0.0f, 0.0f, 1.0f, -speed * delta_time);
        rotation = rotation * delta;
    }

    bool curr_q_key = window.m_input.isKeyDown('Q');
    if(curr_q_key == true)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle(0.0f, 1.0f, 0.0f, speed * delta_time);
        rotation = rotation * delta;
    }
    bool curr_e_key = window.m_input.isKeyDown('E');
    if(curr_e_key == true)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle(0.0f, 1.0f, 0.0f, -speed * delta_time);
        rotation = rotation * delta;
    }
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
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Window window;
    if(!window.create(L"Pixel Engine", 600, 600, 1, hInstance)) { return EXIT_FAILURE; }

    Timer timer;
    timer.init();

    Math::Geometry::Vertex top_left;
    top_left.m_position = Math::Core::Vec4_f(-0.5f, 0.5f, 0.0f, 1.0f);
    top_left.m_tex_coords = Math::Core::Vec2_f(0.0f, 0.0f);
    top_left.m_normal = Math::Core::Vec3_f(0.0f, 0.0f, 0.0f);
    top_left.m_color = Math::Core::Vec4_f(1.0f, 1.0f, 0.0f, 1.0f);

    Math::Geometry::Vertex top_right;
    top_right.m_position = Math::Core::Vec4_f(0.5f, 0.5f, 0.0f, 1.0f);
    top_right.m_tex_coords = Math::Core::Vec2_f(0.0f, 0.0f);
    top_right.m_normal = Math::Core::Vec3_f(0.0f, 0.0f, 0.0f);
    top_right.m_color = Math::Core::Vec4_f(1.0f, 1.0f, 0.0f, 1.0f);

    Math::Geometry::Vertex bot_left;
    bot_left.m_position = Math::Core::Vec4_f(-0.5f, -0.5f, 0.0f, 1.0f);
    bot_left.m_tex_coords = Math::Core::Vec2_f(0.0f, 0.0f);
    bot_left.m_normal = Math::Core::Vec3_f(0.0f, 0.0f, 0.0f);
    bot_left.m_color = Math::Core::Vec4_f(1.0f, 0.0f, 1.0f, 1.0f);

    Math::Geometry::Vertex bot_right;
    bot_right.m_position = Math::Core::Vec4_f(0.5f, -0.5f, 0.0f, 1.0f);
    bot_right.m_tex_coords = Math::Core::Vec2_f(0.0f, 0.0f);
    bot_right.m_normal = Math::Core::Vec3_f(0.0f, 0.0f, 0.0f);
    bot_right.m_color = Math::Core::Vec4_f(1.0f, 0.0f, 1.0f, 1.0f);

    Math::Geometry::Vertex top_left_transformed;
    Math::Geometry::Vertex top_right_transformed;
    Math::Geometry::Vertex bot_left_transformed;
    Math::Geometry::Vertex bot_right_transformed;

    Renderer renderer;

    while(window.processMessages())
    {
        timer.tick();
        processInput(window, timer.deltaTime);

        window.m_backbuffer.clear(0xFF87CEEB); // Sky blue

        rotation.normalise();
        Math::Core::Mat4_f rotate_matrix = rotation.toRotationMatrix();
        Math::Geometry::transformVertex(top_left_transformed, top_left, rotate_matrix);
        Math::Geometry::transformVertex(top_right_transformed, top_right, rotate_matrix);
        Math::Geometry::transformVertex(bot_left_transformed, bot_left, rotate_matrix);
        Math::Geometry::transformVertex(bot_right_transformed, bot_right, rotate_matrix);

        renderer.drawTriangle(window.m_backbuffer, top_left_transformed, bot_left_transformed, top_right_transformed);
        renderer.drawTriangle(window.m_backbuffer, bot_left_transformed, bot_right_transformed, top_right_transformed);

        std::string info_string = top_left_transformed.toString(6, 2);
        window.m_backbuffer.setText(10, 10, info_string.c_str(), info_string.size(), 0xFFFFFFFF);

        window.presentBackbuffer();
    }

    return EXIT_SUCCESS;
}
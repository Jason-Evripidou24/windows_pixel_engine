#include "../math/core/math_core.hpp"
#include "../window/window.hpp"
#include "../renderer/renderer.hpp"
#include "../utils/timer/timer.hpp"

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
void processInput(Window& window)
{
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

    Math::Core::Vec4_f top_left(-0.5f, 0.5f, 0.0f, 1.0f);
    Math::Core::Vec4_f top_right(0.5f, 0.5f, 0.0f, 1.0f);
    Math::Core::Vec4_f bot_left(-0.5f, -0.5f, 0.0f, 1.0f);
    Math::Core::Vec4_f bot_right(0.5f, -0.5f, 0.0f, 1.0f);

    Math::Core::Vec4_f top_left_transformed;
    Math::Core::Vec4_f top_right_transformed;
    Math::Core::Vec4_f bot_left_transformed;
    Math::Core::Vec4_f bot_right_transformed;

    float rotate_angle = 0.0f;

    Renderer renderer;

    while(window.processMessages())
    {
        timer.tick();
        processInput(window);

        window.m_backbuffer.clear(0xFF87CEEB); // Sky blue

        rotate_angle += timer.deltaTime * 1.0f;
        Math::Core::Quaternion rotate = Math::Core::Quaternion::fromAxisAngle(0.0f, 0.0f, 1.0f, rotate_angle);

        top_left_transformed = rotate.toRotationMatrix() * top_left;
        top_right_transformed = rotate.toRotationMatrix() * top_right;
        bot_left_transformed = rotate.toRotationMatrix() * bot_left;
        bot_right_transformed = rotate.toRotationMatrix() * bot_right;

        renderer.drawTriangle
        (
             window.m_backbuffer,
             top_left_transformed.m_data[0], top_left_transformed.m_data[1], top_left_transformed.m_data[2], 0xFFFF0000,
             bot_left_transformed.m_data[0], bot_left_transformed.m_data[1], bot_left_transformed.m_data[2], 0xFFFF0000,
             top_right_transformed.m_data[0], top_right_transformed.m_data[1], top_right_transformed.m_data[2], 0xFFFF0000
        );
        renderer.drawTriangle
        (
             window.m_backbuffer,
             bot_left_transformed.m_data[0], bot_left_transformed.m_data[1], bot_left_transformed.m_data[2], 0xFFFF0000,
             bot_right_transformed.m_data[0], bot_right_transformed.m_data[1], bot_right_transformed.m_data[2], 0xFFFF0000,
             top_right_transformed.m_data[0], top_right_transformed.m_data[1], top_right_transformed.m_data[2], 0xFFFF0000
        );

        std::string info_string = top_left_transformed.toStringRow(6, 2);
        window.m_backbuffer.setText(10, 10, info_string.c_str(), info_string.size(), 0xFFFFFFFF);

        window.presentBackbuffer();
    }

    return EXIT_SUCCESS;
}
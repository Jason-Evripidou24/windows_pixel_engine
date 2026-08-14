#include "../window/window.hpp"
#include "../renderer/renderer.hpp"

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

    Renderer renderer;

    while(window.processMessages())
    {
        processInput(window);

        window.m_backbuffer.clear(0xFF87CEEB); // Sky blue

        renderer.drawTriangle
        (
             window.m_backbuffer,
             0.0f,  0.5f, 0.0f, 0xFFFF0000,
            -0.5f, -0.5f, 0.0f, 0xFF00FF00,
             0.5f, -0.5f, 0.0f, 0xFF0000FF
        );

        window.presentBackbuffer();
    }

    return EXIT_SUCCESS;
}
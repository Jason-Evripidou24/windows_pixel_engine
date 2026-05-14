#include "../window/window.hpp"
#include "../renderer/renderer.hpp"
#include "../renderer/hud.hpp"
#include "../renderer/font.hpp"
#include "../input/input.hpp"
#include "../pixel/pixel.hpp"
#include "../timer/timer.hpp"
#include "../math/vec2/vec2_f.hpp"
#include "../math/math.hpp"

struct Player
{
    float x = 400.0f;
    float y = 300.0f;
};

// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{    
    Window window;
    if (!window.create(L"Pixel Engine", 800, 600, hInstance))
        return -1;

    Renderer renderer;
    renderer.init(&window.m_backbuffer);

    Input input;
    window.m_input = &input;

    Player player;
    Timer timer;
    timer.init();

    const float moveSpeed = 200.0f; // pixels per second

    AsciiFont ascii_font;
    Hud hud;

    while(window.processMessages())
    {
        // -----------------------------------
        // Timing
        // -----------------------------------
        timer.tick();
        float dt = timer.deltaTime;

        // -----------------------------------
        // Input frame start
        // -----------------------------------
        input.beginFrame();

        // -----------------------------------
        // Movement (frame-independent)
        // -----------------------------------
        if(input.isKeyDown(VK_LEFT) || input.isKeyDown('A')) { player.x -= moveSpeed * dt; }
        if(input.isKeyDown(VK_RIGHT) || input.isKeyDown('D')) { player.x += moveSpeed * dt; }
        if(input.isKeyDown(VK_UP) || input.isKeyDown('W')) { player.y -= moveSpeed * dt; }
        if(input.isKeyDown(VK_DOWN) || input.isKeyDown('S')) { player.y += moveSpeed * dt; }

        // -----------------------------------
        // Render
        // -----------------------------------
        renderer.clear(Pixel(0, 0, 0, 0));

        hud.drawText(renderer, 10, 10, "FPS:", Pixel(0, 255, 0, 0), ascii_font);
        hud.drawText(renderer, 60, 10, std::to_string(timer.fps).c_str(), Pixel(0, 255, 0, 0), ascii_font);

        renderer.drawFilledCircle( (int)player.x + 25, (int)player.y + 25, 25, Pixel(0, 0, 255, 0) );

        Vec4_f vertices[4] =
        {
            { -0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.0f, 1.0f },
            {  0.5f,  0.5f, 0.0f, 1.0f },
            { -0.5f,  0.5f, 0.0f, 1.0f }
        };
        int indices[6] =
        {
            0, 1, 2,   // triangle 1
            2, 3, 0    // triangle 2
        };

        //-----------------------------------------------------------------------------------------------------------------//
        // Math testing.
        //-----------------------------------------------------------------------------------------------------------------//
        static float x_pos = 0.0f;
        static float y_pos = 0.0f;
        static float z_pos = 0.0f;
        if(input.isKeyDown('A')) { x_pos -= dt; }
        if(input.isKeyDown('D')) { x_pos += dt; }
        if(input.isKeyDown('W')) { y_pos += dt; }
        if(input.isKeyDown('S')) { y_pos -= dt; }
        if(input.isKeyDown('Q')) { z_pos += dt; }
        if(input.isKeyDown('E')) { z_pos -= dt; }
        Mat4_f translate = Math::translationMat4_f(x_pos, y_pos, z_pos);
        hud.drawMat4_f(renderer, 10, 90, translate, Pixel(0, 255, 0, 0), ascii_font);

        static float scale_factor = 1.0f;
        if(input.isKeyDown(VK_UP)) { scale_factor += dt; }
        if(input.isKeyDown(VK_DOWN)) { scale_factor -= dt; }
        if(scale_factor < 0.1f) { scale_factor = 0.1f; } 
        Mat4_f scale = Math::scaleMat4_f(scale_factor, scale_factor, scale_factor);
        hud.drawMat4_f(renderer, 10, 140, scale, Pixel(0, 255, 0, 0), ascii_font);

        static float theta_rads = 0.0f;
        if(input.isKeyDown(VK_LEFT)) { theta_rads += dt; }
        if(input.isKeyDown(VK_RIGHT)) { theta_rads -= dt; }
        if(theta_rads >= 6.2831853f) { theta_rads -= 6.2831853f; }
        if(theta_rads <= -6.2831853f) { theta_rads += 6.2831853f; }
        Mat4_f rotate = Math::rotationMat4_f(1.0f, 0.0f, 0.0f, theta_rads);
        hud.drawMat4_f(renderer, 10, 190, rotate, Pixel(0, 255, 0, 0), ascii_font);

        Mat4_f model = Math::multiply(Math::multiply(translate, scale), rotate);

        Mat4_f perspective = Math::perspectiveMat4_f
        (
            0.785398f,
            window.m_backbuffer.m_width / window.m_backbuffer.m_height,
            0.1f,
            100.0f
        );

        //Mat4_f transform = Math::multiply(model, perspective);
        Mat4_f transform = Math::multiply(perspective, model);
        //-----------------------------------------------------------------------------------------------------------------//

        Vec4_f clip_vertices[4];
        for(int i = 0; i < 4; i++)
        {
            clip_vertices[i] =
            (
                Math::multiply(transform, vertices[i])
            );
        }

        Vec3_f ndc_vertices[4];
        for(int i = 0; i < 4; i++)
        {
            ndc_vertices[i] =
            (
                Math::clipCoordsToNormalisedDeviceCoords(clip_vertices[i])
            );
        }

        Vec3_f screen[4];
        for(int i = 0; i < 4; i++)
        {
            screen[i] = Math::normalisedDeviceCoordsToScreenCoords
            (
                ndc_vertices[i],
                window.m_backbuffer.m_width,
                window.m_backbuffer.m_height
            );
        }
        
        for(int i = 0; i < 6; i += 3)
        {
            renderer.drawWireframeTrigngle
            (
                screen[indices[i + 0]],
                screen[indices[i + 1]],
                screen[indices[i + 2]],
                Pixel(0, 255, 255, 0)
            );
        }
    
        window.present();
    }

    window.destroy();
    return 0;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
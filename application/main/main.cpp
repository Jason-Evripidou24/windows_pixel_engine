#include "../window/window.hpp"
#include "../renderer/renderer.hpp"
#include "../renderer/hud.hpp"
#include "../renderer/font.hpp"
#include "../input/input.hpp"
#include "../pixel/pixel.hpp"
#include "../timer/timer.hpp"
#include "../math/vec2/vec2_f.hpp"
#include "../math/math.hpp"
#include "../object/object.hpp"
#include "../object/mesh.hpp"

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

    Mesh cube_mesh = Mesh::createCubeMesh();
    Object cube_object = Object(&cube_mesh);

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
        cube_object.m_position = Vec3_f(x_pos, y_pos, z_pos);

        static float scale_factor = 1.0f;
        if(input.isKeyDown(VK_UP)) { scale_factor += dt; }
        if(input.isKeyDown(VK_DOWN)) { scale_factor -= dt; }
        if(scale_factor < 0.1f) { scale_factor = 0.1f; } 
        cube_object.m_scale = Vec3_f(scale_factor, scale_factor, scale_factor);

        static float theta_rads = 0.0f;
        if(input.isKeyDown(VK_LEFT)) { theta_rads += dt; }
        if(input.isKeyDown(VK_RIGHT)) { theta_rads -= dt; }
        if(theta_rads >= 6.2831853f) { theta_rads -= 6.2831853f; }
        if(theta_rads <= -6.2831853f) { theta_rads += 6.2831853f; }
        cube_object.m_rotation_theta_radians = theta_rads;

        Mat4_f perspective = Math::perspectiveMat4_f
        (
            0.785398f,
            window.m_backbuffer.m_width / window.m_backbuffer.m_height,
            0.1f,
            100.0f
        );

        renderer.drawObject(cube_object, Math::identityMat4_f(), perspective);
    
        window.present();
        //-----------------------------------------------------------------------------------------------------------------//
    }

    window.destroy();
    return 0;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
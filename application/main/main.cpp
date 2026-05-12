#include "../window/window.hpp"
#include "../renderer/renderer.hpp"
#include "../renderer/hud.hpp"
#include "../renderer/font.hpp"
#include "../input/input.hpp"
#include "../pixel/pixel.hpp"
#include "../timer/timer.hpp"

struct Player
{
    float x = 400.0f;
    float y = 300.0f;
};

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
        if (input.isKeyDown(VK_LEFT) || input.isKeyDown('A'))
            player.x -= moveSpeed * dt;

        if (input.isKeyDown(VK_RIGHT) || input.isKeyDown('D'))
            player.x += moveSpeed * dt;

        if (input.isKeyDown(VK_UP) || input.isKeyDown('W'))
            player.y -= moveSpeed * dt;

        if (input.isKeyDown(VK_DOWN) || input.isKeyDown('S'))
            player.y += moveSpeed * dt;

        // -----------------------------------
        // Render
        // -----------------------------------
        renderer.clear(Pixel(0, 0, 0, 0));

        hud.drawText(renderer, 10, 10, std::to_string(timer.fps).c_str(), Pixel(0, 255, 0, 0), ascii_font);
        hud.drawText(renderer, 10, 20, "hello this is jason", Pixel(0, 255, 0, 0), ascii_font);

        renderer.drawFilledRect(
            (int)player.x,
            (int)player.y,
            50,
            50,
            Pixel(0, 255, 0, 0)
        );

        renderer.drawCircle(
            (int)player.x + 25,
            (int)player.y + 25,
            25,
            Pixel(0, 0, 255, 0)
        );

        window.present();
    }

    window.destroy();
    return 0;
}
#include "../window/window.hpp"
#include "../renderer/renderer.hpp"
#include "../input/input.hpp"
#include "../pixel/pixel.hpp"

struct Player
{
    int x = 400;
    int y = 300;
    int speed = 5;
};

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE,
                   LPSTR,
                   int)
{
    Window window;
    if (!window.create(L"Pixel Engine", 800, 600, hInstance))
        return -1;

    Renderer renderer;
    renderer.init(&window.m_backbuffer);

    Input input;
    window.m_input = &input;

    Player player;

    while (window.processMessages())
    {
        // -----------------------------------
        // Input frame start (IMPORTANT)
        // -----------------------------------
        input.beginFrame();

        // -----------------------------------
        // Movement (input → game logic)
        // -----------------------------------
        if (input.isKeyDown(VK_LEFT) || input.isKeyDown('A'))
            player.x -= player.speed;

        if (input.isKeyDown(VK_RIGHT) || input.isKeyDown('D'))
            player.x += player.speed;

        if (input.isKeyDown(VK_UP) || input.isKeyDown('W'))
            player.y -= player.speed;

        if (input.isKeyDown(VK_DOWN) || input.isKeyDown('S'))
            player.y += player.speed;

        // -----------------------------------
        // Render
        // -----------------------------------
        renderer.clear(Pixel(0, 0, 0, 0));

        renderer.drawFilledRect(
            player.x,
            player.y,
            50,
            50,
            Pixel(0, 255, 0, 0)
        );

        // optional debug shape
        renderer.drawCircle(
            player.x + 25,
            player.y + 25,
            25,
            Pixel(0, 0, 255, 0)
        );

        window.present();
    }

    window.destroy();
    return 0;
}
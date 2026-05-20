// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "00_types/level_00/pixel/pixel.hpp"
#include "00_types/level_00/mat4/mat4_f.hpp"
#include "00_types/level_00/vec2/vec2_f.hpp"
#include "00_types/level_00/vec2/vec2_i.hpp"
#include "00_types/level_00/vec3/vec3_f.hpp"
#include "00_types/level_00/vec4/vec4_f.hpp"

#include "00_types/level_01/vertex3_f/vertex3_f.hpp"
#include "00_types/level_01/vertex4/vertex4_f.hpp"

#include "01_utils/math/math.hpp"
#include "01_utils/timer/timer.hpp"

#include "02_window/window.hpp"
#include "02_window/backbuffer/backbuffer.hpp"
#include "02_window/input/input.hpp"

#include "03_rendering/renderer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Window window;
    if(!window.create(L"Pixel Engine", 800, 600, 3, hInstance))
    {
        return -1;
    }

    Renderer renderer;

    Timer timer;
    timer.init();
    float totalTime = 0.0f;

    //---------------------------------------------------------------------------------------------------------------------//
    Vertex4_f square_top_left;
    square_top_left.m_position = Vec4_f(-0.5f, 0.5f, 0.0f, 1.0f);
    square_top_left.m_color = Pixel(255, 255, 0, 255);

    Vertex4_f square_top_right;
    square_top_right.m_position = Vec4_f(0.5f, 0.5f, 0.0f, 1.0f);
    square_top_right.m_color = Pixel(0, 255, 255, 255);

    Vertex4_f square_bot_left;
    square_bot_left.m_position = Vec4_f(-0.5f, -0.5f, 0.0f, 1.0f);
    square_bot_left.m_color = Pixel(255, 0, 255, 255);

    Vertex4_f square_bot_right;
    square_bot_right.m_position = Vec4_f(0.5f, -0.5f, 0.0f, 1.0f);
    square_bot_right.m_color = Pixel(255, 255, 255, 255);
    //---------------------------------------------------------------------------------------------------------------------//

    while(window.processMessages())
    {
        timer.tick();

        totalTime += timer.deltaTime;

        float tx = 0.5f * cosf(totalTime);
        float ty = 0.5f * sinf(totalTime);
        Mat4_f translate = Math::translationMat4_f(tx, 0.0f, 0.0f);

        float sx = 0.6f + 0.4f * sinf(totalTime);
        float sy = 0.6f + 0.4f * cosf(totalTime);
        Mat4_f scale = Math::scaleMat4_f(1.0f, 1.0f, 1.0f);
        
        float rz = totalTime;
        Vec3_f rotate_axis(0.0f, 1.0f, 1.0f);
        rotate_axis = Math::normalise(rotate_axis);
        Mat4_f rotate = Math::rotationMat4_f(rotate_axis.m_data[0], rotate_axis.m_data[1], rotate_axis.m_data[2], rz);

        Mat4_f model = Math::multiply(Math::multiply(translate, rotate), scale);


        Mat4_f view = Math::translationMat4_f(0.0f, 0.0f, -3.0f);


        Mat4_f perspective = Math::perspectiveMat4_f(0.7f, window.m_backbuffer.m_width / window.m_backbuffer.m_height, 0.1f, 100.0f);


        Mat4_f transform = Math::multiply(Math::multiply(perspective, view), model);


        Vertex3_f square_top_left_ndc;
        square_top_left_ndc.m_position = Math::clipCoordsToNormalisedDeviceCoords(Math::multiply(transform, square_top_left.m_position));
        square_top_left_ndc.m_color = square_top_left.m_color;

        Vertex3_f square_top_right_ndc;
        square_top_right_ndc.m_position = Math::clipCoordsToNormalisedDeviceCoords(Math::multiply(transform, square_top_right.m_position));
        square_top_right_ndc.m_color = square_top_right.m_color;

        Vertex3_f square_bot_left_ndc;
        square_bot_left_ndc.m_position = Math::clipCoordsToNormalisedDeviceCoords(Math::multiply(transform, square_bot_left.m_position));
        square_bot_left_ndc.m_color = square_bot_left.m_color;

        Vertex3_f square_bot_right_ndc;
        square_bot_right_ndc.m_position = Math::clipCoordsToNormalisedDeviceCoords(Math::multiply(transform, square_bot_right.m_position));
        square_bot_right_ndc.m_color = square_bot_right.m_color;

        renderer.clear(&(window.m_backbuffer), Pixel(0, 0, 0, 0));

        renderer.drawWireframeTriangle(&(window.m_backbuffer), square_top_left_ndc, square_top_right_ndc, square_bot_left_ndc);
        renderer.drawWireframeTriangle(&(window.m_backbuffer), square_bot_left_ndc, square_top_right_ndc, square_bot_right_ndc);

        window.present();
    }

    window.destroy();
    return EXIT_SUCCESS;
}
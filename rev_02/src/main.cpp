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
#include "00_types/level_00/font/ascii_font.hpp"
#include "00_types/level_00/pixel/pixel.hpp"
#include "00_types/level_00/mat4/mat4_f.hpp"
#include "00_types/level_00/vec2/vec2_f.hpp"
#include "00_types/level_00/vec2/vec2_i.hpp"
#include "00_types/level_00/vec3/vec3_f.hpp"
#include "00_types/level_00/vec4/vec4_f.hpp"

#include "00_types/level_01/vertex3_f/vertex3_f.hpp"
#include "00_types/level_01/vertex4/vertex4_f.hpp"

#include "00_types/level_02/mesh/mesh.hpp"

#include "01_utils/math/math.hpp"
#include "01_utils/timer/timer.hpp"

#include "02_window/window.hpp"
#include "02_window/backbuffer/backbuffer.hpp"
#include "02_window/backbuffer/hud.hpp"
#include "02_window/input/input.hpp"

#include "03_rendering/renderer.hpp"

#include "04_object/object.hpp"

#include "05_camera/camera.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Window window;
    if(!window.create(L"Pixel Engine", 800, 600, 1, hInstance))
    {
        return -1;
    }

    Mesh cube_mesh;
    cube_mesh = Mesh::createCubeMesh();

    Object cube_object(&cube_mesh);
    cube_object.m_position = Vec3_f(-1.0f, 1.0f, 3.0f);
    cube_object.m_rotation_axis = Vec3_f(-1.0f, 1.0f, 1.0f);
    cube_object.m_rotation_theta_radians = 0.0f;
    cube_object.m_scale = Vec3_f(1.0f, 1.0f, 1.0f);

    Object animated_cube_object(&cube_mesh);
    animated_cube_object.m_position = Vec3_f(3.0f, 0.0f, 0.0f);
    animated_cube_object.m_rotation_axis = Vec3_f(0.0f, 1.0f, 1.0f);
    animated_cube_object.m_rotation_theta_radians = 0.0f;
    animated_cube_object.m_scale = Vec3_f(1.0f, 1.0f, 1.0f);

    Camera camera
    (
        Vec3_f(0.0f, 0.0f, -10.0f),   // position
        0.0f,                        // pitch
        0.0f,                        // yaw
        0.0f,                        // roll
        0.7f,                        // field of view (radians)
        1.0f,                        // near plane
        100.0f,                      // far plane
        Vec3_f(0.0f, 1.0f, 0.0f)     // world up
    );

    AsciiFont ascii_font;
    Hud hud;

    Renderer renderer;

    Timer timer;
    timer.init();
    float totalTime = 0.0f;

    while(window.processMessages())
    {
        timer.tick();

        float move_speed = 5.0f * timer.deltaTime;
        if(window.m_input.isKeyDown('W')) { camera.moveForward(move_speed); }
        if(window.m_input.isKeyDown('S')) { camera.moveForward(-move_speed); }
        if(window.m_input.isKeyDown('A')) { camera.moveRight(-move_speed); }
        if(window.m_input.isKeyDown('D')) { camera.moveRight(move_speed); }
        if(window.m_input.isKeyDown('Q')) { camera.moveUp(move_speed); }
        if(window.m_input.isKeyDown('E')) { camera.moveUp(-move_speed); }

        totalTime += timer.deltaTime;

        float tz = -fabsf(20.0f * sinf(totalTime));
        animated_cube_object.m_position = Vec3_f(3.0f, 0.0f, tz);

        float sx = 0.6f + 0.4f * sinf(totalTime);
        float sy = 0.6f + 0.4f * cosf(totalTime);
        animated_cube_object.m_scale = Vec3_f(1.0f, 1.0f, 1.0f);
        
        animated_cube_object.m_rotation_axis = Vec3_f(0.0f, 1.0f, 1.0f);
        float rz = totalTime;
        animated_cube_object.m_rotation_theta_radians = rz;

        Mat4_f cam_view = camera.calcViewMatrix();
        Mat4_f perspective = camera.calcProjectionMatrix(window.m_backbuffer.m_width / window.m_backbuffer.m_height);

        renderer.clear(&(window.m_backbuffer), Pixel(0, 0, 0, 0));
    
        renderer.drawFilledObject(&(window.m_backbuffer), animated_cube_object, Math::multiply(perspective, cam_view));
        renderer.drawFilledObject(&(window.m_backbuffer), cube_object, Math::multiply(perspective, cam_view));

        window.present();
    }

    window.destroy();
    return EXIT_SUCCESS;
}
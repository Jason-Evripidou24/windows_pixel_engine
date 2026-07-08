// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <string>
#include <vector>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
#include <windows.h>
#include <windowsx.h>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "backbuffer/backbuffer.hpp"
#include "camera/camera.hpp"
#include "math/math.hpp"
#include "renderer/renderer.hpp"
#include "window/window.hpp"
#include "model/mesh.hpp"
#include "model/model.hpp"
#include "model/vertex.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    //---------------------------------------------------------------------------------------------------------------------//
    static std::vector<Mesh> cube_meshes(3);
    // Center cube.
    cube_meshes[0] = Mesh::createCubeMesh(0xFFFFFF00);
    // Positive color.
    cube_meshes[1] = Mesh::createCubeMesh(0xFF000000);
    // Negative color.
    cube_meshes[2] = Mesh::createCubeMesh(0xFFFFFFFF);

    static std::vector<Model> cube_models(7);
    // Center cube.
    cube_models[0] = Model();
    cube_models[0].m_mesh = &(cube_meshes[0]);
    cube_models[0].m_position = Math::Vec3_f(0.0f, 0.0f, 0.0f);
    cube_models[0].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[0].m_rotate_rad = 0.0f;
    cube_models[0].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Positive x axis.
    cube_models[1] = Model();
    cube_models[1].m_mesh = &(cube_meshes[1]);
    cube_models[1].m_position = Math::Vec3_f(5.0f, 0.0f, 0.0f);
    cube_models[1].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[1].m_rotate_rad = 0.0f;
    cube_models[1].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Negative x axis.
    cube_models[2] = Model();
    cube_models[2].m_mesh = &(cube_meshes[2]);
    cube_models[2].m_position = Math::Vec3_f(-5.0f, 0.0f, 0.0f);
    cube_models[2].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[2].m_rotate_rad = 0.0f;
    cube_models[2].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Positive y axis.
    cube_models[3] = Model();
    cube_models[3].m_mesh = &(cube_meshes[1]);
    cube_models[3].m_position = Math::Vec3_f(0.0f, 5.0f, 0.0f);
    cube_models[3].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[3].m_rotate_rad = 0.0f;
    cube_models[3].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Negative y axis.
    cube_models[4] = Model();
    cube_models[4].m_mesh = &(cube_meshes[2]);
    cube_models[4].m_position = Math::Vec3_f(0.0f, -5.0f, 0.0f);
    cube_models[4].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[4].m_rotate_rad = 0.0f;
    cube_models[4].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Positive z axis.
    cube_models[5] = Model();
    cube_models[5].m_mesh = &(cube_meshes[1]);
    cube_models[5].m_position = Math::Vec3_f(0.0f, 0.0f, 5.0f);
    cube_models[5].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[5].m_rotate_rad = 0.0f;
    cube_models[5].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    // Negative z axis.
    cube_models[6] = Model();
    cube_models[6].m_mesh = &(cube_meshes[2]);
    cube_models[6].m_position = Math::Vec3_f(0.0f, 0.0f, -5.0f);
    cube_models[6].m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    cube_models[6].m_rotate_rad = 0.0f;
    cube_models[6].m_rotate_axis = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    //---------------------------------------------------------------------------------------------------------------------//

    Window window;
    if(!window.create(L"Pixel Engine", 1600, 900, hInstance)) { return -1; }

    Backbuffer backbuffer;
    backbuffer.resize(window.m_width, window.m_height);

    Renderer renderer;

    while(window.processMessages())
    {
        backbuffer.clear(0xFF87CEFA);

        // Pretend we have a camera looking straight ahead at position (0, 0, 5).
        static float camera_x = 0.0f;
        static float camera_y = 0.0f;
        static float camera_z = 15.0f;
        static float camera_speed = 0.005f;
        // Move camera along x
        if(window.m_input.isKeyDown('A') == true) { camera_x -= camera_speed; }
        if(window.m_input.isKeyDown('D') == true) { camera_x += camera_speed; }
        // Move camera along y
        if(window.m_input.isKeyDown('Q') == true) { camera_y += camera_speed; }
        if(window.m_input.isKeyDown('E') == true) { camera_y -= camera_speed; }
        // Move camera along z
        if(window.m_input.isKeyDown('W') == true) { camera_z -= camera_speed; }
        if(window.m_input.isKeyDown('S') == true) { camera_z += camera_speed; }

        Math::Vec3_f cam_pos(camera_x, camera_y, camera_z);
        Math::Vec3_f world_up(0.0f, 1.0f, 0.0f);
        Camera camera
        (
            cam_pos,
            Math::degreesToRadians(0.0f),
            Math::degreesToRadians(180.0f),
            Math::degreesToRadians(45.0f),
            1.0f,
            100.0f,
            world_up
        );

        Math::Mat4_f cam_projection = camera.calcProjectionMatrix((float)backbuffer.m_width / (float)backbuffer.m_height);
        Math::Mat4_f cam_view = camera.calcViewMatrix();

        Math::Vec3_f camera_position(camera_x, camera_y, camera_z);
        Math::Mat4_f view = Math::translationMat4_f
        (
            -camera_position.m_data[0],
            -camera_position.m_data[1],
            -camera_position.m_data[2]
        );

        Math::Mat4_f projection = Math::perspectiveMat4_f(0.7f, (float)backbuffer.m_width / (float)backbuffer.m_height, 1.0f, 100.0f);

        
        Math::Mat4_f proj_view = projection * view;
        static float angle = 0.0f;
        angle += 0.002f;   // radians per frame
        for(int i = 0; i < 7; i++)
        {
            cube_models[i].m_rotate_rad = angle;
            Math::Mat4_f model = cube_models[i].calcModelMatrix();
            renderer.drawModel(backbuffer, cube_models[i], proj_view);
        }

        std::string info_string = camera.toString(6, 2);
        backbuffer.setText(10, 10, info_string.c_str(), info_string.size(), 0xFF000000);


        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
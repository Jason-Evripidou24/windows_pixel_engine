// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <random>
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
#include "../backbuffer/backbuffer.hpp"
#include "../camera/camera.hpp"
#include "../file_parsing/obj_file_parser.hpp"
#include "../file_parsing/mtl_file_parser.hpp"
#include "../math/math.hpp"
#include "../renderer/renderer.hpp"
#include "../window/window.hpp"
#include "../utils/utils.hpp"
#include "../model/mesh.hpp"
#include "../model/model.hpp"
#include "../timer/timer.hpp"

#include "main.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    //---------------------------------------------------------------------------------------------------------------------//
    Mesh backpack_mesh(0, "backpack_mesh");
    backpack_mesh.loadMesh("../assets/backpack/", "obj.obj", "mtl.mtl", "");

    Mesh cube_mesh(1, "cube_mesh");
    cube_mesh.loadMesh("../assets/cube/", "obj.obj", "mtl.mtl", "obj.obj");

    Mesh ground_mesh(2, "ground_mesh");
    ground_mesh.loadMesh("../assets/ground/", "obj.obj", "mtl.mtl", "obj.obj");

    Mesh house_001_mesh(3, "house_001_mesh");
    house_001_mesh.loadMesh("../assets/house_001/", "obj.obj", "mtl.mtl", "");

    Mesh house_002_mesh(4, "house_002_mesh");
    house_002_mesh.loadMesh("../assets/house_002/", "obj.obj", "Bambo_House.mtl", "");

    Mesh house_003_mesh(5, "house_003_mesh");
    house_003_mesh.loadMesh("../assets/house_003/", "obj.obj", "building_04.mtl", "");

    Mesh tree_mesh(6, "tree_mesh");
    tree_mesh.loadMesh("../assets/tree_001/", "obj.obj", "Lowpoly_tree_sample.mtl", "obj.obj");

    Mesh truck_001_mesh(7, "truck_001_mesh");
    truck_001_mesh.loadMesh("../assets/truck_001/", "rig.obj", "rig.mtl", "rig.obj");
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> pos_dist(-19.8f, 19.8f);
    std::uniform_real_distribution<float> scale_dist(0.2f, 0.3f);
    std::uniform_real_distribution<float> rotation_dist(0.0f, 2.0f * 3.1415f);
    std::vector<Model> tree_models(10);
    for (size_t i = 0; i < tree_models.size(); i++)
    {
        tree_models[i] = Model(-1, "tree_model " + std::to_string(i), &tree_mesh);

        float scale = scale_dist(rng);

        tree_models[i].m_position = Math::Vec3_f(pos_dist(rng), 0.0f, pos_dist(rng));
        tree_models[i].m_scale = Math::Vec3_f(scale, scale, scale);

        tree_models[i].m_rotate_rad = rotation_dist(rng);
        tree_models[i].m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);
    }

    Model backpack_model(-1, "backpack_model", &backpack_mesh);
    backpack_model.m_position = Math::Vec3_f(0.0f, 5.0f, 0.0f);
    backpack_model.m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    backpack_model.m_rotate_rad = 0.0f;
    backpack_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Model ground_model(-1, "ground_model", &ground_mesh);
    ground_model.m_position = Math::Vec3_f(0.0f, 0.0f, 0.0f);
    ground_model.m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    ground_model.m_rotate_rad = 0.0f;
    ground_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Model house_001_model(-1, "house_001_model", &house_001_mesh);
    house_001_model.m_position = Math::Vec3_f(-30.0f, 0.0f, 30.0f);
    house_001_model.m_scale = Math::Vec3_f(2.0f, 2.0f, 2.0f);
    house_001_model.m_rotate_rad = Math::convertDegreesToRadians(310.0f);
    house_001_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Model house_002_model(-1, "house_002_model", &house_002_mesh);
    house_002_model.m_position = Math::Vec3_f(-30.0f, 0.0f, -30.0f);
    house_002_model.m_scale = Math::Vec3_f(2.0f, 2.0f, 2.0f);
    house_002_model.m_rotate_rad = Math::convertDegreesToRadians(220.0f);
    house_002_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Model house_003_model(-1, "house_003_model", &house_003_mesh);
    house_003_model.m_position = Math::Vec3_f(20.0f, 1.5f, 20.0f);
    house_003_model.m_scale = Math::Vec3_f(3.0f, 3.0f, 3.0f);
    house_003_model.m_rotate_rad = Math::convertDegreesToRadians(220.0f);
    house_003_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);

    Model truck_001_model(-1, "truck_001_model", &truck_001_mesh);
    truck_001_model.m_position = Math::Vec3_f(30.0f, 0.0f, -30.0f);
    truck_001_model.m_scale = Math::Vec3_f(1.0f, 1.0f, 1.0f);
    truck_001_model.m_rotate_rad = 0.0f;
    truck_001_model.m_rotate_axis = Math::Vec3_f(0.0f, 1.0f, 0.0f);
    //---------------------------------------------------------------------------------------------------------------------//

    Timer timer;
    timer.init();

    Window window;
    if(!window.create(L"Pixel Engine", g_preset_to_use.m_window_width, g_preset_to_use.m_window_height, hInstance)) { return -1; }

    Backbuffer backbuffer;
    int backbuffer_width = window.m_width / g_preset_to_use.m_pixel_size;
    int backbuffer_height = window.m_height / g_preset_to_use.m_pixel_size;
    backbuffer.resize(backbuffer_width, backbuffer_height);

    Renderer renderer(&backbuffer, g_preset_to_use.m_tile_split); // Must divide backbuffer width and height perfectly.

    Math::Mat4_f projection_matrix = g_camera.calcProjectionMatrix((float)backbuffer.m_width / (float)backbuffer.m_height);
    /*
    // Ortho currently broken
    Math::Mat4_f projection_matrix;
    projection_matrix.orthographic
    (
     -10.0f,  // left
      10.0f,  // right
     -10.0f,  // bottom
      10.0f,  // top
      0.1f,   // near
      1000.0f // far
    );
    */
    Math::Mat4_f view_matrix;
    Math::Mat4_f proj_view_matrix;

    while(window.processMessages())
    {
        timer.tick();

        //backbuffer.clear(0xFF87CEEB); // Sky blue
        //backbuffer.clear(0xFFFF0000); // Red
        backbuffer.clear(0xFF000000); // Black
        //backbuffer.clear(0xFFFFFFFF); // White

        processInput(window, timer.deltaTime);

        Math::Vec3_f line_start_pos = g_camera.m_position;
        Math::Vec3_f line_end_pos = g_camera.m_position + (g_camera.m_front * 10.0f);
        Geometry::MultiWireframe hitbox_transformed;

        Geometry::transformMultiWireframe(hitbox_transformed, truck_001_model.m_mesh->m_hitbox, truck_001_model.calcModelMatrix());
        if(Geometry::checkLineSegmentIntersectsMultiWireframe(line_start_pos, line_end_pos, hitbox_transformed) == true)
        {
            std::string intersection_success = truck_001_model.toString();
            backbuffer.setText(10, 30, intersection_success.c_str(), static_cast<int>(intersection_success.size()), 0xFFFFFFFF);
        }
        Geometry::transformMultiWireframe(hitbox_transformed, ground_model.m_mesh->m_hitbox, ground_model.calcModelMatrix());
        if(Geometry::checkLineSegmentIntersectsMultiWireframe(line_start_pos, line_end_pos, hitbox_transformed) == true)
        {
            std::string intersection_success = ground_model.toString();
            backbuffer.setText(10, 30, intersection_success.c_str(), static_cast<int>(intersection_success.size()), 0xFFFFFFFF);
        }
        for(size_t i = 0; i < tree_models.size(); i++)
        {
            Geometry::transformMultiWireframe(hitbox_transformed, tree_models[i].m_mesh->m_hitbox, tree_models[i].calcModelMatrix());
            if(Geometry::checkLineSegmentIntersectsMultiWireframe(line_start_pos, line_end_pos, hitbox_transformed) == true)
            {
                std::string intersection_success = tree_models[i].toString();
                backbuffer.setText(10, 30, intersection_success.c_str(), static_cast<int>(intersection_success.size()), 0xFFFFFFFF);
            }
        }
    
        view_matrix = g_camera.calcViewMatrix();
        proj_view_matrix = projection_matrix * view_matrix;

        int mis_screen_x = backbuffer.toBackbufferCoordX(0);
        int mis_screen_y = backbuffer.toBackbufferCoordY(0);
        for(int i = -5; i <= 5; i++)
        {
            for(int j = -5; j <= 5; j++)
            {
                backbuffer.setPixel(mis_screen_x + i, mis_screen_y + j, 1.0f, 0xFF000000);
            }
        }
        
        for(size_t i = 0; i < tree_models.size(); i++)
        {
            tree_models[i].renderModel(renderer, proj_view_matrix, g_draw_filled, g_vertex_material_color_mix);
        }
        ground_model.renderModel(renderer, proj_view_matrix, g_draw_filled, g_vertex_material_color_mix);

        std::thread t_00([&]() { backpack_model.renderModel(renderer, proj_view_matrix, g_draw_filled, g_vertex_material_color_mix); });
        std::thread t_01([&]() { truck_001_model.renderModel(renderer, proj_view_matrix, g_draw_filled, g_vertex_material_color_mix); });
        std::thread t_02([&]() { house_001_model.renderModel(renderer, proj_view_matrix, g_draw_filled, g_vertex_material_color_mix); });
        std::thread t_03([&]() { house_002_model.renderModel(renderer, proj_view_matrix, g_draw_filled, g_vertex_material_color_mix); });
        std::thread t_04([&]() { house_003_model.renderModel(renderer, proj_view_matrix, g_draw_filled, g_vertex_material_color_mix); });
        
        t_00.join();
        t_01.join();
        t_02.join();
        t_03.join();
        t_04.join();

        std::string info_string = std::string("FPS: ") + std::to_string(timer.fps);
        backbuffer.setText(10, 10, info_string.c_str(), static_cast<int>(info_string.size()), 0xFFFFFFFF);

        backbuffer.setText
        (
            g_preset_to_use.m_control_string_x,
            g_preset_to_use.m_control_string_y,
            g_controls_string.c_str(),
            static_cast<int>(g_controls_string.size()),
            0xFFFFFFFF
        );
        
        backbuffer.present(window.m_dc, window.m_width, window.m_height);
    }

    window.destroy();
    return EXIT_SUCCESS;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
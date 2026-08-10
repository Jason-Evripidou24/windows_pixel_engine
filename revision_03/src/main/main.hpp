// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef MAIN_HPP
#define MAIN_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


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
#include "../math/core/math_core.hpp"
#include "../math/geometry/math_geometry.hpp"
#include "../renderer/renderer.hpp"
#include "../window/window.hpp"
#include "../utils/utils.hpp"
#include "../utils/timer/timer.hpp"
#include "../mesh/mesh.hpp"
#include "../model/model.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
struct presets
{
    int m_window_width;
    int m_window_height;
    int m_pixel_size;
    int m_tile_split;
    int m_control_string_x;
    int m_control_string_y;

    presets
    (
        int window_width,
        int window_height,
        int pixel_size,
        int tile_split,
        int control_string_x,
        int control_string_y
    )
    :
    m_window_width(window_width),
    m_window_height(window_height),
    m_pixel_size(pixel_size),
    m_tile_split(tile_split),
    m_control_string_x(control_string_x),
    m_control_string_y(control_string_y)
    {}
};
extern presets  g_preset00;
extern presets  g_preset01;
extern presets& g_preset_to_use;
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Global variables.
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Camera and camera related variables.
extern Camera g_camera;
extern float g_camera_move_speed;
extern float g_camera_look_speed;

// Input keys that toggle things on and off.
extern bool g_prev_1_key;
extern bool g_prev_2_key;
extern bool g_prev_3_key;
extern bool g_prev_4_key;
extern bool g_prev_5_key;
extern bool g_prev_6_key;
extern bool g_prev_7_key;
extern bool g_prev_8_key;
extern bool g_prev_9_key;
extern bool g_prev_0_key;

// Options we can toggle on and off.
extern bool g_draw_filled;

// Options that we can adjust on a scale from 0 to 100%
extern float g_vertex_material_color_mix;

// Mouse/Cursor position.
extern float g_mouse_pos_x;
extern float g_mouse_pos_y;

// Display controls information.
extern std::string g_controls_string;
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void processInput(Window& window, float delta_time);
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
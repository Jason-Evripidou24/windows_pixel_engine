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
#include "../../backbuffer/backbuffer.hpp"
#include "../../camera/camera.hpp"
#include "../../file_parsing/obj_file_parser.hpp"
#include "../../file_parsing/mtl_file_parser.hpp"
#include "../../math/math.hpp"
#include "../../renderer/renderer.hpp"
#include "../../window/window.hpp"
#include "../../utils/utils.hpp"
#include "../../model/mesh.hpp"
#include "../../model/model.hpp"
#include "../../timer/timer.hpp"

#include "../main.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
presets  g_preset00(1400, 900, 1, 10, 10, 800);
presets  g_preset01(1360, 900, 2, 10, 10, 360);
presets& g_preset_to_use = g_preset00;

// Camera and camera related variables.
Camera g_camera
(
    Math::Vec3_f(0.0f, 1.7f, 5.0f),
    Math::convertDegreesToRadians(0.0f),
    Math::convertDegreesToRadians(180.0f),
    Math::convertDegreesToRadians(45.0f),
    0.1f,
    100.0f,
    Math::Vec3_f(0.0f, 1.0f, 0.0f)
);
float g_camera_move_speed = 5.0f;
float g_camera_look_speed = 0.002f;

// Input keys that toggle things on and off.
bool g_prev_1_key = false;
bool g_prev_2_key = false;
bool g_prev_3_key = false;
bool g_prev_4_key = false;
bool g_prev_5_key = false;
bool g_prev_6_key = false;
bool g_prev_7_key = false;
bool g_prev_8_key = false;
bool g_prev_9_key = false;
bool g_prev_0_key = false;

// Options we can toggle on and off.
bool g_draw_filled = true;

// Options that we can adjust on a scale from 0 to 100%
float g_vertex_material_color_mix = 1.0f;

// Mouse/Cursor position.
float g_mouse_pos_x = 0.0f;
float g_mouse_pos_y = 0.0f;

// Display controls information.
std::string g_controls_string =
    std::string("CONTROLS") + std::string("\n") +
    std::string("W/A                : ") + std::string("MOVE FORWARD/BACKWARD")                        + std::string("\n") +
    std::string("S/D                : ") + std::string("MOVE LEFT/RIGHT")                              + std::string("\n") +
    std::string("Q/E                : ") + std::string("MOVE UP/DOWN")                                 + std::string("\n") +
    std::string("LEFT MOUSE AND DRAG: ") + std::string("LOOK AROUND")                                  + std::string("\n") +
    std::string("0                  : ") + std::string("TOGGLE FILLED/WIREFRAME MODE")                 + std::string("\n") +
    std::string("1/2                : ") + std::string("INCREASE/DECREASE MOVE SPEED")                 + std::string("\n") +
    std::string("8/9                : ") + std::string("CHANGE VERTEX AND MATERIAL COLOR MIX");
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
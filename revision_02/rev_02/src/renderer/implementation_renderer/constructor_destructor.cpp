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
#include "../renderer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Renderer::Renderer(Backbuffer* backbuffer)
:
    m_tile_renderer_00(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer, -1.0f, -0.5f,  0.5f,  1.0f, -1.0f, 1.0f),
    m_tile_renderer_01(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer, -0.5f,  0.0f,  0.5f,  1.0f, -1.0f, 1.0f),
    m_tile_renderer_02(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer,  0.0f,  0.5f,  0.5f,  1.0f, -1.0f, 1.0f),
    m_tile_renderer_03(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer,  0.5f,  1.0f,  0.5f,  1.0f, -1.0f, 1.0f),
    m_tile_renderer_04(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer, -1.0f, -0.5f,  0.0f,  0.5f, -1.0f, 1.0f),
    m_tile_renderer_05(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer, -0.5f,  0.0f,  0.0f,  0.5f, -1.0f, 1.0f),
    m_tile_renderer_06(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer,  0.0f,  0.5f,  0.0f,  0.5f, -1.0f, 1.0f),
    m_tile_renderer_07(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer,  0.5f,  1.0f,  0.0f,  0.5f, -1.0f, 1.0f),
    m_tile_renderer_08(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer, -1.0f, -0.5f, -0.5f,  0.0f, -1.0f, 1.0f),
    m_tile_renderer_09(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer, -0.5f,  0.0f, -0.5f,  0.0f, -1.0f, 1.0f),
    m_tile_renderer_10(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer,  0.0f,  0.5f, -0.5f,  0.0f, -1.0f, 1.0f),
    m_tile_renderer_11(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer,  0.5f,  1.0f, -0.5f,  0.0f, -1.0f, 1.0f),
    m_tile_renderer_12(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer, -1.0f, -0.5f, -1.0f, -0.5f, -1.0f, 1.0f),
    m_tile_renderer_13(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer, -0.5f,  0.0f, -1.0f, -0.5f, -1.0f, 1.0f),
    m_tile_renderer_14(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer,  0.0f,  0.5f, -1.0f, -0.5f, -1.0f, 1.0f),
    m_tile_renderer_15(&m_renderer_mutex, &m_renderer_condition_variable, backbuffer,  0.5f,  1.0f, -1.0f, -0.5f, -1.0f, 1.0f)
{
    m_tile_renderer_00.start();
    m_tile_renderer_01.start();
    m_tile_renderer_02.start();
    m_tile_renderer_03.start();
    m_tile_renderer_04.start();
    m_tile_renderer_05.start();
    m_tile_renderer_06.start();
    m_tile_renderer_07.start();
    m_tile_renderer_08.start();
    m_tile_renderer_09.start();
    m_tile_renderer_10.start();
    m_tile_renderer_11.start();
    m_tile_renderer_12.start();
    m_tile_renderer_13.start();
    m_tile_renderer_14.start();
    m_tile_renderer_15.start();
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Renderer::~Renderer()
{
    m_tile_renderer_00.stop();
    m_tile_renderer_01.stop();
    m_tile_renderer_02.stop();
    m_tile_renderer_03.stop();
    m_tile_renderer_04.stop();
    m_tile_renderer_05.stop();
    m_tile_renderer_06.stop();
    m_tile_renderer_07.stop();
    m_tile_renderer_08.stop();
    m_tile_renderer_09.stop();
    m_tile_renderer_10.stop();
    m_tile_renderer_11.stop();
    m_tile_renderer_12.stop();
    m_tile_renderer_13.stop();
    m_tile_renderer_14.stop();
    m_tile_renderer_15.stop();
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
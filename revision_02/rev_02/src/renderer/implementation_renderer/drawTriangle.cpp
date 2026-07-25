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
/*
-   Triangle has been transformed to clip space and undergone perspective divide but no clipping against x,y,z planes.
*/
void Renderer::drawTriangle(const Math::Triangle& triangle, Material* material, bool draw_filled, float color_mix)
{
    Math::Triangle new_triangle(triangle);

    if(draw_filled == true)
    {
        for(size_t i = 0; i < m_tile_renderers.size(); i++)
        {
            m_tile_renderers[i].second = false;
        }
        for(size_t i = 0; i < m_tile_renderers.size(); i++)
        {
            m_tile_renderers[i].first->parentRequestDrawTriangle
            (
                &new_triangle,
                material,
                draw_filled,
                color_mix,
                &(m_tile_renderers[i].second)
            );
        }

        std::unique_lock renderer_lock(m_renderer_mutex);

        m_renderer_condition_variable.wait
        (
            renderer_lock,
            [&]
            {
                bool all_tile_renderers_finished_triangle = true;
                for(size_t i = 0; i < m_tile_renderers.size(); i++)
                {
                    if(m_tile_renderers[i].second == false)
                    {
                        all_tile_renderers_finished_triangle = false;
                        break;
                    }
                }
                return all_tile_renderers_finished_triangle;
            }
        );
    }
    else
    {
        this->drawLine(triangle.m_v0, triangle.m_v1, material, color_mix);
        this->drawLine(triangle.m_v0, triangle.m_v2, material, color_mix);
        this->drawLine(triangle.m_v1, triangle.m_v2, material, color_mix);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
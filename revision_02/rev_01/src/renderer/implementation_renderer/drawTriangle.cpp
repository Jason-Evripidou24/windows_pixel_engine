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
void Renderer::drawTriangle(const Math::Triangle& triangle, const Material& material, bool draw_filled, float color_mix)
{
    /*
    const std::vector<Math::Triangle> triangles_clipped = Math::clipTriangleBetweenXYZ
    (
        material_triangle.m_triangle,
        -1.0f,
         1.0f,
        -1.0f,
         1.0f,
        -1.0f,
         1.0f
    );

    for(const Math::Triangle& triangle_clipped : triangles_clipped)
    {
        if(draw_filled == true)
        {
            this->fillTriangle(triangle_clipped, material_triangle.m_material, color_mix);
        }
        else
        {
            this->drawLine(triangle_clipped.m_v0, triangle_clipped.m_v1, material_triangle.m_material, color_mix);
            this->drawLine(triangle_clipped.m_v0, triangle_clipped.m_v2, material_triangle.m_material, color_mix);
            this->drawLine(triangle_clipped.m_v1, triangle_clipped.m_v2, material_triangle.m_material, color_mix);
        }
    }
    */

    if(draw_filled == true)
    {
        this->fillTriangle(triangle, material, color_mix);
    }
    else
    {
        this->drawLine(triangle.m_v0, triangle.m_v1, material, color_mix);
        this->drawLine(triangle.m_v0, triangle.m_v2, material, color_mix);
        this->drawLine(triangle.m_v1, triangle.m_v2, material, color_mix);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
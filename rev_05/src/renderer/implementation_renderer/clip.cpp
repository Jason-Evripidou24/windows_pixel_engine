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

#include "../../math/vec3_f.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Assumes that the line between v_0 and v_1 intersects plane_z.
*/
Math::Vertex Renderer::clipIntersectionZ(const Math::Vertex& v_0, const Math::Vertex& v_1, const float plane_z)
{
    //---------------------------------------------------------------------------------------------------------------------//
    Math::Vec4_f pos_0 = v_0.m_position;
    float color_0_A = (float)((v_0.m_color >> 0)  & 0xFF);
    float color_0_R = (float)((v_0.m_color >> 8)  & 0xFF);
    float color_0_G = (float)((v_0.m_color >> 16) & 0xFF);
    float color_0_B = (float)((v_0.m_color >> 24) & 0xFF);

    Math::Vec4_f pos_1 = v_1.m_position;
    float color_1_A = (float)((v_1.m_color >> 0)  & 0xFF);
    float color_1_R = (float)((v_1.m_color >> 8)  & 0xFF);
    float color_1_G = (float)((v_1.m_color >> 16) & 0xFF);
    float color_1_B = (float)((v_1.m_color >> 24) & 0xFF);
    //---------------------------------------------------------------------------------------------------------------------//

    float t = (plane_z - pos_0.m_data[2]) / (pos_1.m_data[2] - pos_0.m_data[2]);

    Math::Vec4_f intersection_pos =  pos_0 + ((pos_1 - pos_0) * t);

    uint8_t intersection_color_a = (uint8_t)((color_0_A * (1.0f - t)) + (color_1_A * t));
    uint8_t intersection_color_r = (uint8_t)((color_0_R * (1.0f - t)) + (color_1_R * t));
    uint8_t intersection_color_g = (uint8_t)((color_0_G * (1.0f - t)) + (color_1_G * t));
    uint8_t intersection_color_b = (uint8_t)((color_0_B * (1.0f - t)) + (color_1_B * t));

    uint32_t intersection_color_argb =
            (uint32_t(intersection_color_a) << 0)  |
            (uint32_t(intersection_color_r) << 8)  |
            (uint32_t(intersection_color_g) << 16) |
            (uint32_t(intersection_color_b) << 24);
    
    Math::Vertex result;
    result.m_position = intersection_pos;
    result.m_color = intersection_color_argb;

    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Possible cases:
    1.  Entire triangle is below max_z_plane.
    2.  Entire triangle is above max_z_plane.
    3.  Triangle is split by max_z_plane.
*/
std::vector<Math::Triangle> Renderer::clipTriangleMaxZ(const Math::Triangle& triangle, const float max_z_plane)
{
    Math::Vec4_f pos_0 = triangle.m_vertices[0].m_position;
    Math::Vec4_f pos_1 = triangle.m_vertices[1].m_position;
    Math::Vec4_f pos_2 = triangle.m_vertices[2].m_position;

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 1: Entire triangle is below max_z_plane.
    //---------------------------------------------------------------------------------------------------------------------//
    if( (pos_0.m_data[2] <= max_z_plane) && (pos_1.m_data[2] <= max_z_plane) && (pos_2.m_data[2] <= max_z_plane) )
    {
        return std::vector<Math::Triangle>(1, triangle);
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 2: Entire triangle is above max_z_plane.
    //---------------------------------------------------------------------------------------------------------------------//
    if( (pos_0.m_data[2] > max_z_plane) && (pos_1.m_data[2] > max_z_plane) && (pos_2.m_data[2] > max_z_plane) )
    {
        return std::vector<Math::Triangle>();
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 3: Triangle is split by max_z_plane. 1 vertex below and 2 above. Create a triangle.
    //---------------------------------------------------------------------------------------------------------------------//
    if( (pos_0.m_data[2] <= max_z_plane) && (pos_1.m_data[2] > max_z_plane) && (pos_2.m_data[2] > max_z_plane) )
    {
        Math::Vertex new_vertex_0 = this->clipIntersectionZ(triangle.m_vertices[0], triangle.m_vertices[1], max_z_plane);
        Math::Vertex new_vertex_1 = this->clipIntersectionZ(triangle.m_vertices[0], triangle.m_vertices[2], max_z_plane);

        Math::Triangle new_triangle;
        new_triangle.m_vertices[0] = new_vertex_0;
        new_triangle.m_vertices[1] = new_vertex_1;
        new_triangle.m_vertices[2] = triangle.m_vertices[0];

        std::vector<Math::Triangle> result(1);
        result[0] = new_triangle;
        
        return result;
    }
    else if( (pos_0.m_data[2] > max_z_plane) && (pos_1.m_data[2] <= max_z_plane) && (pos_2.m_data[2] > max_z_plane) )
    {
        Math::Vertex new_vertex_0 = this->clipIntersectionZ(triangle.m_vertices[1], triangle.m_vertices[0], max_z_plane);
        Math::Vertex new_vertex_1 = this->clipIntersectionZ(triangle.m_vertices[1], triangle.m_vertices[2], max_z_plane);

        Math::Triangle new_triangle;
        new_triangle.m_vertices[0] = new_vertex_0;
        new_triangle.m_vertices[1] = new_vertex_1;
        new_triangle.m_vertices[2] = triangle.m_vertices[1];

        std::vector<Math::Triangle> result(1);
        result[0] = new_triangle;
        
        return result;
    }
    else if( (pos_0.m_data[2] > max_z_plane) && (pos_1.m_data[2] > max_z_plane) && (pos_2.m_data[2] <= max_z_plane) )
    {
        Math::Vertex new_vertex_0 = this->clipIntersectionZ(triangle.m_vertices[2], triangle.m_vertices[0], max_z_plane);
        Math::Vertex new_vertex_1 = this->clipIntersectionZ(triangle.m_vertices[2], triangle.m_vertices[1], max_z_plane);

        Math::Triangle new_triangle;
        new_triangle.m_vertices[0] = new_vertex_0;
        new_triangle.m_vertices[1] = new_vertex_1;
        new_triangle.m_vertices[2] = triangle.m_vertices[2];

        std::vector<Math::Triangle> result(1);
        result[0] = new_triangle;
        
        return result;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 4: Triangle is split by max_z_plane. 2 vertex below and 1 above. Create a quad.
    //---------------------------------------------------------------------------------------------------------------------//
    if( (pos_0.m_data[2] > max_z_plane) && (pos_1.m_data[2] <= max_z_plane) && (pos_2.m_data[2] <= max_z_plane) )
    {
        Math::Vertex new_vertex_0 = this->clipIntersectionZ(triangle.m_vertices[0], triangle.m_vertices[1], max_z_plane);
        Math::Vertex new_vertex_1 = this->clipIntersectionZ(triangle.m_vertices[0], triangle.m_vertices[2], max_z_plane);

        Math::Triangle new_triangle_0;
        new_triangle_0.m_vertices[0] = triangle.m_vertices[1];
        new_triangle_0.m_vertices[1] = triangle.m_vertices[2];
        new_triangle_0.m_vertices[2] = new_vertex_0;

        Math::Triangle new_triangle_1;
        new_triangle_0.m_vertices[0] = new_vertex_0;
        new_triangle_0.m_vertices[1] = new_vertex_1;
        new_triangle_0.m_vertices[2] = triangle.m_vertices[2];
        
        std::vector<Math::Triangle> result(2);
        result[0] = new_triangle_0;
        result[1] = new_triangle_1;
        
        return result;
    }
    else if( (pos_0.m_data[2] <= max_z_plane) && (pos_1.m_data[2] > max_z_plane) && (pos_2.m_data[2] <= max_z_plane) )
    {
        Math::Vertex new_vertex_0 = this->clipIntersectionZ(triangle.m_vertices[1], triangle.m_vertices[0], max_z_plane);
        Math::Vertex new_vertex_1 = this->clipIntersectionZ(triangle.m_vertices[1], triangle.m_vertices[2], max_z_plane);

        Math::Triangle new_triangle_0;
        new_triangle_0.m_vertices[0] = triangle.m_vertices[0];
        new_triangle_0.m_vertices[1] = triangle.m_vertices[2];
        new_triangle_0.m_vertices[2] = new_vertex_0;

        Math::Triangle new_triangle_1;
        new_triangle_0.m_vertices[0] = new_vertex_0;
        new_triangle_0.m_vertices[1] = new_vertex_1;
        new_triangle_0.m_vertices[2] = triangle.m_vertices[2];
        
        std::vector<Math::Triangle> result(2);
        result[0] = new_triangle_0;
        result[1] = new_triangle_1;
        
        return result;
    }
    else if( (pos_0.m_data[2] <= max_z_plane) && (pos_1.m_data[2] <= max_z_plane) && (pos_2.m_data[2] > max_z_plane) )
    {
        Math::Vertex new_vertex_0 = this->clipIntersectionZ(triangle.m_vertices[2], triangle.m_vertices[0], max_z_plane);
        Math::Vertex new_vertex_1 = this->clipIntersectionZ(triangle.m_vertices[2], triangle.m_vertices[1], max_z_plane);

        Math::Triangle new_triangle_0;
        new_triangle_0.m_vertices[0] = triangle.m_vertices[0];
        new_triangle_0.m_vertices[1] = triangle.m_vertices[1];
        new_triangle_0.m_vertices[2] = new_vertex_0;

        Math::Triangle new_triangle_1;
        new_triangle_0.m_vertices[0] = new_vertex_0;
        new_triangle_0.m_vertices[1] = new_vertex_1;
        new_triangle_0.m_vertices[2] = triangle.m_vertices[1];
        
        std::vector<Math::Triangle> result(2);
        result[0] = new_triangle_0;
        result[1] = new_triangle_1;
        
        return result;
    }
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cstdint>
#include <vector>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../renderer.hpp"

#include "../../backbuffer/backbuffer.hpp"
#include "../../math/vertex.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Triangle is (should be) within clip space.
*/
std::vector<Math::Triangle> Renderer::clipTriangleMinZ(const Math::Triangle& triangle, const float min_z_plane)
{
    //---------------------------------------------------------------------------------------------------------------------//
    const Math::Vertex& vert_0 = triangle.m_vertices[0];
    const Math::Vertex& vert_1 = triangle.m_vertices[1];
    const Math::Vertex& vert_2 = triangle.m_vertices[2];

    bool vert_0_in_bounds = false; if(vert_0.m_position.m_data[2] >= min_z_plane) { vert_0_in_bounds = true; }
    bool vert_1_in_bounds = false; if(vert_1.m_position.m_data[2] >= min_z_plane) { vert_1_in_bounds = true; }
    bool vert_2_in_bounds = false; if(vert_2.m_position.m_data[2] >= min_z_plane) { vert_2_in_bounds = true; }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 1: Entire triangle is above max_z_plane.
    //---------------------------------------------------------------------------------------------------------------------//
    if( (vert_0_in_bounds == true) && (vert_1_in_bounds == true) && (vert_2_in_bounds == true) )
    {
        return std::vector<Math::Triangle>(1, triangle);
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 2: Entire triangle is below max_z_plane.
    //---------------------------------------------------------------------------------------------------------------------//
    if( (vert_0_in_bounds == false) && (vert_1_in_bounds == false) && (vert_2_in_bounds == false) )
    {
        return std::vector<Math::Triangle>();
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 3: Triangle is split by max_z_plane. 1 vertex above and 2 below. Create a triangle.
    //---------------------------------------------------------------------------------------------------------------------//
    /*
    -   Vertex 0 is in bounds, Vertex 1 and Vertex 2 are out of bounds. Create new triangle with vertices:
        -   Vertex 0
        -   Intersection of Vertex 0 and Vertex 1 with min_z_plane.
        -   Intersection of Vertex 0 and Vertex 2 with min_z_plane.

    -   Apply the same logic to all sub cases of Case 3.
    */
    if( (vert_0_in_bounds == true) && (vert_1_in_bounds == false) && (vert_2_in_bounds == false) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_0, vert_1, min_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_0, vert_2, min_z_plane);

        std::vector<Math::Triangle> output(1);
        output[0] = Math::Triangle(vert_0, intersection_vert_0, intersection_vert_1);

        return output;
    }
    else if( (vert_0_in_bounds == false) && (vert_1_in_bounds == true) && (vert_2_in_bounds == false) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_1, vert_0, min_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_1, vert_2, min_z_plane);

        std::vector<Math::Triangle> output(1);
        output[0] = Math::Triangle(vert_1, intersection_vert_0, intersection_vert_1);

        return output;
    }
    else if( (vert_0_in_bounds == false) && (vert_1_in_bounds == false) && (vert_2_in_bounds == true) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_2, vert_0, min_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_2, vert_1, min_z_plane);

        std::vector<Math::Triangle> output(1);
        output[0] = Math::Triangle(vert_2, intersection_vert_0, intersection_vert_1);

        return output;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 4: Triangle is split by max_z_plane. 2 vertex below and 1 above. Create a quad.
    //---------------------------------------------------------------------------------------------------------------------//
    /*
    -   Vertex 0 and Vertex 1 are in bounds, Vertex 2 is out of bounds. Create two new triangles:
        -   Triangle 0 with vertices:
            -   Vertex 0
            -   Vertex 1
            -   Intersection of Vertex 0 and Vertex 2 with min_z_plane.
        -   Triangle 1 with vertices:
            -   Vertex 1
            -   Intersection of Vertex 0 and Vertex 2 with min_z_plane.
            -   Intersection of Vertex 1 and Vertex 2 with min_z_plane.

    -   Apply the same logic to all sub cases of Case 4.
    */
    if( (vert_0_in_bounds == true) && (vert_1_in_bounds == true) && (vert_2_in_bounds == false) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_0, vert_2, min_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_1, vert_2, min_z_plane);

        std::vector<Math::Triangle> output(2);
        output[0] = Math::Triangle(vert_0, vert_1, intersection_vert_0);
        output[1] = Math::Triangle(vert_1, intersection_vert_0, intersection_vert_1);

        return output;
    }
    else if( (vert_0_in_bounds == true) && (vert_1_in_bounds == false) && (vert_2_in_bounds == true) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_0, vert_1, min_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_2, vert_1, min_z_plane);

        std::vector<Math::Triangle> output(2);
        output[0] = Math::Triangle(vert_0, vert_2, intersection_vert_0);
        output[1] = Math::Triangle(vert_2, intersection_vert_0, intersection_vert_1);

        return output;
    }
    else if( (vert_0_in_bounds == false) && (vert_1_in_bounds == true) && (vert_2_in_bounds == true) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_1, vert_0, min_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_2, vert_0, min_z_plane);

        std::vector<Math::Triangle> output(2);
        output[0] = Math::Triangle(vert_1, vert_2, intersection_vert_0);
        output[1] = Math::Triangle(vert_2, intersection_vert_0, intersection_vert_1);
        
        return output;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    // Should not get here.
    return std::vector<Math::Triangle>();
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Triangle is (should be) within clip space.
*/
std::vector<Math::Triangle> Renderer::clipTriangleMaxZ(const Math::Triangle& triangle, const float max_z_plane)
{
    //---------------------------------------------------------------------------------------------------------------------//
    const Math::Vertex& vert_0 = triangle.m_vertices[0];
    const Math::Vertex& vert_1 = triangle.m_vertices[1];
    const Math::Vertex& vert_2 = triangle.m_vertices[2];

    bool vert_0_in_bounds = false; if(vert_0.m_position.m_data[2] <= max_z_plane) { vert_0_in_bounds = true; }
    bool vert_1_in_bounds = false; if(vert_1.m_position.m_data[2] <= max_z_plane) { vert_1_in_bounds = true; }
    bool vert_2_in_bounds = false; if(vert_2.m_position.m_data[2] <= max_z_plane) { vert_2_in_bounds = true; }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 1: Entire triangle is below max_z_plane.
    //---------------------------------------------------------------------------------------------------------------------//
    if( (vert_0_in_bounds == true) && (vert_1_in_bounds == true) && (vert_2_in_bounds == true) )
    {
        return std::vector<Math::Triangle>(1, triangle);
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 2: Entire triangle is above max_z_plane.
    //---------------------------------------------------------------------------------------------------------------------//
    if( (vert_0_in_bounds == false) && (vert_1_in_bounds == false) && (vert_2_in_bounds == false) )
    {
        return std::vector<Math::Triangle>();
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 3: Triangle is split by max_z_plane. 1 vertex below and 2 above. Create a triangle.
    //---------------------------------------------------------------------------------------------------------------------//
    /*
    -   Vertex 0 is in bounds, Vertex 1 and Vertex 2 are out of bounds. Create new triangle with vertices:
        -   Vertex 0
        -   Intersection of Vertex 0 and Vertex 1 with max_z_plane.
        -   Intersection of Vertex 0 and Vertex 2 with max_z_plane.

    -   Apply the same logic to all sub cases of Case 3.
    */
    if( (vert_0_in_bounds == true) && (vert_1_in_bounds == false) && (vert_2_in_bounds == false) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_0, vert_1, max_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_0, vert_2, max_z_plane);

        std::vector<Math::Triangle> output(1);
        output[0] = Math::Triangle(vert_0, intersection_vert_0, intersection_vert_1);

        return output;
    }
    else if( (vert_0_in_bounds == false) && (vert_1_in_bounds == true) && (vert_2_in_bounds == false) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_1, vert_0, max_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_1, vert_2, max_z_plane);

        std::vector<Math::Triangle> output(1);
        output[0] = Math::Triangle(vert_1, intersection_vert_0, intersection_vert_1);

        return output;
    }
    else if( (vert_0_in_bounds == false) && (vert_1_in_bounds == false) && (vert_2_in_bounds == true) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_2, vert_0, max_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_2, vert_1, max_z_plane);

        std::vector<Math::Triangle> output(1);
        output[0] = Math::Triangle(vert_2, intersection_vert_0, intersection_vert_1);

        return output;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Case 4: Triangle is split by max_z_plane. 2 vertex below and 1 above. Create a quad.
    //---------------------------------------------------------------------------------------------------------------------//
    /*
    -   Vertex 0 and Vertex 1 are in bounds, Vertex 2 is out of bounds. Create two new triangles:
        -   Triangle 0 with vertices:
            -   Vertex 0
            -   Vertex 1
            -   Intersection of Vertex 0 and Vertex 2 with max_z_plane.
        -   Triangle 1 with vertices:
            -   Vertex 1
            -   Intersection of Vertex 0 and Vertex 2 with max_z_plane.
            -   Intersection of Vertex 1 and Vertex 2 with max_z_plane.

    -   Apply the same logic to all sub cases of Case 4.
    */
    if( (vert_0_in_bounds == true) && (vert_1_in_bounds == true) && (vert_2_in_bounds == false) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_0, vert_2, max_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_1, vert_2, max_z_plane);

        std::vector<Math::Triangle> output(2);
        output[0] = Math::Triangle(vert_0, vert_1, intersection_vert_0);
        output[1] = Math::Triangle(vert_1, intersection_vert_0, intersection_vert_1);

        return output;
    }
    else if( (vert_0_in_bounds == true) && (vert_1_in_bounds == false) && (vert_2_in_bounds == true) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_0, vert_1, max_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_2, vert_1, max_z_plane);

        std::vector<Math::Triangle> output(2);
        output[0] = Math::Triangle(vert_0, vert_2, intersection_vert_0);
        output[1] = Math::Triangle(vert_2, intersection_vert_0, intersection_vert_1);

        return output;
    }
    else if( (vert_0_in_bounds == false) && (vert_1_in_bounds == true) && (vert_2_in_bounds == true) )
    {
        Math::Vertex intersection_vert_0 = this->intersectionWithPlaneZ(vert_1, vert_0, max_z_plane);
        Math::Vertex intersection_vert_1 = this->intersectionWithPlaneZ(vert_2, vert_0, max_z_plane);

        std::vector<Math::Triangle> output(2);
        output[0] = Math::Triangle(vert_1, vert_2, intersection_vert_0);
        output[1] = Math::Triangle(vert_2, intersection_vert_0, intersection_vert_1);
        
        return output;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    // Should not get here.
    return std::vector<Math::Triangle>();
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<Math::Triangle> Renderer::clipTriangleBetweenZ
(
    const Math::Triangle& triangle,
    const float min_z_plane,
    const float max_z_plane
)
{
    std::vector<Math::Triangle> clipped_to_min = this->clipTriangleMinZ(triangle, min_z_plane);

    std::vector<Math::Triangle> result;
    for(const Math::Triangle& triangle_clip_min : clipped_to_min)
    {
        std::vector<Math::Triangle> clipped_to_min_max = this->clipTriangleMaxZ(triangle_clip_min, max_z_plane);

        for(const Math::Triangle& triangle_clip_min_max : clipped_to_min_max)
        {
            result.push_back(triangle_clip_min_max);
        }
    }

    return result;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
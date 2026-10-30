// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <vector>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "../math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::vector<Math::Triangle> Math::clipTriangleBetweenXYZ
(
    const Math::Triangle& triangle,
    const float min_x_plane,
    const float max_x_plane,
    const float min_y_plane,
    const float max_y_plane,
    const float min_z_plane,
    const float max_z_plane
)
{
    std::vector<Math::Triangle> triangles_clipped_between_x = std::vector<Math::Triangle>();
    std::vector<Math::Triangle> triangles_clipped_between_x_y = std::vector<Math::Triangle>();
    std::vector<Math::Triangle> triangles_clipped_between_x_y_z = std::vector<Math::Triangle>();

    triangles_clipped_between_x = Math::clipTriangleBetweenX(triangle, min_x_plane, max_x_plane);

    for(const Math::Triangle& triangle_clipped_between_x : triangles_clipped_between_x)
    {
        std::vector<Math::Triangle> temp_triangles = Math::clipTriangleBetweenY(triangle_clipped_between_x, min_y_plane, max_y_plane);

        for(const Math::Triangle& temp_triangle : temp_triangles)
        {
            triangles_clipped_between_x_y.push_back(temp_triangle);
        }
    }

    for(const Math::Triangle& triangle_clipped_between_x_y : triangles_clipped_between_x_y)
    {
        std::vector<Math::Triangle> temp_triangles = Math::clipTriangleBetweenZ(triangle_clipped_between_x_y, min_z_plane, max_z_plane);

        for(const Math::Triangle& temp_triangle : temp_triangles)
        {
            triangles_clipped_between_x_y_z.push_back(temp_triangle);
        }
    }

    return triangles_clipped_between_x_y_z;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <cmath>
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
std::vector<Math::Triangle> Math::clipAgainstPlaneMinMaxXYZ(const Math::Triangle& triangle)
{
    std::vector<Math::Triangle> traingles_clipped_min_max_x = Math::clipAgainstPlaneMinMaxX(triangle);

    std::vector<Math::Triangle> traingles_clipped_min_max_x_y;
    traingles_clipped_min_max_x_y.reserve(8);

    for(const Math::Triangle& traingle_clipped_min_max_x : traingles_clipped_min_max_x)
    {
        std::vector<Math::Triangle> clipped = Math::clipAgainstPlaneMinMaxY(traingle_clipped_min_max_x);
        traingles_clipped_min_max_x_y.insert(traingles_clipped_min_max_x_y.end(), clipped.begin(), clipped.end());
    }

    std::vector<Math::Triangle> traingles_clipped_min_max_x_y_z;
    traingles_clipped_min_max_x_y_z.reserve(16);

    for(const Math::Triangle& traingle_clipped_min_max_x_y_z : traingles_clipped_min_max_x_y)
    {
        std::vector<Math::Triangle> clipped = Math::clipAgainstPlaneMinMaxZ(traingle_clipped_min_max_x_y_z);
        traingles_clipped_min_max_x_y_z.insert(traingles_clipped_min_max_x_y_z.end(), clipped.begin(), clipped.end());
    }

    return traingles_clipped_min_max_x_y_z;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
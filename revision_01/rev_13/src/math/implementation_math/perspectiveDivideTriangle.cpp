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
#include "../math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Triangle Math::perspectiveDivideTriangle(const Math::Triangle& triangle)
{
    Math::Triangle output = triangle;

    float w;
    float inv_w;

    Math::Vertex& v0 = output.m_v0;
    w = v0.m_position.m_data[3];
    if(w <= 0.0f)
    {
        v0.m_position.m_data[0] = 0.0f;
        v0.m_position.m_data[1] = 0.0f;
        v0.m_position.m_data[2] = 0.0f;
        v0.m_position.m_data[3] = 0.0f;
    }
    else
    {
        inv_w = 1.0f / w;

        v0.m_position.m_data[0] = v0.m_position.m_data[0] * inv_w;
        v0.m_position.m_data[1] = v0.m_position.m_data[1] * inv_w;
        v0.m_position.m_data[2] = v0.m_position.m_data[2] * inv_w;
        v0.m_position.m_data[3] = v0.m_position.m_data[3];
    }

    Math::Vertex& v1 = output.m_v1;
    w = v1.m_position.m_data[3];
    if(w <= 0.0f)
    {
        v1.m_position.m_data[0] = 0.0f;
        v1.m_position.m_data[1] = 0.0f;
        v1.m_position.m_data[2] = 0.0f;
        v1.m_position.m_data[3] = 0.0f;
    }
    else
    {
        inv_w = 1.0f / w;

        v1.m_position.m_data[0] = v1.m_position.m_data[0] * inv_w;
        v1.m_position.m_data[1] = v1.m_position.m_data[1] * inv_w;
        v1.m_position.m_data[2] = v1.m_position.m_data[2] * inv_w;
        v1.m_position.m_data[3] = v1.m_position.m_data[3];
    }

    Math::Vertex& v2 = output.m_v2;
    w = v2.m_position.m_data[3];
    if(w <= 0.0f)
    {
        v2.m_position.m_data[0] = 0.0f;
        v2.m_position.m_data[1] = 0.0f;
        v2.m_position.m_data[2] = 0.0f;
        v2.m_position.m_data[3] = 0.0f;
    }
    else
    {
        inv_w = 1.0f / w;

        v2.m_position.m_data[0] = v2.m_position.m_data[0] * inv_w;
        v2.m_position.m_data[1] = v2.m_position.m_data[1] * inv_w;
        v2.m_position.m_data[2] = v2.m_position.m_data[2] * inv_w;
        v2.m_position.m_data[3] = v2.m_position.m_data[3];
    }

    return output;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
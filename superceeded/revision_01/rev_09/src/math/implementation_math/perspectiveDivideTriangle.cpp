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
        v0.m_position.m_data[0] = v0.m_position.m_data[0] / w;
        v0.m_position.m_data[1] = v0.m_position.m_data[1] / w;
        v0.m_position.m_data[2] = v0.m_position.m_data[2] / w;
        v0.m_position.m_data[3] = 1.0f;
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
        v1.m_position.m_data[0] = v1.m_position.m_data[0] / w;
        v1.m_position.m_data[1] = v1.m_position.m_data[1] / w;
        v1.m_position.m_data[2] = v1.m_position.m_data[2] / w;
        v1.m_position.m_data[3] = 1.0f;
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
        v2.m_position.m_data[0] = v2.m_position.m_data[0] / w;
        v2.m_position.m_data[1] = v2.m_position.m_data[1] / w;
        v2.m_position.m_data[2] = v2.m_position.m_data[2] / w;
        v2.m_position.m_data[3] = 1.0f;
    }

    /*
    Math::Triangle output = triangle;

    for(int i = 0; i < 3; i++)
    {
        Math::Vec4_f& output_position = output.m_vertices[i].m_position;

        float w = output_position.m_data[3];

        if(w <= 0.0f)
        {
            output_position.m_data[0] = 0.0f;
            output_position.m_data[1] = 0.0f;
            output_position.m_data[2] = 0.0f;
            output_position.m_data[3] = 0.0f;
        }
        else
        {
            output_position.m_data[0] = output_position.m_data[0] / w;
            output_position.m_data[1] = output_position.m_data[1] / w;
            output_position.m_data[2] = output_position.m_data[2] / w;
            output_position.m_data[3] = 1.0f;
        }
    }
    */

    return output;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
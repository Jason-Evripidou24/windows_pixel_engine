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
#include "renderer.hpp"

#include "../00_types/level_00/pixel/pixel.hpp"
#include "../00_types/level_00/vec3/vec3_f.hpp"

#include "../02_window/backbuffer/backbuffer.hpp"

#include "../01_utils/math/math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::clear(Backbuffer* backbuffer, const Pixel& color)
{
    //---------------------------------------------------------------------------------------------------------------------//
    if(backbuffer == nullptr) { return; }
    //---------------------------------------------------------------------------------------------------------------------//

    backbuffer->clear(color);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawPixel(Backbuffer* backbuffer, float x, float y, float z, const Pixel& color)
{
    //---------------------------------------------------------------------------------------------------------------------//
    if
    (
        (backbuffer == nullptr)   ||
        (x < -1.0f) || (x > 1.0f) ||
        (y < -1.0f) || (y > 1.0f) ||
        (z < -1.0f) || (z > 1.0f)
    )
    {
        return;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    int screen_x = (x + 1.0f) * backbuffer->m_width * 0.5f;
    if(screen_x < 0) { screen_x = 0; } 
    if(screen_x >= backbuffer->m_width) { screen_x = backbuffer->m_width - 1; }

    int screen_y = (-y + 1.0f) * backbuffer->m_height * 0.5f;
    if(screen_y < 0) { screen_y = 0; } 
    if(screen_y >= backbuffer->m_height) { screen_y = backbuffer->m_height - 1; }

    backbuffer->setPixel(x, y, z, color);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Each Vec3_f represents an (x, y, z) coordinate that is drawn if x,y,z are between [-1, 1]
*/
void Renderer::drawLine(Backbuffer* backbuffer, Vertex3_f& vert0, Vertex3_f& vert1)
{
    //---------------------------------------------------------------------------------------------------------------------//
    if(backbuffer == nullptr) { return; }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    int screen_x0 = (vert0.m_position.m_data[0] + 1.0f) * backbuffer->m_width * 0.5f;
    int screen_y0 = (-(vert0.m_position.m_data[1]) + 1.0f) * backbuffer->m_height * 0.5f;
    float z0 = vert0.m_position.m_data[2];

    int screen_x1 = (vert1.m_position.m_data[0] + 1.0f) * backbuffer->m_width * 0.5f;
    int screen_y1 = (-(vert1.m_position.m_data[1]) + 1.0f) * backbuffer->m_height * 0.5f;
    float z1 = vert1.m_position.m_data[2];

    float colB0 = (float)vert0.m_color.getB();
    float colG0 = (float)vert0.m_color.getG();
    float colR0 = (float)vert0.m_color.getR();
    float colA0 = (float)vert0.m_color.getA();

    float colB1 = (float)vert1.m_color.getB();
    float colG1 = (float)vert1.m_color.getG();
    float colR1 = (float)vert1.m_color.getR();
    float colA1 = (float)vert1.m_color.getA();
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    // Amount of pixels width and height.
    //---------------------------------------------------------------------------------------------------------------------//
    int dx = screen_x1 - screen_x0;
    int dy = screen_y1 - screen_y0;

    int abs_dx = dx; if(abs_dx < 0) { abs_dx *= -1; }
    int abs_dy = dy; if(abs_dy < 0) { abs_dy *= -1; }

    int steps = abs_dx; if(abs_dy > steps) { steps = abs_dy; }

    if(steps == 0)
    {
        backbuffer->setPixel(screen_x0, screen_y0, (z0 + z1) * 0.5f, vert0.m_color);
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    for(int i = 0; i < steps; i++)
    {
        float t = static_cast<float>(i) / static_cast<float>(steps);

        int curr_x = screen_x0 + (dx * i) / steps;
        int curr_y = screen_y0 + (dy * i) / steps;
        float curr_z = (z0 * (1.0f - t)) + (z1 * t);

        uint8_t curr_col_b = (uint8_t)((colB0 * (1.0f - t)) + (colB1 * t));
        uint8_t curr_col_g = (uint8_t)((colG0 * (1.0f - t)) + (colG1 * t));
        uint8_t curr_col_r = (uint8_t)((colR0 * (1.0f - t)) + (colR1 * t));
        uint8_t curr_col_a = (uint8_t)((colA0 * (1.0f - t)) + (colA1 * t));
        Pixel color(curr_col_b, curr_col_g, curr_col_r, curr_col_a);

        backbuffer->setPixel(curr_x, curr_y, curr_z, color);
    }
    //---------------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Each Vec3_f represents a screen coord vertex (x == x_screen_coord, y == y_screen_coord, z == depth)
*/
void Renderer::drawWireframeTriangle(Backbuffer* backbuffer, Vertex3_f& v0, Vertex3_f& v1, Vertex3_f& v2)
{
    this->drawLine(backbuffer, v0, v1);
    this->drawLine(backbuffer, v0, v2);
    this->drawLine(backbuffer, v1, v2);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Each Vertex3_f contains NDC coordinates:
    x, y, z ∈ [-1, 1]

-   This function:
    1. Converts vertices to screen coordinates.
    2. Computes a screen-space bounding box.
    3. Uses barycentric coordinates to determine whether each pixel is inside.
    4. Interpolates depth and color.
    5. Writes pixels through the depth buffer.
*/
void Renderer::drawFilledTriangle
(
    Backbuffer* backbuffer,
    Vertex3_f& v0,
    Vertex3_f& v1,
    Vertex3_f& v2
)
{
    //-----------------------------------------------------------------------------------------------------------------//
    if(backbuffer == nullptr)
    {
        return;
    }
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Convert NDC to screen coordinates.
    //-----------------------------------------------------------------------------------------------------------------//
    int x0 = (v0.m_position.m_data[0] + 1.0f) * backbuffer->m_width * 0.5f;
    int y0 = (-v0.m_position.m_data[1] + 1.0f) * backbuffer->m_height * 0.5f;
    float z0 = v0.m_position.m_data[2];

    int x1 = (v1.m_position.m_data[0] + 1.0f) * backbuffer->m_width * 0.5f;
    int y1 = (-v1.m_position.m_data[1] + 1.0f) * backbuffer->m_height * 0.5f;
    float z1 = v1.m_position.m_data[2];

    int x2 = (v2.m_position.m_data[0] + 1.0f) * backbuffer->m_width * 0.5f;
    int y2 = (-v2.m_position.m_data[1] + 1.0f) * backbuffer->m_height * 0.5f;
    float z2 = v2.m_position.m_data[2];
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Edge function.
    //-----------------------------------------------------------------------------------------------------------------//
    auto edge = [](int ax, int ay, int bx, int by, int px, int py) -> float
    {
        return static_cast<float>
        (
            (px - ax) * (by - ay) -
            (py - ay) * (bx - ax)
        );
    };
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Triangle area.
    //-----------------------------------------------------------------------------------------------------------------//
    float area = edge(x0, y0, x1, y1, x2, y2);

    // Degenerate triangle.
    if(area == 0.0f)
    {
        return;
    }
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Compute bounding box.
    //-----------------------------------------------------------------------------------------------------------------//
    int min_x = x0;
    if(x1 < min_x) { min_x = x1; }
    if(x2 < min_x) { min_x = x2; }

    int max_x = x0;
    if(x1 > max_x) { max_x = x1; }
    if(x2 > max_x) { max_x = x2; }

    int min_y = y0;
    if(y1 < min_y) { min_y = y1; }
    if(y2 < min_y) { min_y = y2; }

    int max_y = y0;
    if(y1 > max_y) { max_y = y1; }
    if(y2 > max_y) { max_y = y2; }

    // Clamp bounding box to the backbuffer.
    if(min_x < 0) { min_x = 0; }
    if(min_y < 0) { min_y = 0; }

    if(max_x >= backbuffer->m_width)
    {
        max_x = backbuffer->m_width - 1;
    }

    if(max_y >= backbuffer->m_height)
    {
        max_y = backbuffer->m_height - 1;
    }
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Rasterize all pixels inside the bounding box.
    //-----------------------------------------------------------------------------------------------------------------//
    for(int y = min_y; y <= max_y; y++)
    {
        for(int x = min_x; x <= max_x; x++)
        {
            // Compute barycentric edge values.
            float w0 = edge(x1, y1, x2, y2, x, y);
            float w1 = edge(x2, y2, x0, y0, x, y);
            float w2 = edge(x0, y0, x1, y1, x, y);

            // Accept either winding order.
            bool all_non_negative =
            (
                (w0 >= 0.0f) &&
                (w1 >= 0.0f) &&
                (w2 >= 0.0f)
            );

            bool all_non_positive =
            (
                (w0 <= 0.0f) &&
                (w1 <= 0.0f) &&
                (w2 <= 0.0f)
            );

            if(!(all_non_negative || all_non_positive))
            {
                continue;
            }

            // Normalize barycentric coordinates.
            w0 /= area;
            w1 /= area;
            w2 /= area;

            //-----------------------------------------------------------------//
            // Interpolate depth.
            //-----------------------------------------------------------------//
            float z =
                (z0 * w0) +
                (z1 * w1) +
                (z2 * w2);

            //-----------------------------------------------------------------//
            // Interpolate color.
            //-----------------------------------------------------------------//
            uint8_t b = static_cast<uint8_t>
            (
                v0.m_color.getB() * w0 +
                v1.m_color.getB() * w1 +
                v2.m_color.getB() * w2
            );

            uint8_t g = static_cast<uint8_t>
            (
                v0.m_color.getG() * w0 +
                v1.m_color.getG() * w1 +
                v2.m_color.getG() * w2
            );

            uint8_t r = static_cast<uint8_t>
            (
                v0.m_color.getR() * w0 +
                v1.m_color.getR() * w1 +
                v2.m_color.getR() * w2
            );

            uint8_t a = static_cast<uint8_t>
            (
                v0.m_color.getA() * w0 +
                v1.m_color.getA() * w1 +
                v2.m_color.getA() * w2
            );

            Pixel color(b, g, r, a);

            //-----------------------------------------------------------------//
            // Write pixel.
            //-----------------------------------------------------------------//
            backbuffer->setPixel(x, y, z, color);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Draws every indexed triangle in the mesh as a wireframe.
void Renderer::drawWireframeObject
(
    Backbuffer* backbuffer,
    const Object& object,
    const Mat4_f& view_projection
)
{
    //-----------------------------------------------------------------------------------------------------------------//
    if
    (
        (backbuffer == nullptr) ||
        (object.m_mesh == nullptr)
    )
    {
        return;
    }
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Final transform = ViewProjection * Model
    //-----------------------------------------------------------------------------------------------------------------//
    Mat4_f model = object.calcModelMatrix();
    Mat4_f transform = Math::multiply(view_projection, model);
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Draw each indexed triangle.
    //-----------------------------------------------------------------------------------------------------------------//
    for(int i = 0; i < object.m_mesh->m_index_count; i += 3)
    {
        // Indices for one triangle.
        int index0 = object.m_mesh->m_indices[i + 0];
        int index1 = object.m_mesh->m_indices[i + 1];
        int index2 = object.m_mesh->m_indices[i + 2];

        // Source vertices (object space).
        const Vertex4_f& src_v0 = object.m_mesh->m_vertices[index0];
        const Vertex4_f& src_v1 = object.m_mesh->m_vertices[index1];
        const Vertex4_f& src_v2 = object.m_mesh->m_vertices[index2];

        //---------------------------------------------------------------------//
        // Transform to clip space.
        //---------------------------------------------------------------------//
        Vec4_f clip_pos0 = Math::multiply(transform, src_v0.m_position);
        Vec4_f clip_pos1 = Math::multiply(transform, src_v1.m_position);
        Vec4_f clip_pos2 = Math::multiply(transform, src_v2.m_position);

        //---------------------------------------------------------------------//
        // Skip vertices behind the camera or invalid for perspective divide.
        //---------------------------------------------------------------------//
        if
        (
            (clip_pos0.m_data[3] == 0.0f) ||
            (clip_pos1.m_data[3] == 0.0f) ||
            (clip_pos2.m_data[3] == 0.0f)
        )
        {
            continue;
        }

        //---------------------------------------------------------------------//
        // Convert clip coordinates to NDC.
        //---------------------------------------------------------------------//
        Vertex3_f ndc_v0;
        ndc_v0.m_position = Math::clipCoordsToNormalisedDeviceCoords(clip_pos0);
        ndc_v0.m_color = src_v0.m_color;

        Vertex3_f ndc_v1;
        ndc_v1.m_position = Math::clipCoordsToNormalisedDeviceCoords(clip_pos1);
        ndc_v1.m_color = src_v1.m_color;

        Vertex3_f ndc_v2;
        ndc_v2.m_position = Math::clipCoordsToNormalisedDeviceCoords(clip_pos2);
        ndc_v2.m_color = src_v2.m_color;

        //---------------------------------------------------------------------//
        // Draw triangle edges.
        //---------------------------------------------------------------------//
        this->drawWireframeTriangle(backbuffer, ndc_v0, ndc_v1, ndc_v2);
    }
    //-----------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //

#include "../02_window/backbuffer/hud.hpp"
#include "../00_types/level_00/font/ascii_font.hpp"
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
// Draws every indexed triangle in the mesh as a wireframe.
void Renderer::drawFilledObject
(
    Backbuffer* backbuffer,
    const Object& object,
    const Mat4_f& view_projection
)
{
    //-----------------------------------------------------------------------------------------------------------------//
    if
    (
        (backbuffer == nullptr) ||
        (object.m_mesh == nullptr)
    )
    {
        return;
    }
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Final transform = ViewProjection * Model
    //-----------------------------------------------------------------------------------------------------------------//
    Mat4_f model = object.calcModelMatrix();
    Mat4_f transform = Math::multiply(view_projection, model);
    //-----------------------------------------------------------------------------------------------------------------//

    //-----------------------------------------------------------------------------------------------------------------//
    // Draw each indexed triangle.
    //-----------------------------------------------------------------------------------------------------------------//
    for(int i = 0; i < object.m_mesh->m_index_count; i += 3)
    {
        // Indices for one triangle.
        int index0 = object.m_mesh->m_indices[i + 0];
        int index1 = object.m_mesh->m_indices[i + 1];
        int index2 = object.m_mesh->m_indices[i + 2];

        // Source vertices (object space).
        const Vertex4_f& src_v0 = object.m_mesh->m_vertices[index0];
        const Vertex4_f& src_v1 = object.m_mesh->m_vertices[index1];
        const Vertex4_f& src_v2 = object.m_mesh->m_vertices[index2];

        //---------------------------------------------------------------------//
        // Transform to clip space.
        //---------------------------------------------------------------------//
        Vec4_f clip_pos0 = Math::multiply(transform, src_v0.m_position);
        Vec4_f clip_pos1 = Math::multiply(transform, src_v1.m_position);
        Vec4_f clip_pos2 = Math::multiply(transform, src_v2.m_position);

        bool outside =
        (
            (clip_pos0.m_data[0] < -clip_pos0.m_data[3] && clip_pos1.m_data[0] < -clip_pos1.m_data[3] && clip_pos2.m_data[0] < -clip_pos2.m_data[3]) ||
            (clip_pos0.m_data[0] >  clip_pos0.m_data[3] && clip_pos1.m_data[0] >  clip_pos1.m_data[3] && clip_pos2.m_data[0] >  clip_pos2.m_data[3]) ||

            (clip_pos0.m_data[1] < -clip_pos0.m_data[3] && clip_pos1.m_data[1] < -clip_pos1.m_data[3] && clip_pos2.m_data[1] < -clip_pos2.m_data[3]) ||
            (clip_pos0.m_data[1] >  clip_pos0.m_data[3] && clip_pos1.m_data[1] >  clip_pos1.m_data[3] && clip_pos2.m_data[1] >  clip_pos2.m_data[3]) ||

            (clip_pos0.m_data[2] < -clip_pos0.m_data[3] && clip_pos1.m_data[2] < -clip_pos1.m_data[3] && clip_pos2.m_data[2] < -clip_pos2.m_data[3]) ||
            (clip_pos0.m_data[2] >  clip_pos0.m_data[3] && clip_pos1.m_data[2] >  clip_pos1.m_data[3] && clip_pos2.m_data[2] >  clip_pos2.m_data[3])
        );
        if(outside)
        {
            continue;
        }

        //---------------------------------------------------------------------//
        // Skip vertices behind the camera or invalid for perspective divide.
        //---------------------------------------------------------------------//
        if
        (
            (clip_pos0.m_data[3] == 0.0f) ||
            (clip_pos1.m_data[3] == 0.0f) ||
            (clip_pos2.m_data[3] == 0.0f)
        )
        {
            continue;
        }

        //---------------------------------------------------------------------//
        // Convert clip coordinates to NDC.
        //---------------------------------------------------------------------//
        Vertex3_f ndc_v0;
        ndc_v0.m_position = Math::clipCoordsToNormalisedDeviceCoords(clip_pos0);
        ndc_v0.m_color = src_v0.m_color;

        Vertex3_f ndc_v1;
        ndc_v1.m_position = Math::clipCoordsToNormalisedDeviceCoords(clip_pos1);
        ndc_v1.m_color = src_v1.m_color;

        Vertex3_f ndc_v2;
        ndc_v2.m_position = Math::clipCoordsToNormalisedDeviceCoords(clip_pos2);
        ndc_v2.m_color = src_v2.m_color;

        //---------------------------------------------------------------------//
        // Draw triangle edges.
        //---------------------------------------------------------------------//
        this->drawFilledTriangle(backbuffer, ndc_v0, ndc_v1, ndc_v2);
    }
    //-----------------------------------------------------------------------------------------------------------------//
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
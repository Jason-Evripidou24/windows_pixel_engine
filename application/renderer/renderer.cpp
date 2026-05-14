// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <algorithm>
#include <cmath>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "font.hpp"
#include "renderer.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::init(Backbuffer* backbuffer)
{
    m_backbuffer = backbuffer;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::clear(const Pixel& color)
{
    m_backbuffer->clear(color);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawPixel(int x, int y, float depth, const Pixel& color)
{
    m_backbuffer->setPixel(x, y, depth, color);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Each Vec3_f represents a screen coord vertex (x_screen, y_screen, z == depth)
*/
void Renderer::drawLine(const Vec3_f& a, const Vec3_f& b, const Pixel& color)
{
    int ax = (int)std::round(a.m_data[0]);
    int ay = (int)std::round(a.m_data[1]);

    int bx = (int)std::round(b.m_data[0]);
    int by = (int)std::round(b.m_data[1]);

    float az = a.m_data[2];
    float bz = b.m_data[2];

    int dx = std::abs(bx - ax);
    int dy = std::abs(by - ay);

    int sx = (ax < bx) ? 1 : -1;
    int sy = (ay < by) ? 1 : -1;

    int err = dx - dy;

    int steps = dx; if(dy > dx) { steps = dy; }

    float t = 0.0f;
    float dt = (steps == 0) ? 0.0f : 1.0f / steps;

    while(true)
    {
        float depth = az + (bz - az) * t;

        this->drawPixel(ax, ay, depth, color);

        if( (ax == bx) && (ay == by) ) { break; }

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            ax += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            ay += sy;
        }

        t += dt;
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
/*
-   Each Vec3_f represents a screen coord vertex (x == x_screen_coord, y == y_screen_coord, z == depth)
*/
void Renderer::drawWireframeTrigngle(const Vec3_f& a, const Vec3_f& b, const Vec3_f& c, const Pixel& color)
{
    this->drawLine(a, b, color);
    this->drawLine(b, c, color);
    this->drawLine(c, a, color);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawTriangle(const Vec3_f& v0, const Vec3_f& v1, const Vec3_f& v2, const Pixel& color)
{
    float x0 = v0.m_data[0];
    float y0 = v0.m_data[1];
    float z0 = v0.m_data[2];

    float x1 = v1.m_data[0];
    float y1 = v1.m_data[1];
    float z1 = v1.m_data[2];

    float x2 = v2.m_data[0];
    float y2 = v2.m_data[1];
    float z2 = v2.m_data[2];

    // Bounding box
    int minX = (int)std::floor(x0);
    if (x1 < minX) { minX = (int)std::floor(x1); }
    if (x2 < minX) { minX = (int)std::floor(x2); }

    int maxX = (int)std::ceil(x0);
    if (x1 > maxX) { maxX = (int)std::ceil(x1); }
    if (x2 > maxX) { maxX = (int)std::ceil(x2); }

    int minY = (int)std::floor(y0);
    if (y1 < minY) { minY = (int)std::floor(y1); }
    if (y2 < minY) { minY = (int)std::floor(y2); }

    int maxY = (int)std::ceil(y0);
    if (y1 > maxY) { maxY = (int)std::ceil(y1); }
    if (y2 > maxY) { maxY = (int)std::ceil(y2); }

    // Clamp to framebuffer
    if(minX < 0) { minX = 0; }
    if(minY < 0) { minY = 0; }
    if(maxX >= m_backbuffer->m_width)  { maxX = m_backbuffer->m_width - 1; }
    if(maxY >= m_backbuffer->m_height) { maxY = m_backbuffer->m_height - 1; }

    // Signed area
    float area = ((x1 - x0) * (y2 - y0)) - ((y1 - y0) * (x2 - x0));
    if(area == 0.0f) { return; }

    float invArea = 1.0f / area;

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            float px = (float)x + 0.5f;
            float py = (float)y + 0.5f;

            float w0 = (((x1 - px) * (y2 - py)) - ((y1 - py) * (x2 - px))) * invArea;

            float w1 = (((x2 - px) * (y0 - py)) - ((y2 - py) * (x0 - px))) * invArea;

            float w2 = 1.0f - w0 - w1;

            // Inside test
            if(w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f)
            {
                float depth = (z0 * w0) + (z1 * w1) + (z2 * w2);
                this->drawPixel(x, y, depth, color);
            }
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawObject(Object& object, const Mat4_f& view_mat, const Mat4_f& proj_mat, const Pixel& color)
{
    const Mat4_f model_mat = object.calcModelMatrix();

    Mat4_f transform = Math::multiply(proj_mat, model_mat);

    for(int i = 0; i < object.m_vertex_count; i++)
    {
        object.m_clip[i] = Math::multiply(transform, object.m_vertices[i]);
    }
    for(int i = 0; i < object.m_vertex_count; i++)
    {
        object.m_ndc[i] = Math::clipCoordsToNormalisedDeviceCoords(object.m_clip[i]);
    }
    for(int i = 0; i < object.m_vertex_count; i++)
    {
        object.m_screen[i] = Math::normalisedDeviceCoordsToScreenCoords
        (
            object.m_ndc[i],
            m_backbuffer->m_width,
            m_backbuffer->m_height
        );
    }

    for(int i = 0; i < object.m_index_count; i += 3)
    {
        this->drawWireframeTrigngle
        (
            object.m_screen[object.m_indices[i + 0]],
            object.m_screen[object.m_indices[i + 1]],
            object.m_screen[object.m_indices[i + 2]],
            color
        );
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawCircle(int cx, int cy, int r, const Pixel& color)
{
    int x = r;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        // 8-way symmetry
        this->drawPixel(cx + x, cy + y, 0.0f, color);
        this->drawPixel(cx + y, cy + x, 0.0f, color);
        this->drawPixel(cx - y, cy + x, 0.0f, color);
        this->drawPixel(cx - x, cy + y, 0.0f, color);
        this->drawPixel(cx - x, cy - y, 0.0f, color);
        this->drawPixel(cx - y, cy - x, 0.0f, color);
        this->drawPixel(cx + y, cy - x, 0.0f, color);
        this->drawPixel(cx + x, cy - y, 0.0f, color);

        y++;

        if(err <= 0)
        {
            err += 2 * y + 1;
        }
        else
        {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Renderer::drawFilledCircle(int cx, int cy, int r, const Pixel& color)
{
    for (int y = -r; y <= r; y++)
    {
        int dx = (int)sqrtf((float)(r * r - y * y));

        int xStart = cx - dx;
        int xEnd   = cx + dx;
        int py     = cy + y;

        for (int x = xStart; x <= xEnd; x++)
        {
            drawPixel(x, py, 0.0f, color);
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
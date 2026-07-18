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
#include "hud.hpp"
#include "font.hpp"
#include "renderer.hpp"
#include "../pixel/pixel.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Hud::drawCharacter(Renderer& renderer, int x, int y, char character, const Pixel& color, AsciiFont& font) const
{
    uint8_t c = static_cast<uint8_t>(character);

    const uint8_t* glyph = font.m_ascii_font_basic_bitmap[c];

    for(int row = 0; row < font.glyph_height; row++)
    {
        uint8_t bits = glyph[row];

        for(int col = 0; col < font.glyph_width; col++)
        {
            // MSB → LSB (left to right)
            //bool pixel_on = bits & (0x80 >> col);
            bool pixel_on = bits & (1 << col);

            if(pixel_on)
            {
                renderer.drawPixel(x + col, y + row, 0.0f, color);
            }
        }
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Hud::drawText(Renderer& renderer, int x, int y, const char* text, const Pixel& color, AsciiFont& font) const
{
    int cursor_x = x;

    for(int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        this->drawCharacter(renderer, cursor_x, y, c, color, font);

        cursor_x += font.glyph_width + font.spacing;
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Hud::drawMat4_f(Renderer& renderer, int x, int y, const Mat4_f& mat, const Pixel& color, AsciiFont& font) const
{
    char buffer[64];

    for(int row = 0; row < 4; row++)
    {
        // Build one row as a string
        // Example:
        // [  1.00  0.00  0.00  0.50 ]
        std::snprintf
        (
            buffer,
            sizeof(buffer),
            "[ %6.2f %6.2f %6.2f %6.2f ]",
            mat.m_data[row * 4 + 0],
            mat.m_data[row * 4 + 1],
            mat.m_data[row * 4 + 2],
            mat.m_data[row * 4 + 3]
        );

        // Draw the row
        this->drawText(renderer, x, y + row * (font.glyph_height + 2), buffer, color, font);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Hud::drawVec4_fRow(Renderer& renderer, int x, int y, const Vec4_f& vec, const Pixel& color, AsciiFont& font) const
{
    char buffer[64];

    std::snprintf
    (
        buffer,
        sizeof(buffer),
        "[ %6.2f %6.2f %6.2f %6.2f ]",
        vec.m_data[0],
        vec.m_data[1],
        vec.m_data[2],
        vec.m_data[3]
    );

    this->drawText(renderer, x, y, buffer, color, font);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
void Hud::drawVec4_fCol(Renderer& renderer, int x, int y, const Vec4_f& vec, const Pixel& color, AsciiFont& font) const
{
    char buffer[32];

    for (int row = 0; row < 4; row++)
    {
        // Format one value per line
        std::snprintf(buffer, sizeof(buffer), "| %6.2f |", vec.m_data[row]);

        // Draw this value on its own line
        this->drawText(renderer, x, y + row * (font.glyph_height + 2), buffer, color, font);
    }
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
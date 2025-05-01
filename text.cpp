#include "text.h" // Using stb_easy_fonts: https://github.com/nothings/stb/blob/master/stb_easy_font.h

namespace Tmpl8
{
    void Text::printOnScreen(const std::string& txt, vec2 pos, Surface* screen, Pixel c)
    {
        const int buffer_size = 99999;          // A large buffer static size just in case a text is too long
        static char vertexBuffer[buffer_size];  // Create the buffer of verts to read from to get the positions later for the draw of the lines
        const char* text = (char*)txt.c_str();  // Cast to char

        int num_quads = stb_easy_font_print(pos.x, pos.y, (char*)txt.c_str(), NULL, vertexBuffer, buffer_size); // Not using the color parameter from stb_easy_font, 
                                                                                                                // rendering the color rather in Line()

        float* verts = (float*)vertexBuffer;    // Convert to float to make vec2s and use Line()

        for (int i = 0; i < num_quads; i++)     // Go through all the quads to draw all the lines from verts
        {
            int base = i * 16;                  // 1 quad = 4 verts, 1 vert = 2 floats (x;y), 1 float = 4 bytes, so 1 quad = 4 verts * 2 floats * 4 bytes = 32 bytes. We process 2 quads, so 32 bytes / 2 = 16 bytes per quad.
            vec2 pos[4]; 
                                                                    //                      -* OFFSETS: *-
            vec2 pos0 = vec2(verts[base + 0], verts[base + 1]);     // Top Left      ->  x: 0 * 4 || y: x + 1   ->  So basically vertex = (x: i * 4 || y: i * 4 + 1)
            vec2 pos1 = vec2(verts[base + 4], verts[base + 5]);     // Top Right     ->  x: 1 * 4 || y: x + 1       the y value is stored right after x so we add 1 to access
            vec2 pos2 = vec2(verts[base + 8], verts[base + 9]);     // Bottom Right  ->  x: 2 * 4 || y: x + 1       it in the vertexBuffer
            vec2 pos3 = vec2(verts[base + 12], verts[base + 13]);   // Bottom Left   ->  x: 3 * 4 || y: x + 1

            screen->Line(pos0, pos1, c); // Top
            screen->Line(pos1, pos2, c); // Right
            screen->Line(pos2, pos3, c); // Bottom
            screen->Line(pos3, pos0, c); // Left
        }
    }
}
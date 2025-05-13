#pragma once
#include "surface.h"
#include <string>
#include "../include/stb_easy_font.h"

namespace Tmpl8
{
    class Text
    {
    public:

        // Function to print stb_easy_font text on the screen with a given text, position, surface to draw on, size and color.
        void printOnScreen(const std::string& txt, vec2 pos, Surface* screen, vec2 size, Pixel c);
    };
}

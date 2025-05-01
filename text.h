#pragma once
#include "surface.h"
#include <string>
#include "stb_easy_font.h"

namespace Tmpl8
{
    class Text
    {
    public:
        void printOnScreen(const std::string& txt, vec2 pos, Surface* screen, Pixel c);
    };
}

#pragma once
#include "surface.h"

namespace Tmpl8
{
    // Debug class
    class Debug {
    public:
        void drawHitbox(int x, int y, Surface* screen);
        void displayDebug(Surface* screen);
    };
};
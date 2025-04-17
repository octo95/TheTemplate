#pragma once
#include "surface.h"
#include "camera.h"
#include "tilemap.h"

namespace Tmpl8
{
    // Debug class
    class Debug {

    public:
        void drawHitbox(int x, int y, Surface* screen);
        void displayDebug(Surface* screen, float deltaTime);
        void defaultPos();
        void nextDebugMap();
        int getFPS(float deltaTime);
    private:
        Camera camera;
        TileMap map;
    };
}
#pragma once
#include "camera.h"
#include "surface.h"

namespace Tmpl8
{
    class Debug {
    public:
        void setCamera(Camera* cam) { camera = cam; }
        void drawHitbox(int x, int y, Surface* screen);
        void displayDebug(Surface* screen, float deltaTime);
        void defaultPos();
        void nextDebugMap();
        int getFPS(float deltaTime);
    private:
        Camera* camera;
    };
};
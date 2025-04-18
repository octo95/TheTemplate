#pragma once
#include "camera.h"
#include "surface.h"
#include "template.h"
#include "player.h"

namespace Tmpl8
{
    class TileMap;

    class Debug {
    public:
        void setCamera(Camera* cam) { camera = cam; }
        void setMap(TileMap* tilemap) { map = tilemap; }
        void setPlayer(Player* p) { player = p; }
        void drawHitbox(const vec2& pos, Surface* screen);
        void displayDebug(Surface* screen, float deltaTime);
        void defaultPos();
        void nextDebugMap();
        int getFPS(float deltaTime);
    private:
        Camera* camera;
        TileMap* map;
        Player* player;
    };
}

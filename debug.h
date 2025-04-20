#pragma once
#include "camera.h"
#include "surface.h"
#include "template.h"
#include "player.h"
#include "collectible.h"
#include "tilemap.h"
#include "wall.h"

namespace Tmpl8
{
    class TileMap;

    class Debug {
    public:
        Debug(Camera& cameraRef, TileMap& tilemapRef, Player& playerRef, CollectibleMap& collectibleRef, WallMap& wallRef);
        void drawHitbox(const vec2& pos, Surface* screen);
        void displayDebug(Surface* screen, float deltaTime);
        void defaultPos();
        void nextDebugMap();
        int getFPS(float deltaTime);
        void drawVelocityNorm(Surface* screen);
        void restartCurrentLevel();
    private:
        Camera& camera;
        TileMap& tilemap;
        Player& player;
        CollectibleMap& collectible;
        WallMap& wall;
    };
}

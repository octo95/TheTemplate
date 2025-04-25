#pragma once
#include "camera.h"
#include "surface.h"
#include "template.h"
#include "player.h"
#include "collectible.h"
#include "tilemap.h"
#include "wall.h"
#include "ai_follow.h"
#include "level.h"
#include "collisions.h"
#include "menu.h"

namespace Tmpl8
{
    class TileMap;

    class Debug {
    public:
        Debug(Camera& cameraRef, TileMap& tilemapRef, Player& playerRef, CollectibleMap& collectibleRef, WallMap& wallRef, AI_Follow& ai_followRef, Level& levelRef, Collisions& collisionRef, Menu& menuRef);
        void drawHitbox(const vec2& pos, Surface* screen);
        void drawTileHitbox(const vec2& pos, Surface* screen);
        void displayDebug(Surface* screen, float deltaTime);
        void defaultPos();
        void nextDebugMap();
        int getFPS(float deltaTime);
        void drawVelocityNorm(Surface* screen);
        void restartCurrentLevel();
        void drawDistancePlayerToAI(vec2 ai_pos, Surface* screen);
        void gameSlowMode();
        bool gameSlow = false;
        bool isTDown = false;
    private:
        Camera& camera;
        TileMap& tilemap;
        Player& player;
        CollectibleMap& collectible;
        WallMap& wall;
        AI_Follow& ai_follow;
        Level& level;
        Collisions& collisions;
        Menu& menu;
    };
}

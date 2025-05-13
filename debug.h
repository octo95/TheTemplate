#pragma once
#include "ai_follow.h"
#include "ai_patrol.h"
#include "camera.h"
#include "collisions.h"
#include "collectible.h"
#include "level.h"
#include "menu.h"
#include "player.h"
#include "surface.h"
#include "template.h"
#include "tilemap.h"
#include "wall.h"
#include "ai_copy.h"

namespace Tmpl8
{
    class TileMap;

    class Debug 
    {
        public:
            // Constructor
            Debug(
                AIMap& ai_map,
                Camera& cameraRef,
                CollectibleMap& collectibleRef,
                Collisions& collisionRef,
                Level& levelRef,
                Menu& menuRef,
                Player& playerRef,
                TileMap& tilemapRef,
                WallMap& wallRef
            );

            // Main debug function, press <SPACEBAR> to enable it. 
            // /!\ Every other function can be called only if debug is active.
            void displayDebug(Surface* screen, float deltaTime);

            // Draw functions for hitboxes and lines.
            void drawPlayerHitbox(const vec2& pos, Surface* screen);
            void drawPlayerTileHitbox(const vec2& pos, Surface* screen);
            void drawHitbox(const vec2& pos, Sprite* img, Surface* screen);
            void drawVelocityNorm(Surface* screen);
            void drawDistancePlayerToAI(vec2 ai_pos, float size, Surface* screen);

            // Other functions
            void defaultPos();
            void nextDebugMap();
            void restartCurrentLevel();
            void stopAIs();

		    // Getters / Setters
            int getFPS(float deltaTime);
            void giveDashes();

        private:
            Camera& camera;
            TileMap& tilemap;
            Player& player;
            CollectibleMap& collectible;
            WallMap& wall;
            Level& level;
            Collisions& collisions;
            Menu& menu;
            AIMap& ai_map;
    };
}

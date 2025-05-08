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
                Camera& cameraRef,
                TileMap& tilemapRef,
                Player& playerRef,
                CollectibleMap& collectibleRef,
                WallMap& wallRef,
                AI_Follow& ai_followRef,
                Level& levelRef,
                Collisions& collisionRef,
                Menu& menuRef,
                AI_Patrol& ai_patrolRef,
                AI_Copy& ai_copyRef
            );

            // Variables
            bool gameSlow = false;
            bool isTDown = false;

            // Main debug function
            void displayDebug(Surface* screen, float deltaTime);

            // Draw functions
            void drawPlayerHitbox(const vec2& pos, Surface* screen);
            void drawPlayerTileHitbox(const vec2& pos, Surface* screen);
            void drawHitbox(const vec2& pos, Sprite* img, Surface* screen);
            void drawVelocityNorm(Surface* screen);
            void drawDistancePlayerToAI(vec2 ai_pos, int size, Surface* screen);

            // Other functions
            void defaultPos();
            void nextDebugMap();
            void restartCurrentLevel();
            void stopAIs();

		    // Getters / Setters
            int getFPS(float deltaTime);
            void toggleInfiniteDashes();

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
            AI_Patrol& ai_patrol;
            AI_Copy& ai_copy;
    };
}

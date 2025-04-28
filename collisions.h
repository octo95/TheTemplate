#pragma once
#include "ai_follow.h"
#include "ai_patrol.h"
#include "bell.h"
#include "camera.h"
#include "collectible.h"
#include "gamesound.h"
#include "level.h"
#include "player.h"
#include "tilemap.h"
#include "wall.h"

namespace Tmpl8
{
    extern Sprite img_water_slide;

    class Collisions {
    public:
        // Constructor
        Collisions(
            Player& playerRef,
            TileMap& tilemapRef,
            AI_Follow& ai_followRef,
            CollectibleMap& collectibleRef,
            WallMap& wallRef,
            Level& levelRef,
            Camera& cameraRef,
            GameSound& gamesoundRef,
            Bell& bellRef,
            AI_Patrol& ai_patrolRef
        );

		// Variables
        bool playerHitAI = false;
        bool isOnIce = false;

        // Collision checks
        TileType CheckCollisionBottom(const vec2& pos);
        TileType CheckCollisionTop(const vec2& pos);
        TileType CheckCollisionRight(const vec2& pos);
        TileType CheckCollisionLeft(const vec2& pos);

		// Other functions
        void manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles);
        void applyBouncingPhysics(vec2& new_pos);
        void drawSplash(Surface* screen, vec2 player_pos, float deltaTime);

		// Getters / Setters
        bool getJumpState(vec2& new_pos);
        void setTouchStateFollowAI(bool isTouched) { playerHitAI = isTouched; }

    private:
        Player& player;
        TileMap& tilemap;
        AI_Follow& ai_follow;
        CollectibleMap& collectible;
        WallMap& wall;
        Level& level;
        Camera& camera;
        GameSound& gamesound;
        Bell& bell;
        AI_Patrol& ai_patrol;

        bool canPlayerJump = false;
        float bouncing_force = 1.0f;
        float gravity = 0.5f;
        float wall_force = 2.0f;
        float trigger_fall_light = 2.0f;
        float trigger_fall_normal = 5.0f;
        float trigger_fall_hard = 9.0f;
    };
}

#pragma once
#include "player.h"
#include "tilemap.h"
#include "ai_follow.h"
#include "collectible.h"
#include "wall.h"
#include "level.h"
#include "camera.h"
#include "gamesound.h"
#include "bell.h"

namespace Tmpl8
{
    extern Sprite img_water_slide;

    class Collisions {
    public:
        Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef, WallMap& wallRef, Level& levelRef, Camera& cameraRef, GameSound& gamesoundRef, Bell& bellRef);
        TileType CheckCollisionBottom(const vec2& pos);
        TileType CheckCollisionTop(const vec2& pos);
        TileType CheckCollisionRight(const vec2& pos);
        TileType CheckCollisionLeft(const vec2& pos);
        void manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles);
        bool getJumpState(vec2& new_pos);
        void setTouchStateFollowAI(bool isTouched) { playerHitAI = isTouched; }
        void applyBouncingPhysics(vec2& new_pos);
        void drawSplash(Surface* screen, vec2 player_pos, float deltaTime);
        bool playerHitAI = false;
        bool isOnIce = false;
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

        bool canPlayerJump = false;
        float bouncing_force = 1.0f;
        float gravity = 0.5f;
        float wall_force = 2.0f;
        float trigger_fall_light = 2.0f;
        float trigger_fall_normal = 5.0f;
        float trigger_fall_hard = 9.0f;
    };
}

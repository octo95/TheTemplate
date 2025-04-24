#pragma once
#include "player.h"
#include "tilemap.h"
#include "ai_follow.h"
#include "collectible.h"
#include "wall.h"
#include "level.h"
#include "camera.h"
#include "gamesound.h"

namespace Tmpl8
{
    class Collisions {
    public:
        Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef, WallMap& wallRef, Level& levelRef, Camera& cameraRef, GameSound& gamesoundRef);
        TileType CheckCollisionBottom(const vec2int& pos);
        TileType CheckCollisionTop(const vec2& pos);
        TileType CheckCollisionSides(const vec2& pos);
        void manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles);
        bool getJumpState(vec2& new_pos);
        void setTouchStateFollowAI(bool isTouched) { playerHitAI = isTouched; }
        bool playerHitAI = false;
        void applyBouncingPhysics(vec2& new_pos);
    private:
        Player& player;
        TileMap& tilemap;
        AI_Follow& ai_follow;
        CollectibleMap& collectible;
        WallMap& wall;
        Level& level;
        Camera& camera;
        GameSound& gamesound;

        bool canPlayerJump = false;
        float gravity = 0.5f;
        float friction = 0.05f;
        float wall_force = 7.0f;
    };
}

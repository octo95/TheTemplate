#pragma once
#include "ai_follow.h"
#include "ai_patrol.h"
#include "camera.h"
#include "gamesound.h"
#include "level.h"
#include "player.h"
#include "tilemap.h"
#include "ai_copy.h"
#include "menu.h"

namespace Tmpl8
{
    extern Sprite img_water_slide;

    //enum TouchType {
    //    NoneX,
    //    NoneY,
    //    Damage,
    //    End,
    //    Collision,
    //    Ice
    //};

    class Collisions {
    public:
        // Constructor
        Collisions(
            Player& playerRef,
            TileMap& tilemapRef,
            AI_Follow& ai_followRef,
            Level& levelRef,
            Camera& cameraRef,
            GameSound& gamesoundRef,
            AI_Patrol& ai_patrolRef,
            AI_Copy& ai_copyRef,
            Menu& menuRef
        );

        // Variables
        bool playerHitAI = false;
        bool isOnIce = false;

        // Collision checks
        TileType checkCollisionB(const vec2& pos);
        TileType checkCollisionBottom(const vec2& pos, bool left, bool right);
        TileType checkCollisionT(const vec2& pos);
        TileType checkCollisionTop(const vec2& pos, bool left, bool right);
        TileType checkCollisionR(const vec2& pos);
        TileType checkCollisionRight(const vec2& pos);
        TileType checkCollisionL(const vec2& pos);
        TileType checkCollisionLeft(const vec2& pos);

        // Other functions
        TileType checkCollisionAtOffset(const vec2& pos, const vec2& offset);
        void manageCollisions(vec2& new_pos);
        void drawSplash(Surface* screen, vec2 player_pos, float deltaTime);
        void applyBouncingPhysics(vec2& new_pos, bool left, bool right, bool bottom, bool top);
        void collisionsSFX(bool bottom, bool isIce);

        // Getters / Setters
        bool getJumpState(vec2& new_pos);
        void setTouchStateFollowAI(bool isTouched) { playerHitAI = isTouched; }

    private:
        Player& player;
        TileMap& tilemap;
        AI_Follow& ai_follow;
        Level& level;
        Camera& camera;
        GameSound& gamesound;
        AI_Patrol& ai_patrol;
        AI_Copy& ai_copy;
        Menu& menu;

        bool canPlayerJump = false;
        float bouncing_force = 1.0f;
        float gravity = 0.5f;
        float trigger_fall_light = 2.0f;
        float trigger_fall_normal = 5.0f;
        float trigger_fall_hard = 9.0f;
    };
}
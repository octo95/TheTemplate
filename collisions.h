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
#include "health.h"

namespace Tmpl8
{
    extern Sprite img_water_slide;

    class Collisions {
    public:
        // Constructor
        Collisions(
            AIMap& ai_map,
            Camera& cameraRef,
            GameSound& gamesoundRef,
            Health& healthRef,
            Level& levelRef,
            Menu& menuRef,
            Player& playerRef,
            TileMap& tilemapRef
        );


        // Collision checks
        TileType getTileCollision(const vec2& player_tpos, const vec2& offset);
        TileType checkCollisionB(const vec2& pos, bool left, bool right);
        TileType checkCollisionT(const vec2& pos, bool left, bool right);
        TileType checkCollisionR(const vec2& pos);
        TileType checkCollisionL(const vec2& pos);

        // Other functions
        vec2 getPlayerTPos(const vec2& pos);
        void manageCollisions(vec2& new_pos);
        bool manageAICollisions();
        void applyCollisions(bool isDamage, bool isIce, bool isCollision);
        void drawSplash(Surface* screen, vec2 player_pos, float deltaTime);
        void applyBouncingPhysics(vec2& new_pos, bool left, bool right, bool bottom, bool top);
        void applyCollisionsSFX(bool bottom, bool isIce);

        // Getters / Setters
        bool getJumpState(vec2& new_pos);

    private:
        Player& player;
        TileMap& tilemap;
        Level& level;
        Camera& camera;
        GameSound& gamesound;
        AIMap& ai_map;
        Menu& menu;
        Health& health;

        bool isOnIce = false;
        bool FallNormal = false;
        bool FallHard = false;
        bool canPlayerJump = false;
    };
}
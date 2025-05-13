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
        TileType checkCollisionB(const vec2& pos, bool left, bool right);   // Check what tile the player is touching at the <bottom> of their hitbox.
        TileType checkCollisionT(const vec2& pos, bool left, bool right);   // ..same for the <top>.
        TileType checkCollisionR(const vec2& pos);                          // ..<right>
        TileType checkCollisionL(const vec2& pos);                          // ..<left>
                                                    
        void manageCollisions(vec2& new_pos);                                                       // Gather all the conditions from tile detection and apply them.
        bool manageAICollisions();                                                                  // Gather all the conditions for AI collisions to apply damage.
        void applyCollisions(bool isDamage, bool isIce, bool isCollision);                          // Apply the tile detection logic.
        void applyBouncingPhysics(vec2& new_pos, bool left, bool right, bool bottom, bool top);     // Apply physics to make the player bounce on the ground.
        void drawSplash(Surface* screen, vec2 player_pos, float deltaTime);                         // Draw a splash visual when the player is on ice.
        void applyCollisionsSFX(bool bottom, bool isIce);                                           // Apply some SFX for some collision checks.

        // Getters / Setters
        bool getJumpState(vec2& new_pos);                                           // Determine if the player can jump if touching the ground.
        vec2 getPlayerTPos(const vec2& pos);                                        // Gives the coordinates of what tile the player is in, also called as its tile coordinates.
        TileType getTileCollision(const vec2& player_tpos, const vec2& offset);     // Get the type of the tile the player is touching at a given offset.

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
    };
}
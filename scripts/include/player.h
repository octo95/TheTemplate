#pragma once
#include "camera.h"
#include "collectible.h"
#include "surface.h"
#include "tilemap.h"
#include <unordered_map>

namespace Tmpl8
{
    extern Sprite img_player;
   
    class TileMap;
    class Collisions;

    class Player 
    {
        public:

            // Constructor
            Player(
                Camera& cameraRef
            );

		    // Variables
            vec2 velocity = { 0, 0 };
            vec2 position = { 0, 0 };
            vec2 default_pos = { 0, 0 };

            // Physics
            const float GRAVITY = 0.10f;               // Gravity for vertical force.
            const float ENERGY_LOSS = 0.7f;            // Energy retained after bounce (in %).
            float friction = 0.05f;                    // Ground friction, lower for more momentum.
            float max_horizontal_speed = 2.5f;         // Max velocity.x.
            float max_vertical_speed = 25.0f;          // Max velocity.y.

            // Hitbox & Image Dimensions
            float hitbox_tolerance = 2.0f;
            float hitbox_radius = 16.0f - hitbox_tolerance;
            float player_img_width = img_player.GetWidth();
            float player_img_height = img_player.GetHeight();

            // Player State
            bool can_jump = false;
            bool jumping = false;
            bool dashing = false;
            int dash_count = 0;
            float angular_acceleration = 0.0f;

            // Cooldowns
            float move_cooldown = 0.0f;
            float jumping_cooldown = 0.0f;
            float dashing_cooldown = 0.0f;

            // Functions
            vec2 movePlayer(Collisions* collisions, float deltaTime);
            vec2 camFollowPlayer(TileMap* map);
            void restrictPlayerInMap(TileMap* tilemap);
            void applyGravity(float deltaTime);
            void manageJump(float deltaTime);
            void manageDash(float deltaTime);

		    // Getters / Setters
            void getPlayerPos(vec2& pos) { pos = position; }
            void setPlayerPos(const vec2& pos) { position = pos; }
            void setJumpState(bool canJump) { can_jump = canJump; }
            void setPlayerDefaultPos(const vec2& pos) { default_pos = pos; }
            void getPlayerDefaultPos(vec2& pos) { pos = default_pos; }
            void resetPlayerVelocity() { velocity = { 0.0f, 0.0f }; }

        private:
            Camera& camera;
            bool is_touched_follow_ai = false;
            float vertical_speed = 0.0f;
            float horizontal_speed = 0.0f;
            const float ACCELERATION = 0.05f;

    };
}

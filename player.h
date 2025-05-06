#pragma once
#include "camera.h"
#include "collectible.h"
#include "surface.h"
#include "tilemap.h"
#include <unordered_map>

namespace Tmpl8
{
    extern Sprite img_player;
    extern int hitbox_radius;
    extern int player_img_width;
    extern int player_img_height;
   
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

            bool can_jump = false;
            bool is_hurt = false;
            float move_cooldown = 0.0f;
            bool jumping = false;
            float jumping_cooldown = 0.0f;
            float angular_acceleration = 0.0f;
            float gravity = 0.10f;
		    float friction = 0.05f;                     // Friction on the ground, lower friction results in more momentum
		    float max_horizontal_speed = 1.5f;          // Max horizontal speed
		    float max_vertical_speed = 10.0f;           // Max vertical speed
            const float ENERGY_LOSS = 0.7f;             // How much energy the ball keeps after a bounce in %
		    const float PLAYER_DRAW_OFFSET_Y = -4.0f;   // Offset for the player sprite (since it has a reduced hitbox, to put it back on the ground)

            // Functions
            vec2 movePlayer(Collisions* collisions, float deltaTime);
            vec2 camFollowPlayer(TileMap* map);
            void dash();

		    // Getters / Setters
            void getPlayerPos(vec2& pos) { pos = position; }
            void setPlayerPos(const vec2& pos) { position = pos; }
            void setJumpState(bool canJump) { can_jump = canJump; }
            void setPlayerDefaultPos(const vec2& pos) { default_pos = pos; }
            void getPlayerDefaultPos(vec2& pos) { pos = default_pos; }
            void resetPlayerVelocity() { velocity = { 0, 0 }; }

        private:
            Camera& camera;
            bool is_touched_follow_ai = false;
            float vertical_speed = 0.0f;
            float horizontal_speed = 0.0f;
            const float ACCELERATION = 0.05f;

    };
}

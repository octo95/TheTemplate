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

            float angular_acceleration = 0.0f;
            float gravity = 0.28f;
		    float friction = 0.05f;                     // Friction on the ground, lower friction results in more momentum
            const float ENERGY_LOSS = 0.9f;             // How much energy the ball keeps after a bounce in %
		    const float MAX_HORIZONTAL_SPEED = 3.0f;    // Max horizontal speed
		    const float MAX_VERTICAL_SPEED = 10.0f;     // Max vertical speed
		    const float PLAYER_DRAW_OFFSET_Y = -4.0f;   // Offset for the player sprite (since it has a reduced hitbox, to put it back on the ground)

            // Functions
            void movePlayer(vec2& new_pos, Collisions* collisions, float deltaTime);
            vec2 camFollowPlayer(TileMap* map);

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
            float wall_force = 7.0f;
            const float ACCELERATION = 0.3f;
    };
}

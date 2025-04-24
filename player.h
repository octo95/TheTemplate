#pragma once
#include "surface.h"
#include "tilemap.h"
#include "collectible.h"
#include <unordered_map>
#include "camera.h"

namespace Tmpl8
{
    extern Sprite player_img;
    extern int hitbox_radius;
    extern int player_img_width;
    extern int player_img_height;

    class TileMap;

    class Collisions;

    class Player {
    public:
        Player(Camera& cameraRef);
        vec2 velocity = { 0, 0 };
        vec2 position = { 0, 0 };
        vec2 default_pos = { 0, 0 };
        const float ENERGY_LOSS = 0.7f;
        const float MAX_HORIZONTAL_SPEED = 3.0f;
        const float MAX_VERTICAL_SPEED = 10.0f;

        void movePlayer(vec2& new_pos, Collisions* collisions);
        vec2 camFollowPlayer();

        void setPlayerDefaultPos(const vec2& pos) { default_pos = pos; }
        void getPlayerDefaultPos(vec2& pos) { pos = default_pos; }
        void getPlayerPos(vec2& pos) { pos = position; }
        void setPlayerPos(const vec2& pos) { position = pos; }
        void setJumpState(bool canJump) { can_jump = canJump; }

    private:
        Camera& camera;
        bool is_touched_follow_ai = false;
        bool can_jump = false;
        float gravity = 0.28f;
        float vertical_speed = 0;
        float horizontal_speed = 0;
        float friction = 0.05f;
        float wall_force = 7.0f;
        float rotation_speed = 90.0f;
        const float ACCELERATION = 0.3f;
    };
}

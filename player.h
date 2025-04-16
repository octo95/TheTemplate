#pragma once
#include "surface.h"
#include "tilemap.h"
#include "template.h"

namespace Tmpl8
{
    // Extern variables
    extern Sprite player_img;
    extern int hitbox_size;
    extern int px;
    extern int py;
    extern int rotation;
    extern int player_img_width;
    extern int player_img_height;
    extern int gravity;
    extern float vertical_speed;
    extern float horizontal_speed;
    extern int spawn_px ;
    extern int spawn_py;
    extern float friction;                      // How much the player sticks to the ground

    // Constants
    const float ACCELERATION = 0.3f;            // How long it will take the player to reach the max horizontal speed.
    const float MAX_HORIZONTAL_SPEED = 3.0f;    // The max horizontal speed.            

    // Player class
    class Player {
    public:
        TileType Player::CheckCollisionBottom(int x, int y);
        TileType Player::CheckCollisionSides(int x, int y);
        void movePlayer(int& x, int& y);
        bool manageCollisions(int& nx, int& ny, Surface* screen);
        void getPlayerPos(int& x, int& y);
        void setPlayerPos(int x, int y);
        void setMapDefaultPos();
        vec2 camFollowPlayer();
    };
};
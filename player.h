#pragma once
#include "surface.h"
#include "tilemap.h"

namespace Tmpl8
{
    // Extern variables
    extern Sprite player_img;
    extern int hitbox_size;
    extern int px;
    extern int py;
    extern int player_img_width;
    extern int player_img_height;
    extern int gravity;
    extern int vertical_speed;
    extern float horizontal_speed;
    extern int spawn_px ;
    extern int spawn_py;

    // Constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 512;
    const float ACCELERATION = 0.3f;            // How long it will take the player to reach the max horizontal speed.
    const float MAX_HORIZONTAL_SPEED = 3.0f;    // The max horizontal speed.
    const float FRICTION = 0.05f;               // How much the player sticks to the ground

    // Player class
    class Player {
    public:
        TileType Player::CheckCollisionBottom(int x, int y);
        TileType Player::CheckCollisionSides(int x, int y);
        void movePlayer(int& x, int& y);
        void manageCollisions(int& nx, int& ny, Surface* screen);
        int getPlayerPos();
        void setPlayerPos(int& x, int& y);
        void setMapDefaultPos();
    };
};
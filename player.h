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
    extern int spawn_px ;
    extern int spawn_py;
                 
    // Player class
    class TileMap;

    class Player {
    public:
        void setMap(TileMap* tilemap) { map = tilemap; }
        TileType Player::CheckCollisionBottom(int x, int y);
        TileType Player::CheckCollisionSides(int x, int y);
        void movePlayer(int& x, int& y);
        bool manageCollisions(int& nx, int& ny, Surface* screen);
        void getPlayerPos(int& x, int& y);
        void setPlayerPos(int x, int y);
        void setPlayerDefaultPos();
        vec2 camFollowPlayer();
    private:
        TileMap* map;
        int rotation = 0;
        int gravity = 3;
        float vertical_speed = 0;
        float horizontal_speed = 0;
        float friction = 0.05f;                     // How much the player sticks to the ground
        const float ACCELERATION = 0.3f;            // How long it will take the player to reach the max horizontal speed.
        const float MAX_HORIZONTAL_SPEED = 3.0f;    // The max horizontal speed.     
    };
};
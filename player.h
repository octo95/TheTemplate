#pragma once
#include "surface.h"
#include "tilemap.h"

namespace Tmpl8
{
    // Extern variables
    extern Sprite player_img;
    extern TileMap map;
    extern int hitbox_size;
    extern int px;
    extern int py;
    extern int player_img_width;
    extern int player_img_height;

    // Constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 512;
    const int DEFAULT_PX = 400;
    const int DEFAULT_PY = 10;

    // Player class
    class Player {
    public:
        TileType CheckCollision(int x, int y, Surface* screen);
        void movePlayer(int& x, int& y, int player_speed);
        void manageCollisions(int& nx, int& ny, Surface* screen);
    };
};
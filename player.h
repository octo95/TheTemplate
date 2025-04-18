#pragma once
#include "surface.h"
#include "tilemap.h"

namespace Tmpl8
{
    extern Sprite player_img;
    extern int hitbox_size;
    extern int player_img_width;
    extern int player_img_height;

    class TileMap;

    class Player {
    public:
        void setMap(TileMap* tilemap) { map = tilemap; }
        TileType CheckCollisionBottom(const vec2& pos);
        TileType CheckCollisionSides(const vec2& pos);
        void movePlayer(vec2& new_pos);
        bool manageCollisions(vec2& new_pos, Surface* screen);
        void getPlayerPos(vec2& pos);
        void setPlayerPos(const vec2& pos);
        void setPlayerDefaultPos(const vec2& pos);
        void getPlayerDefaultPos(vec2& pos);
        vec2 camFollowPlayer();
    private:
        TileMap* map;
        vec2 position = { 400, 10 };
        vec2 default_pos = { 400, 10 };
        int rotation = 0;
        int gravity = 3;
        float vertical_speed = 0;
        float horizontal_speed = 0;
        float friction = 0.05f;
        const float ACCELERATION = 0.3f;
        const float MAX_HORIZONTAL_SPEED = 3.0f;
    };
}

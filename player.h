#pragma once
#include "surface.h"
#include "tilemap.h"
#include "collectible.h"
#include <unordered_map>

namespace Tmpl8
{
    extern Sprite player_img;
    extern int hitbox_size;
    extern int player_img_width;
    extern int player_img_height;

    class TileMap;

    class Player {
    public:
        Player(TileMap& tmap);
        vec2 velocity = { 0, 0 };
        vec2 position = { 400, 10 };
        vec2 default_pos = { 400, 10 };

        TileType CheckCollisionBottom(const vec2& pos);
        TileType CheckCollisionSides(const vec2& pos);
        void movePlayer(vec2& new_pos);
        bool manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles);
        void getPlayerPos(vec2& pos);
        void setPlayerPos(const vec2& pos);
        void setPlayerDefaultPos(const vec2& pos);
        void getPlayerDefaultPos(vec2& pos);
        vec2 camFollowPlayer();
    private:
        TileMap& map;
        int rotation = 0;
        int gravity = 3;
        float vertical_speed = 0;
        float horizontal_speed = 0;
        float friction = 0.05f;
        const float ENERGY_LOSS = 0.15f;
        const float ACCELERATION = 0.3f;
        const float MAX_HORIZONTAL_SPEED = 3.0f;
    };
}

#pragma once
#include "player.h"
#include "tilemap.h"
#include "ai_follow.h"

namespace Tmpl8
{
    class Collisions {
    public:
        Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef);
        TileType CheckCollisionBottom(const vec2& pos);
        TileType CheckCollisionSides(const vec2& pos);
        bool manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles);
    private:
        Player& player;
        TileMap& tilemap;
        AI_Follow& ai_follow;

        bool is_touched_follow_ai = false;
        float gravity = 0.5f;
        float friction = 0.05f;
        float wall_force = 7.0f;
    };
}

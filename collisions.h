#pragma once
#include "player.h"
#include "tilemap.h"
#include "ai_follow.h"

namespace Tmpl8
{
    class Collisions {
    public:
        Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef);

    private:
        Player& player;
        TileMap& tilemap;
        AI_Follow& ai_follow;
    };
}

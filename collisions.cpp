#include "collisions.h"

namespace Tmpl8
{
    Collisions::Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef) :
        player(playerRef),
        tilemap(tilemapRef),
        ai_follow(ai_followRef)
    {}
}


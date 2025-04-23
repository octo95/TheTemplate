#pragma once
#include "tilemap.h"
#include "player.h"
#include "ai_follow.h"
#include "collectible.h"
#include "wall.h"

namespace Tmpl8
{
    class Level {
    public:
        const vec2 AI_FOLLOW_DEFAULT_POS[3] =
        {
            vec2 {100,500},
            vec2 {100,300},
            vec2 {0,0}
        };

        const vec2 PLAYER_DEFAULT_POS[3] =
        {
            vec2 {300,10},
            vec2 {500,10},
            vec2 {600,10}
        };
        bool level_finished = false;

        Level(TileMap& tilemapRef, Player& playerRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef, WallMap& wallRef);
        void loadLevel(int i);
        void manageDefaultPos(int map_index);
    private:
        TileMap& tilemap;
        Player& player;
        AI_Follow& ai_follow;
        CollectibleMap& collectible;
        WallMap& wall;


    };
}

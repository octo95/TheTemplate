#pragma once
#include "tilemap.h"
#include "player.h"
#include "ai_follow.h"
#include "collectible.h"
#include "wall.h"
#include "gamesound.h"
#include "bell.h"
#include "ai_patrol.h"
#include "ai_copy.h"

namespace Tmpl8
{
    class Level 
    {
        public:
            // Constructor
            Level(
                TileMap& tilemapRef,
                Player& playerRef,
                AI_Follow& ai_followRef,
                CollectibleMap& collectibleRef,
                WallMap& wallRef,
                GameSound& gamesoundRef,
                Bell& bellRef,
                AI_Patrol& ai_patrolRef,
                AI_Copy& ai_copyRef
            );

			// Default positions for the player and AIs
            const vec2 AI_FOLLOW_DEFAULT_POS[5] =
            {
                vec2 {100,500},
                vec2 {100,300},
                vec2 {0,0},
                vec2 {0,0},
                vec2 {500,250}
            };
            const vec2 AI_PATROL_DEFAULT_POS[5] =
            {
                vec2 {660,224},
                vec2 {100,300},
                vec2 {0,0},
                vec2 {0,0},
                vec2 {500,250}
            };
            const vec2 PLAYER_DEFAULT_POS[5] =
            {
                vec2 {300,10},
                vec2 {500,10},
                vec2 {600,10},
                vec2 {600,30},
                vec2 {100,10}
            };

			// Boolean variables
            bool level_finished = false;
            bool game_finished = false;
            
			// Functions
            void loadLevel(int i);
            void manageDefaultPos(int map_index);

        private:
            TileMap& tilemap;
            Player& player;
            AI_Follow& ai_follow;
            CollectibleMap& collectible;
            WallMap& wall;
            GameSound& gamesound;
            Bell& bell;
            AI_Patrol& ai_patrol;
            AI_Copy& ai_copy;
    };
}

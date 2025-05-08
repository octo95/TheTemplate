#pragma once
#include "tilemap.h"
#include "player.h"
#include "ai_follow.h"
#include "collectible.h"
#include "wall.h"
#include "gamesound.h"
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
                AI_Patrol& ai_patrolRef,
                AI_Copy& ai_copyRef
            );

            const vec2 OFF_SCREEN = vec2{ -500, -500 };

			// Default positions for the player and AIs
            const vec2 AI_FOLLOW_DEFAULT_POS[5] =
            {
                OFF_SCREEN,
                OFF_SCREEN,
                vec2 {-2*32,13*32}, // Show on level 3, appear offscreen at first
                OFF_SCREEN,
                vec2 {3 * 32,6 * 32}
            };
            const vec2 AI_PATROL_DEFAULT_POS[5] =
            {
                OFF_SCREEN,
                vec2 {13*32,8*32}, // Show on level 2
                OFF_SCREEN,
                OFF_SCREEN,
                vec2 {5 * 32,40 * 32}
            };
            const vec2 PLAYER_DEFAULT_POS[5] =
            {
                vec2 {5*32,0*32},
                vec2 {4*32,2*32},
                vec2 {9*32,13*32},
                vec2 {300,30},
                vec2 {100,10}
            };

			// Boolean variables
            bool level_finished = false;
            bool game_finished = false;
            
			// Functions
            void loadLevel(int i);
            void nextLevel();
            void manageDefaultPos(int map_index);
            void manageAIsPerMap(int map_index);

        private:
            TileMap& tilemap;
            Player& player;
            AI_Follow& ai_follow;
            CollectibleMap& collectible;
            WallMap& wall;
            GameSound& gamesound;
            AI_Patrol& ai_patrol;
            AI_Copy& ai_copy;
    };
}

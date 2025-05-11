#pragma once
#include "tilemap.h"
#include "player.h"
#include "collectible.h"
#include "wall.h"
#include "gamesound.h"
#include "ai.h"
#include "ai_copy.h"
#include "ai_follow.h"
#include "ai_patrol.h"
#include "camera.h"
#include "cloud.h"

namespace Tmpl8
{
    class Level 
    {
        public:
            // Constructor
            Level(
                AIMap& ai_mapRef,
                Camera& cameraRef,
                CloudMap& cloudRef,
                CollectibleMap& collectibleRef,
                GameSound& gamesoundRef,
                Player& playerRef,
                TileMap& tilemapRef,
                WallMap& wallRef
            );


            const vec2 OFF_SCREEN = vec2{ -500, -500 };

			// Default positions for the player and AIs
            const vec2 AI_FOLLOW_SPAWN_POS[2] =
            {
                vec2 {-5,13},   // LVL3
                vec2 {33,25}    // LVL5
            };
            const vec2 AI_PATROL_SPAWN_POS[5] =
            {
                vec2 {13,8},    // LVL2 (top)
                vec2 {13,29},   // LVL2 (bottom)
                vec2 {36,5},    // LVL5 (path bottom)
                vec2 {31,36},   // LVL5 (path right)
                vec2 {16,7}     // (test)
            };
            const vec2 PLAYER_DEFAULT_POS[5] =
            {
                vec2 {5*32,0*32},
                vec2 {4*32,2*32},
                vec2 {9*32,13*32},
                vec2 {39*32,0*2},
                vec2 {2*32,0*32}
            };

			// Boolean variables
            bool level_finished = false;
            bool game_finished = false;
            
			// Functions
            void loadLevel(int i);
            void nextLevel();
            void manageDefaultPos(int map_index);
            void manageAIsPerMap(int map_index);

            void addAiCopy(AIMap* ai_map, float timer);
            void addAiFollow(AIMap* ai_map, vec2 spawn_pos);
            void addAiPatrol(AIMap* ai_map, vec2 spawn_pos);

        private:
            TileMap& tilemap;
            Player& player;
            CollectibleMap& collectible;
            WallMap& wall;
            GameSound& gamesound;
            AIMap& ai_map;
            Camera& camera;
            CloudMap& cloud;
    };
}

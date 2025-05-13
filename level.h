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

			// Default positions for the player and AIs. 
            // The AI Copy doesn't need a default pos as it follows the player anyways.

            const vec2 AI_FOLLOW_SPAWN_POS[2] =
            {
                vec2 {-5,13},   // LVL3
                vec2 {33,25}    // LVL5
            };
            const vec2 AI_PATROL_SPAWN_POS[4] =
            {
                vec2 {13,8},    // LVL2 (top)
                vec2 {13,29},   // LVL2 (bottom)
                vec2 {36,5},    // LVL5 (path bottom)
                vec2 {31,36}    // LVL5 (path right)
            };
            const vec2 PLAYER_DEFAULT_POS[5] =
            {
                vec2 {5*32,0*32},   //LVL1
                vec2 {4*32,2*32},   //LVL2
                vec2 {9*32,13*32},  //LVL3
                vec2 {39*32,0*2},   //LVL4
                vec2 {2*32,0*32}    //LVL5
            };

			// Boolean variables
            bool level_finished = false;
            bool game_finished = false;
            
			// Functions
            void loadLevel(int i);                  // Loads a given level logic.
            void nextLevel();                       // Handles the level incrementation logic.
            void manageDefaultPos(int map_index);   // Handles the player's spawn position logic.
            void manageAIsPerMap(int map_index);    // Handles where to put to put the AIs for a given level index.

            void addAiCopy(AIMap* ai_map, float timer);         // Helper function to add an AI Copy.
            void addAiFollow(AIMap* ai_map, vec2 spawn_pos);    // ... to add an AI Follow.
            void addAiPatrol(AIMap* ai_map, vec2 spawn_pos);    // ... to add an AI Patrol.

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

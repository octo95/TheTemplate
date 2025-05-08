#pragma once
#include "surface.h"
#include "tile.h"
#include "player.h"
#include <unordered_map>

namespace Tmpl8
{
    const int TOTAL_MAPS = 3;
    const int TILE_ROWS = 32;
    const int TILE_COLUMNS = 27;
    const int MAP_AMOUNT = 5;

    extern Sprite img_map1_data_read;

    // Jump collectibles
    const vec2 MAP1_COLLEC_JUMP[1] = {
        vec2 {10,12}
    };
    const vec2 MAP2_COLLEC_JUMP[2] = {
        vec2 {12,15},
        vec2 {12,29}
    };
    const vec2 MAP3_COLLEC_JUMP[4] = {
        vec2 {19,3},
        vec2 {29,4}
    };
    const vec2 MAP4_COLLEC_JUMP[4] = {
        vec2 {3,2},
        vec2 {11,9},
        vec2 {9,11},
        vec2 {12,1}
    };
    const vec2 MAP5_COLLEC_JUMP[4] = {
        vec2 {3,2},
        vec2 {11,9},
        vec2 {9,11},
        vec2 {12,1}
    };

    // Health collectibles
    const vec2 MAP1_COLLEC_HEALTH[1] = {
        vec2 {22,7}
    };
    const vec2 MAP2_COLLEC_HEALTH[1] = {
        vec2 {2,29}
    };
    const vec2 MAP3_COLLEC_HEALTH[1] = {
        vec2 {5,2}
    };
    const vec2 MAP4_COLLEC_HEALTH[1] = {
        vec2 {0,0}
    };
    const vec2 MAP5_COLLEC_HEALTH[1] = {
        vec2 {0,0}
    };
  

    // Walls
    const vec2 MAP1_WALLS[1] = {
        vec2 {21,7}
    };
    const vec2 MAP2_WALLS[2] = {
        vec2 {8,2},
        vec2 {4,29}
    };
    const vec2 MAP3_WALLS[7] = {
        vec2 {8,3},
        vec2 {22,3},
        vec2 {22,2},
        vec2 {22,1},
        vec2 {22,0},
        vec2 {41,14},
        vec2 {46,14}
    };
    const vec2 MAP4_WALLS[4] = {
        vec2 {5,7},
        vec2 {1,1},
        vec2 {3,3},
        vec2 {5,4}
    };
    const vec2 MAP5_WALLS[4] = {
        vec2 {5,7},
        vec2 {1,1},
        vec2 {3,3},
        vec2 {5,4}
    };

    class Player;

    class TileMap 
    {
        public:
			// Constructor
            TileMap(
                Player& playerRef
            );

			// Variables
            std::unordered_map<vec2, TileType> map_collision;
            Sprite* current_map_data_read;
            Sprite* current_map_draw;

            // 
            const char (*current_map)[TILE_COLUMNS * 3];
            int current_level = 1;

            // Functions
            void readImageToMap(Sprite* image);


            void loadLevel(int i);

            int incrementMapIndex() { return current_level = current_level % MAP_AMOUNT + 1; }

			// Getters / Setters
            void loadMap(int index);
            int getCurrentLevel() const { return (current_level - 1) % MAP_AMOUNT + 1; }

        private:
            Player& player;
    };
};


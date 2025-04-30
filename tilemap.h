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

    const vec2 MAP1_COLLECTIBLES[10] = {
        vec2 {3,4},
        vec2 {13,5},
        vec2 {19,6},
        vec2 {6,12},
        vec2 {7,11},
        vec2 {8,11},
        vec2 {24,1},
        vec2 {10,11},
        vec2 {11,11},
        vec2 {12,21}
    };
    const vec2 MAP1_WALLS[2] = {
        vec2 {22,1},
        vec2 {8,18}
    };
    
    // MAP2
    const vec2 MAP2_COLLECTIBLES[2] = {
        vec2 {3,2},
        vec2 {12,1}
    };
    const vec2 MAP2_WALLS[2] = {
        vec2 {5,7},
        vec2 {1,4}
    };

    // MAP3
    const vec2 MAP3_COLLECTIBLES[4] = {
        vec2 {3,2},
        vec2 {11,9},
        vec2 {9,11},
        vec2 {12,1}
    };
    const vec2 MAP3_WALLS[4] = {
        vec2 {5,7},
        vec2 {1,1},
        vec2 {3,3},
        vec2 {5,4}
    };

    // MAP4
    const vec2 MAP4_COLLECTIBLES[4] = {
        vec2 {3,2},
        vec2 {11,9},
        vec2 {9,11},
        vec2 {12,1}
    };
    const vec2 MAP4_WALLS[4] = {
        vec2 {5,7},
        vec2 {1,1},
        vec2 {3,3},
        vec2 {5,4}
    };

    // MAP5
    const vec2 MAP5_COLLECTIBLES[4] = {
        vec2 {3,2},
        vec2 {11,9},
        vec2 {9,11},
        vec2 {12,1}
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


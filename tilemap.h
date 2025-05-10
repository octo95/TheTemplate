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
    const vec2 MAP1_COLLEC_DASH[1] = {
        vec2 {10,12}
    };
    const vec2 MAP2_COLLEC_DASH[2] = {
        vec2 {12,15},
        vec2 {12,29}
    };
    const vec2 MAP3_COLLEC_DASH[4] = {
        vec2 {19,3},
        vec2 {29,4}
    };
    const vec2 MAP4_COLLEC_DASH[10] = {
        vec2 {30,7},
        vec2 {23,6},
        vec2 {18,7},
        vec2 {17,7},
        vec2 {12,6},
        vec2 {2,15},
        vec2 {10,14},
        vec2 {26,12},
        vec2 {9,25},
        vec2 {32,25}
    };
    const vec2 MAP5_COLLEC_DASH[13] = {
        vec2 {2,5},
        vec2 {15,5},
        vec2 {23,5},
        vec2 {30,4},
        vec2 {43,4},
        vec2 {53,5},
        vec2 {58,11},
        vec2 {59,20},
        vec2 {60,20},
        vec2 {61,20},
        vec2 {62,20},
        vec2 {12,35},
        vec2 {17,35}
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
        vec2 {4,20}
    };
    const vec2 MAP5_COLLEC_HEALTH[2] = {
        vec2 {30,24},
        vec2 {46,18}
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
    const vec2 MAP4_WALLS[8] = {
        vec2 {36,17},
        vec2 {6,29},
        vec2 {6,28},
        vec2 {56,35},
        vec2 {53,31},
        vec2 {53,30},
        vec2 {13,29},
        vec2 {13,30}
    };
    const vec2 MAP5_WALLS[7] = {
        vec2 {47,36},
        vec2 {47,35},
        vec2 {56,36},
        vec2 {56,35},
        vec2 {57,31},
        vec2 {57,30},
        vec2 {50,18}
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
            Sprite* current_map_draw_bg;

            // 
            const char (*current_map)[TILE_COLUMNS * 3];
            int current_level = 1;

            // Functions
            void readImageToMap(Sprite* image);
            void loadLevel(int i);
            //void drawClouds(Surface* screen, Camera* camera, float deltaTime);
            int incrementMapIndex() { return current_level = current_level % MAP_AMOUNT + 1; }

			// Getters / Setters
            void loadMap(int index);
            int getCurrentLevel() const { return (current_level - 1) % MAP_AMOUNT + 1; }

        private:
            Player& player;
    };
};


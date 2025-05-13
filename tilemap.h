#pragma once
#include "surface.h"
#include "player.h"
#include "vec2_hash.h"
#include <unordered_map>

namespace Tmpl8
{
    // The game contains 5 levels.
    const int MAP_AMOUNT = 5;

    extern Sprite img_map1_data_read;
    extern Sprite img_map1_draw;
    extern Sprite img_map1_draw_bg;
    extern Sprite img_map5_draw_alt;

    // The game is drawn with tiles, each tile having a size of 32 pixels.
    const float TILE_SIZE = 32.0f;

    // The game contains multiple tiles that will affect the player differently:
    /*---------------------------------------------------------------------------
    * - None:       Basically air, can go through it.
    * - Damage:     Lava that hits the player if they enter it by more than half from the bottom.
    * - End:        (unused)
    * - Collision:  Walls the player can't go through. In collision logic however we often use rather !None in case we want the logic to apply to the other types.
    * - Ice:        Similar to the collision but makes the player slide on it. 
    */
    enum TileType
    {
        None = 0,
        Damage = 1,
        End = 2,
        Collision = 3,
        Ice = 4
    };

    extern Sprite img_map1_data_read;

    // Place the dash collectibles in tile coordinates for every map.
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
    const vec2 MAP5_COLLEC_DASH[17] = {
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
        vec2 {17,35},
    };

    // Place the health collectibles in tile coordinates for every map.
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
  
    // Place the walls in tile coordinates for every map.
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
            TileMap(Player& player) : player(player) {}

			// Variables
            std::unordered_map<vec2, TileType> map_collision;

            // Initialize by default the maps on map1
            Sprite* current_map_data_read = &img_map1_data_read;
            Sprite* current_map_draw = &img_map1_draw;
            Sprite* current_map_draw_bg = &img_map1_draw_bg;

            int current_level = 1;          // Sets the map_index.
            bool secret_collected = false;  // Handles the detection of the secret room of level 5.

            // We hold and read the collision data for each map in pictures that are easy to read with basic colors.
            void readImageToMap(Sprite* image);

            // Helper function to increment the map index and wrap around when reaching the total amount back to the first one instead of going out of scope.
            int incrementMapIndex() { return current_level = current_level % MAP_AMOUNT + 1; }

			// Getters / Setters
            void loadMap(int index);
            int getCurrentLevel() const { return (current_level - 1) % MAP_AMOUNT + 1; }

        private:
            Player& player;
    };
};


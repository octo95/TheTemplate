#pragma once
#include "surface.h"
#include "tile.h"
#include "player.h"


namespace Tmpl8
{
    const int TOTAL_MAPS = 3;
    const int TILE_ROWS = 32;
    const int TILE_COLUMNS = 27;
    const int MAP_AMOUNT = 5;

    // MAP1
    const char MAP1[TILE_ROWS][TILE_COLUMNS * 3] = {
    "ca ca da da da da da da da da da da da da da da da da da da da da ca ca ca ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca ca ca ca",
    "ca da da da da da da da da da da da ca ca da da da da da da da da da da da ca ca",
    "ca da da da da da da da da da da da da ca da da da da da da da da da da da ca ca",
    "ca ba ca ca ca ca ca da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca ca ca ca ca ca da da ca ca ca ca ca ca ca ca ca da da da da da da da ca ca",
    "ca ca ca ca ca ca ca da da da da da da da da da da da da ca ca ca ca da da ca ca",
    "ca ca ca ca ca ca ca da da da da da da da da da da da da ca ca ca ca da da ca ca",
    "ca ca ca ca ca ca ca da da da da da da da da da da da da ca ca ca ca da da ca ca",
    "ca ca ca ca ca ca ca da da da da da da da da da da da da ca ca ca ca da da ca ca",
    "ca ca ca ca ca ca ca aa aa aa aa aa aa aa aa aa aa aa aa ca ca ca ca da da ca ca",
    "ca ca ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da ca ca",
    "ca ca ca da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca",
    "ca ca ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca",
    "ca ca da da da da da ca ca ca da da da ca ca da da da da ca ca ca da da da ca ca",
    "ca ca da da da da da ca ca da da da da da ca da da da da da ca da da da da ca ca",
    "ca ca da da da da da da ca da da da da da da da da da da da da da da da da ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca da da da da ea ea ea ea ea ea ea ea ea ea ea ea ea ea ca ca ca ca da ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca aa aa ca ca ca ca ca da da da da ca ca ca ca ca ca ca ca ca ca ca da ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da da ca ca",
    "ca ca aa ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da da da ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ba ba ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca"
    };
    const vec2 MAP1_COLLECTIBLES[10] = {
        vec2 {3,4},
        vec2 {4,11},
        vec2 {5,8},
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
    const char MAP2[TILE_ROWS][TILE_COLUMNS * 3] = {
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da ca ca ca ca da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da ca da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da ca da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da ca da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da ca ea ea ea da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da ca ca da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da ca da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da ea da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da aa da da da aa da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da ca da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da aa da da da aa da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca ca ba ba ca ca aa ca ca ca ca ca ba ba ca ca ca ca ca ca aa ca ca ba ba ca ca"
    };
    const vec2 MAP2_COLLECTIBLES[2] = {
        vec2 {3,2},
        vec2 {12,1}
    };
    const vec2 MAP2_WALLS[2] = {
        vec2 {5,7},
        vec2 {1,4}
    };

    // MAP3
    const char MAP3[TILE_ROWS][TILE_COLUMNS * 3] = {
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca",
    "ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca",
    "ca da da da da da da da da da da da da ca da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da ca da da da da da da da da da da da da ca",
    "ca ca ca ca ca ca ca ca ca da da da ca ca ca da da da ca ca ca ca ca ca ca ca ca",
    "ca ca ca ca ca ca ca ca ca da da da ca ca ca da da da ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da ea ea ea ea ea ea ea ea ea ea ea ea ea ea ea da da da ca ca ca",
    "ca ca ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca aa aa da da ca ca ca ca da da da da da ca ca ca ca ca ca aa aa ca ca ca",
    "ca ca ca ca ca da da ca ca ca ca da da da da da ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da da ca ca ca ca da da da da da ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca aa aa da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da ca da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da ca ca ca ca ca da da da da da ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca ca da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca ca ca da da aa ca ca ca da da da da da ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca ca"
    };
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
    const char MAP4[TILE_ROWS][TILE_COLUMNS * 3] = {
    "ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca",
    "ca da da ca da da da da da da da da da da da da da da da da da da ca da da da ca",
    "ca da da ca da da da da da da da da da da da da da da da da da da ca da da da ca",
    "ca ba ba ca ca ca ca ca ca ca ca ca da da da ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca ca ca ca ca ca ca da ca ca ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da ea ea ea ea ea ea ea ea ea ea ea ea ea ea ea ea ea ea ea da da da da ca",
    "ca da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca ca ca aa aa ca da da da ca ca da da da da ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca ca ca ca da da da ca ca da da da da ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da ca",
    "ca da ca ca ca ca ca ca ca da da da da da da ca ca ca ca ca ca ca ca da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca ca ca aa aa ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da ca",
    "ca ca ca ca ca ca ca ca ca da da da da da da ca ca ca ca ca ca ca ca da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da ca",
    "ca da aa aa ca ca da da da da da da da da da ca ca ca ca ca ca ca ca ca aa aa ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca ca"
    };
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
    const char MAP5[TILE_ROWS][TILE_COLUMNS * 3] = {
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca",
    "ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca",
    "ca da da da da da da da da da da da da ca da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da ca da da da da da da da da da da da da ca",
    "ca ba ba ca ca ca ca ca ca da da da ca ca ca da da da ca ca ca ca ca ca ca ca ca",
    "ca ca ca ca ca ca ca ca ca da da da ca ca ca da da da ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da ea ea ea ea ea ea ea ea ea ea ea ea ea ea ea da da da ca ca ca",
    "ca ca ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca aa aa da da ca ca ca ca da da da da da ca ca ca ca ca ca aa aa ca ca ca",
    "ca ca ca ca ca da da ca ca ca ca da da da da da ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da da ca ca ca ca da da da da da ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca aa aa da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da ca da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da ca ca ca ca ca da da da da da ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca ca da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca ca ca da da aa ca ca ca da da da da da ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca ca"
    };
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

    class TileMap {
    public:
        const char (*current_map)[TILE_COLUMNS * 3];

        TileMap(Player& playerRef);
        void setMapIndex(int index);
        Tile tile_at(int x, int y);
        void drawMap(Surface* screen, const Camera& camera);
        void loadLevel(int i);
        int getCurrentLevel() const { return (current_level - 1) % MAP_AMOUNT + 1; }
        int incrementMapIndex() { return current_level = current_level % MAP_AMOUNT + 1; }
        int current_level = 1;
    private:
        Player& player;
    };
};


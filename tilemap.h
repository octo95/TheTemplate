#pragma once
#include "surface.h"
#include "tile.h"

namespace Tmpl8
{
    // Constants
    const int TOTAL_MAPS = 3;
    const int TILE_ROWS = 16;
    const int TILE_COLUMNS = 25;
    const char MAP1[TILE_ROWS][TILE_COLUMNS * 3] = {
        "da da da da da da da da da da da da da da da da da da da da da da da da da",
        "da da da da da da da da da da da da da da da da da da da da da da da da da",
        "da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da",
        "da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da",
        "da da da da da da da da da da da da ca da da da da da da da da da da da da",
        "da da da da da da da da da da da da ca da da da da da da da da da da da da",
        "ca ca ca ca ca ca ca ca da da da ca ca ca da da da ca ca ca ca ca ca ca ca",
        "ca ca ca ca ca ca ca ca da da da ca ca ca da da da ca ca ca ca ca ca ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca da da da ea ea ea ea ea ea ea ea ea ea ea ea ea ea ea da da da ca ca",
        "ca ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca aa aa ca ca ca ca ca ca da da da da da ca ca ca ca ca ca aa aa ca ca",
        "ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca"
    };
    const char MAP2[TILE_ROWS][TILE_COLUMNS * 3] = {
        "da da da da da da da da da da da da da da da da ca da da da da da da da da",
        "da da da da da da da da da da da da da da da da ca da da da da da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da da da da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da da aa aa aa da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da aa aa da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da aa aa aa aa da da",
        "da da da da da da da da da da da da da da da da ca da da aa aa aa aa da da",
        "da da da da da da da da da da da da da da da da ca da da da aa da aa da da",
        "ca ca ca ca ca ca ca ca ca ca ca da da da da da ca ca da da aa da aa da ca",
        "ca ca ca ca ca ca ca ca ca ca ca da da da da da ca ca ca ca ca ca ca ca ca",
        "ca ca da da da da da da da da aa da da da da da da da da da da da da ca ca",
        "ca ca da da da da da da da da aa da da aa da da da da da da da da da ca ca",
        "ca ca da da ca ca ca ca ca ca aa da da aa ca ca ca ca ca ca da da da ca ca",
        "ca ca da da ca ca ca ca ca ca aa da da aa ca ca ca ca ca ca aa da da ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca"
    };
    const char MAP3[TILE_ROWS][TILE_COLUMNS * 3] = {
        "da da da da da da da da da da da da da da da da da da da da da da da da da",
        "da da da da da da da da da da da da da da da da da da da da da da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da da da da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da da da da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da da da da da da da",
        "da da da da da da da da da da da da da da da da ca da da da da da da da da",
        "da da da da da da da da da da da da da da da da ca da da da da da da da da",
        "ca ca ca ca ca ca ca ca ca ca ca da da da da da ca da da da da da da da da",
        "ca ca ca ca ca ca ca ca ca ca ca da da da da da ca ca ca ca ca ca ca ca aa",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca da da ca ca ca ca ca ca ca ca ca aa aa ca ca ca ca ca da da da ca ca",
        "ca ca da da ca ca ca ca ca ca da da da da ca ca ca ca ca ca da da da ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca"
    };

    class TileMap {
    public:
        const char (*current_map)[TILE_COLUMNS * 3];

        TileMap();
        int getCurrentLevel() const;
        void setMapIndex(int index);
        int incrementMapIndex();
        Tile tile_at(int x, int y);
        void drawMap(Surface* screen);
    private:
        int current_level = 1;
    };
};
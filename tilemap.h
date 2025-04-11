#pragma once
#include "surface.h"
#include "tile.h"

namespace Tmpl8
{
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
        "ca ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca",
        "ca ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca aa aa ca ca ca ca ca ca da da da da da ca ca ca ca ca ca aa aa ca ca",
        "ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca"
    };
    const char MAP2[TILE_ROWS][TILE_COLUMNS * 3] = {
        "da da da da da da da da da da da da da da da da da da da da da da da da da",
        "da da da da da da da da da da da da da da da da da da da da da da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da da da da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da da da da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da da da da da da da",
        "da da da da da da ca ca ca ca ca ca ca ca ca ca ca da da da da da da da da",
        "da da da da da da da da da da da da da da da da ca da da da da da da da da",
        "da da da da da da da da da da da da da da da da ca da da da da da da da da",
        "ca ca ca ca ca ca ca ca ca ca ca ca da da da da ca ca ca ca ca ca ca ca ca",
        "ca ca ca ca ca ca ca ca ca ca ca ca da da da da ca ca ca ca ca ca ca ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca da da aa aa da da da da da da aa aa da da da da da aa aa da da ca ca",
        "ca ca da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da ca ca",
        "ca ca da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da ca ca",
        "ca ca da da da da da da da da da da da da da da da da da da da da da ca ca",
        "ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca"
    };

    class TileMap {
    private:

    public:
        ///  Pointer to the current tile map in use
        char ** current_map;

        TileMap(int index);

        Tile tile_at(int x, int y) const;

        void drawMap(Surface* screen);
    };
};
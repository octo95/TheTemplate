#pragma once
#include "surface.h"

namespace Tmpl8
{
    // External variables
    extern Surface tiles;

    // Constants
    const int TILE_SIZE = 32;
    enum TileType 
    {
        None,
        Damage,
        End,
        Collision,
        Ice
    };

    // Tile struct
    struct Tile {
        int tx;
        int ty;
        TileType type;

        void DrawTile(Surface* screen, int x, int y);
    };
};
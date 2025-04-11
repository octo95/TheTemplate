#pragma once
#include "surface.h"

namespace Tmpl8
{
    extern Surface tiles;
    const int TILE_SIZE = 32;

    enum TileType {
        None,
        Damage,
        End,
        Collision
    };

    struct Tile {
        int tx;
        int ty;
        TileType type;

        void DrawTile(Surface* screen, int x, int y);
    };
};
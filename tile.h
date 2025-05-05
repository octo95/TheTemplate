#pragma once
#include "surface.h"
#include "camera.h"
#include "vec2_hash.h"

namespace Tmpl8
{
    // External variables
    extern Surface img_tilemap;

    // Constants
    const int TILE_SIZE = 32;
    enum TileType 
    {
        None = 0,
        Damage = 1,
        End = 2,
        Collision = 3,
        Ice = 4
    };

    // Tile struct
    struct Tile {
        int tx;
        int ty;
        TileType type;

        //void DrawTile(Surface* screen, int x, int y, const Camera& camera);
    };
}
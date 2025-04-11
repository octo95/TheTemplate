#include "tile.h"
#include "surface.h"
#include "tilemap.h"

#include <stdio.h>
#include <iostream>

namespace Tmpl8
{
    TileMap::TileMap(int index)
    {
        if      (index == 1)    current_map = (char**) MAP1;
        else if (index == 2)    current_map = (char**) MAP2;
        else if (index == 3)    current_map = (char**) MAP3;
    }

    Tile TileMap::tile_at(int x, int y)
    {

        int tile_row = y / TILE_SIZE;
        int tile_col = x / TILE_SIZE;

        char a = MAP1[tile_row][tile_col * 3];
        char b = MAP1[tile_row][tile_col * 3 + 1];

        int tx = a - 'a';
        int ty = b - 'a';

        TileType tile_type = None;

        if (a == 'd' && b == 'a')       tile_type = None;
        else if (a == 'a' && b == 'a')  tile_type = Damage;
        else if (a == 'b' && b == 'a')  tile_type = End;
        else if (a == 'c' && b == 'a')  tile_type = Collision;

        Tile tile = Tile{
            tx,
            ty,
            tile_type,
        };
        return tile;
    }

    void TileMap::drawMap(Surface* screen)
    {
        TileMap tile_map = *this;

        for (int y = 0; y < TILE_ROWS; y++)
            for (int x = 0; x < TILE_COLUMNS; x++)
            {
                Tile tile = tile_map.tile_at(x * TILE_SIZE, y * TILE_SIZE);
                tile.DrawTile(screen, x * TILE_SIZE, y * TILE_SIZE);
            }
    }
};

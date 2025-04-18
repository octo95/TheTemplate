#include "player.h"
#include "tilemap.h"
#include "game.h"

namespace Tmpl8
{
    TileMap::TileMap() {}

    Sprite img_map1(new Surface("assets/map1.png"), 1);

    int TileMap::getCurrentLevel() const
    {
        return (current_level - 1) % 3 + 1;
    }

    int TileMap::incrementMapIndex()
    {
        return current_level = current_level % 3 + 1;
    }

    void TileMap::setMapIndex(int index)
    {
        switch (index)
        {
        case 1:
            current_map = MAP1;
            // player->setPlayerDefaultPos(vec2(400.0f, 10.0f));
            break;
        case 2:
            current_map = MAP2;
            // player->setPlayerDefaultPos(vec2(80.0f, 10.0f));
            break;
        case 3:
            current_map = MAP3;
            // player->setPlayerDefaultPos(vec2(600.0f, 10.0f));
            break;
        }
    }

    Tile TileMap::tile_at(int x, int y)
    {
        int tile_row = y / TILE_SIZE;
        int tile_col = x / TILE_SIZE;

        char a = current_map[tile_row][tile_col * 3];
        char b = current_map[tile_row][tile_col * 3 + 1];

        int tx = a - 'a';
        int ty = b - 'a';

        TileType tile_type = None;

        if (a == 'd' && b == 'a')       tile_type = None;
        else if (a == 'a' && b == 'a')  tile_type = Damage;
        else if (a == 'b' && b == 'a')  tile_type = End;
        else if (a == 'c' && b == 'a')  tile_type = Collision;
        else if (a == 'e' && b == 'a')  tile_type = Ice;

        Tile tile = Tile
        {
            tx,
            ty,
            tile_type,
        };

        return tile;
    }

    void TileMap::drawMap(Surface* screen, const Camera& camera)
    {
        for (int y = 0; y < TILE_ROWS; ++y)
        {
            for (int x = 0; x < TILE_COLUMNS; ++x)
            {
                Tile tile = tile_at(x * TILE_SIZE, y * TILE_SIZE);
                tile.DrawTile(screen, x * TILE_SIZE, y * TILE_SIZE, camera);
            }
        }
    }
}

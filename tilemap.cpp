#include "tilemap.h"

namespace Tmpl8
{
    TileMap::TileMap(Player& playerRef) :
        player(playerRef)
    {
    }

    Sprite map_test(new Surface("assets/map_test.png"), 1);

    void TileMap::setMapIndex(int index)
    {
        switch (index)
        {
        case 1:
            current_map = MAP1;
            break;
        case 2:
            current_map = MAP2;
            break;
        case 3:
            current_map = MAP3;
            break;
        case 4:
            current_map = MAP4;
            break;
        case 5:
            current_map = MAP5;
            break;
            current_level = index;
        }
    }

    Tile TileMap::tile_at(vec2 pos)
    {
        int tile_row = (int)(pos.y / TILE_SIZE);
        int tile_col = (int)(pos.x / TILE_SIZE);

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

    std::string getTileColor(int color)
    {
        if (color == 0xFF0000) return "aa"; // Red      (Damage)
        if (color == 0x00FF00) return "ba"; // Green    (End)
        if (color == 0x0000FF) return "ca"; // Blue     (Collision)
        if (color == 0x000000) return "da"; // Black    (None)
        if (color == 0x00DEFF) return "ea"; // Cyan     (Ice)
    }

    void TileMap::readImageToCharMap()
    {
        int columns_amount = map_test.GetWidth() / TILE_SIZE;
        int rows_amount = map_test.GetHeight() / TILE_SIZE;

        for (int row = 0; row < rows_amount; ++row)
        {
            for (int col = 0; col < columns_amount; ++col)
            {
                // TODO
            }
        }

    }
}

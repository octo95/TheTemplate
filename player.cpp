#define WIN32_LEAN_AND_MEAN
#include "player.h"
#include "windows.h"
#include "tile.h"
#include <stdio.h>

namespace Tmpl8
{
    // Variables
    TileMap map = TileMap(2);
    Sprite player_img(new Surface("assets/tangerine.png"), 1);

    int hitbox_size = 16 - 1; // Radius of the hitbox with a tolerance of 1 pixel
    int px = DEFAULT_PX;
    int py = DEFAULT_PY;
    int player_img_width = player_img.GetWidth();
    int player_img_height = player_img.GetHeight();

    // Player functions
    TileType Player::CheckCollision(int x, int y, Surface* screen)
    {
        TileType tile_type = None;

        auto tile = map.tile_at(x, y);
        if (tile.type != TileType::None) tile_type = tile.type;

        tile = map.tile_at(x + hitbox_size * 2, y);
        if (tile.type != TileType::None) tile_type = tile.type;

        tile = map.tile_at(x, y + hitbox_size * 2);
        if (tile.type != TileType::None) tile_type = tile.type;

        tile = map.tile_at(x + hitbox_size * 2, y + hitbox_size * 2);
        if (tile.type != TileType::None) tile_type = tile.type;

        // Debug
        if (GetAsyncKeyState(VK_SPACE))
        {
            char coords[100];
            sprintf(coords, "Collision type: %d", tile_type);
            screen->Print(coords, 10, 30, 0xFFFF00);
        }
        return tile_type;
    }

    void Player::movePlayer(int& x, int& y, int player_speed)
    {
        // Player movement
        if (GetAsyncKeyState(VK_LEFT))  x -= player_speed;
        if (GetAsyncKeyState(VK_RIGHT)) x += player_speed;
        if (GetAsyncKeyState(VK_UP))    y -= player_speed;
        if (GetAsyncKeyState(VK_DOWN))  y += player_speed;

        // Clamping positions to stay on the screen
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + player_img_width > SCREEN_WIDTH) x = SCREEN_WIDTH - player_img_width;
        if (y + player_img_height > SCREEN_HEIGHT) y = SCREEN_HEIGHT - player_img_height;
    }

    void Player::manageCollisions(int& nx, int& ny, Surface* screen)
    {
        switch (CheckCollision(nx, ny, screen))
        {
        case TileType::None:
            px = nx;
            py = ny;
            break;
        case TileType::Collision:
            break;
        case TileType::Damage:
            px = DEFAULT_PX;
            py = DEFAULT_PY;
        case TileType::End:
            px = DEFAULT_PX;
            py = DEFAULT_PY;
            break;
        }
    }
};

#define WIN32_LEAN_AND_MEAN

#include "surface.h"
#include "template.h"
#include "game.h"
#include "tile.h"
#include "tilemap.h"
#include "windows.h"

#include <stdio.h>
#include <vector>

namespace Tmpl8
{
    Sprite player_img(new Surface("assets/tenjarine.png"), 1);

    const int DEFAULT_PX = 400, DEFAULT_PY = 10;
    int px = DEFAULT_PX;
    int py = DEFAULT_PY;

    void Game::Init() {}
    void Game::Shutdown() {}

    const int screen_width = 800;
    const int screen_height = 512;
    const int player_img_width = player_img.GetWidth();
    const int player_img_height = player_img.GetHeight();

    TileMap map = TileMap(1);

    // Radius of the hitbox with a tolerance of 1 pixel
    int hitbox_size = 16 - 1;

    TileType CheckCollision(int x, int y, Surface* screen)
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

        if (GetAsyncKeyState(VK_SPACE))
        {
            char coords[100];
            sprintf(coords, "Collision type: %d", tile_type);
            screen->Print(coords, 10, 30, 0xFFFF00);
        }
        return tile_type;
    }

    void DrawHitbox(int x, int y, bool enemy, Surface* screen)
    {
        int squareTop = y + player_img_width / 2 - hitbox_size;
        int squareRight = x + player_img_width / 2 + hitbox_size;
        int squareBottom = y + player_img_width / 2 + hitbox_size;
        int squareLeft = x + player_img_width / 2 - hitbox_size;

        int color = enemy ? 0xFF0000 : 0x00FF00;

        screen->Box(squareLeft, squareTop, squareRight, squareBottom, color);
    }

    void Debug(Surface* screen)
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            // Display the player's hitbox
            DrawHitbox(px, py, false, screen);

            // Display the player's screen coordinates
            char coords[100];
            sprintf(coords, "px: %d, py: %d", px, py);
            screen->Print(coords, 10, 10, 0xFFFF00);
        }
    }

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        map.drawMap(screen);

        Debug(screen);

        int nx = px, ny = py;
        int player_speed = 1;

        if (GetAsyncKeyState(VK_LEFT))
        {
            nx -= player_speed;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            nx += player_speed;
        }
        if (GetAsyncKeyState(VK_UP))
        {
            ny -= player_speed;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            ny += player_speed;
        }

        char coords[100];

        switch (CheckCollision(nx, ny, screen)) {
        case TileType::None:
            px = nx, py = ny;
            break;
        case TileType::Collision:
            break;
        case TileType::Damage:
            px = DEFAULT_PX, py = DEFAULT_PY;
            break;
        case TileType::End:
            px = DEFAULT_PX;
            py = DEFAULT_PY;
            break;
        }
        player_img.Draw(screen, px, py);
    }
}

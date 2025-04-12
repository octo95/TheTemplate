// Libraries and files
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
    Sprite player_img(new Surface("assets/tangerine.png"), 1);

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

        // Debug
        if (GetAsyncKeyState(VK_SPACE))
        {
            char coords[100];
            sprintf(coords, "Collision type: %d", tile_type);
            screen->Print(coords, 10, 30, 0xFFFF00);
        }
        return tile_type;
    }

    // Debug
    void DrawHitbox(int x, int y, Surface* screen)
    {
        int squareTop = y + player_img_width / 2 - hitbox_size;
        int squareRight = x + player_img_width / 2 + hitbox_size;
        int squareBottom = y + player_img_width / 2 + hitbox_size;
        int squareLeft = x + player_img_width / 2 - hitbox_size;

        screen->Box(squareLeft, squareTop, squareRight, squareBottom, 0x00FF00);
    }

    void Debug(Surface* screen)
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            // Display the player's hitbox
            DrawHitbox(px, py, screen);

            // Display the player's screen coordinates
            char coords[100];
            sprintf(coords, "px: %d, py: %d", px, py);
            screen->Print(coords, 10, 10, 0xFFFF00);
        }
    }

    void movePlayer(int& x, int& y, int player_speed)
    {
        // Player movement
        if (GetAsyncKeyState(VK_LEFT))  x -= player_speed;
        if (GetAsyncKeyState(VK_RIGHT)) x += player_speed;
        if (GetAsyncKeyState(VK_UP))    y -= player_speed;
        if (GetAsyncKeyState(VK_DOWN))  y += player_speed;

        // Clamping positions to stay on the screen
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + player_img_width > screen_width) x = screen_width - player_img_width;
        if (y + player_img_height > screen_height) y = screen_height - player_img_height;
    }

    void manageCollisions(int& nx, int& ny, Surface* screen)
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

    void Game::Tick(float deltaTime)
    {
        // Drawing the map and clearing the screen every tick.
        screen->Clear(0);
        map.drawMap(screen);

        // Player movement
        int nx = px, ny = py;
        movePlayer(nx, ny, 1);

        // Draw the player
        player_img.Draw(screen, px, py);

        // Managing each type of collisions and what to do.
        manageCollisions(nx, ny, screen);

        // Debug: Enabled if pressing space
        Debug(screen);
    }
}

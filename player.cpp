#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <stdio.h>

#include "game.h"
#include "player.h"

namespace Tmpl8
{
    // Variables
    Sprite player_img(new Surface("assets/tangerine.png"), 1);

    int hitbox_size = 16 - 2; // Radius of the hitbox with a tolerance of 2 pixels
    int player_img_width = player_img.GetWidth();
    int player_img_height = player_img.GetHeight();
    int spawn_px = 400;
    int spawn_py = 10;
    int px = spawn_px;
    int py = spawn_py;

    // Player functions
    TileType Player::CheckCollisionBottom(int x, int y)
    {
        TileType type = None;

        // Bottom-left
        auto tile = map->tile_at(x, y + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Bottom-right
        tile = map->tile_at(x + hitbox_size * 2, y + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Player::CheckCollisionSides(int x, int y)
    {
        TileType type = None;

        // Left
        auto tile = map->tile_at(x, y);
        if (tile.type != TileType::None) type = tile.type;

        tile = map->tile_at(x, y + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Right
        tile = map->tile_at(x + hitbox_size * 2, y);
        if (tile.type != TileType::None) type = tile.type;

        tile = map->tile_at(x + hitbox_size * 2, y + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    void Player::movePlayer(int& x, int& y)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            horizontal_speed -= ACCELERATION;
            if (horizontal_speed < -MAX_HORIZONTAL_SPEED) horizontal_speed = -MAX_HORIZONTAL_SPEED;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            horizontal_speed += ACCELERATION;
            if (horizontal_speed > MAX_HORIZONTAL_SPEED) horizontal_speed = MAX_HORIZONTAL_SPEED;
        }
        else // When there is no movement left, the player slides depending on the friction.
        {
            if (horizontal_speed > 0)
            {
                horizontal_speed -= friction;
                if (horizontal_speed < 0) horizontal_speed = 0;
            }
            else if (horizontal_speed < 0)
            {
                horizontal_speed += friction;
                if (horizontal_speed > 0) horizontal_speed = 0;
            }
        }

        bool upPressedLastFrame = false;
        bool isUpDown = GetAsyncKeyState(VK_UP) & 0x8000;
        if (isUpDown && !upPressedLastFrame)
        {
            // JUMP LOGIC TODO
        }

        // Rotation
        rotation += horizontal_speed;
        // printf("rotation: %d\n", rotation);

        // Horizontal movement (converting horizontal_speed < float->int >)
        x += static_cast<int>(horizontal_speed);

        // Vertical movement (gravity)
        vertical_speed = gravity;
        y += static_cast<int>(vertical_speed);

        // Clamp coordinates to make the player not go outside of the screen boundaries horizontally.
        if (x < 0) x = 0;
        if (x + player_img_width > SCREEN_WIDTH) x = SCREEN_WIDTH - player_img_width;
    }

    void Player::setPlayerDefaultPos()
    {
        // int level = map->getCurrentLevel();
        switch (true)
        {
        case 1:
            spawn_px = 400;
            spawn_py = 10;
            break;
        case 2:
            spawn_px = 300;
            spawn_py = 10;
            break;
        case 3:
            spawn_px = 600;
            spawn_py = 10;
            break;
        }
    }

    bool Player::manageCollisions(int& nx, int& ny, Surface* screen)
    {
        TileType CheckSides = CheckCollisionSides(nx, py);
        TileType CheckBottom = CheckCollisionBottom(px, ny);

        bool camShake = false;

        bool isNoneX = (CheckSides == TileType::None);
        bool isNoneY = (CheckBottom == TileType::None);
        bool isDamage = (CheckSides == TileType::Damage || CheckBottom == TileType::Damage);
        bool isEnd = (CheckSides == TileType::End || CheckBottom == TileType::End);
        bool isCollision = (CheckSides == TileType::Collision || CheckBottom == TileType::Collision);
        bool isIce = (CheckSides == TileType::Ice || CheckBottom == TileType::Ice);

        if (isNoneX) { px = nx; }
        if (isNoneY) { py = ny; }
        if (isDamage)
        {
            px = spawn_px;
            py = spawn_py;
            camShake = true;
        }
        if (isEnd)
        {
            map->setMapIndex(map->incrementMapIndex());
            px = spawn_px;
            py = spawn_py;
        }
        if (isCollision || isIce)
        {
            if (isIce)
                friction = 0.0f;
            else
                friction = 0.05f;

            vertical_speed = 0;
            py = (ny > py) ? py : ny;
        }

        return camShake;

    }

    void Player::setPlayerPos(int x, int y) { px = x, py = y; }

    vec2 Player::camFollowPlayer()
    {
        float camX = -TILE_SIZE;  // Offset by 1 tile to the left as we make the map 1 tile bigger on the sides for shaking.
        float camY = 0;
        int playerCenterY = py + player_img_height / 2;
        int screenCenterY = SCREEN_HEIGHT / 2;
        int mapHeight = TILE_ROWS * TILE_SIZE;
        int maxCamY = SCREEN_HEIGHT - mapHeight;

        // If player goes above the top half
        if (playerCenterY < screenCenterY)
            camY = 0;
        // If player goes below the screen center, follow
        else
        {
            camY = -(playerCenterY - screenCenterY);

            // If player goes bottom half
            if (camY < maxCamY)
                camY = maxCamY;
        }

        return { camX, camY };
    }
};

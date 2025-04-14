#define WIN32_LEAN_AND_MEAN
#include "player.h"
#include "windows.h"
#include "game.h"
#include "tile.h"
#include "tilemap.h"
#include <stdio.h>

namespace Tmpl8
{
    // Variables
    Sprite player_img(new Surface("assets/tangerine.png"), 1);

    int hitbox_size = 16 - 1; // Radius of the hitbox with a tolerance of 1 pixel
    int px = spawn_px;
    int py = spawn_py;
    int player_img_width = player_img.GetWidth();
    int player_img_height = player_img.GetHeight();
    int gravity = 3;
    int vertical_speed = 0;
    int spawn_px = 400;
    int spawn_py = 10;
    float horizontal_speed = 0.0f;
    float friction = 0.05f;

    // Player functions
    TileType Player::CheckCollisionBottom(int x, int y)
    {
        TileType type = None;

        // Bottom-left
        auto tile = map.tile_at(x, y + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Bottom-right
        tile = map.tile_at(x + hitbox_size * 2, y + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Player::CheckCollisionSides(int x, int y)
    {
        TileType type = None;

        // Left
        auto tile = map.tile_at(x, y);
        if (tile.type != TileType::None) type = tile.type;

        tile = map.tile_at(x, y + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Right
        tile = map.tile_at(x + hitbox_size * 2, y);
        if (tile.type != TileType::None) type = tile.type;

        tile = map.tile_at(x + hitbox_size * 2, y + hitbox_size * 2);
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
        bool upPressedLastFrame = false;
        bool isUpDown = GetAsyncKeyState(VK_UP) & 0x8000;
        if (isUpDown && !upPressedLastFrame)
        {
            // JUMP LOGIC TODO
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

        // Horizontal movement (converting horizontal_speed < float->int >)
        x += static_cast<int>(horizontal_speed);

        // Vertical movement (gravity)
        vertical_speed = gravity;
        y += vertical_speed;

       //  offsetPlayerPos(OFFSET_X, OFFSET_Y);

        // Clamp coordinates to make the player not go outside of the screen boundaries.
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + player_img_width > SCREEN_WIDTH) x = SCREEN_WIDTH - player_img_width;
        if (y + player_img_height > SCREEN_HEIGHT) y = SCREEN_HEIGHT - player_img_height;
    }

    void Player::setMapDefaultPos()
    {
        switch(map.getCurrentLevel())
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
    
    void Player::manageCollisions(int& nx, int& ny, Surface* screen)
    {
        // Horizontal collisions
        switch (CheckCollisionSides(nx, py))
        {
        case TileType::None:
            px = nx;
            break;
        case TileType::Damage:
            px = spawn_px;
            py = spawn_py;
            break;
        case TileType::End:
            map.setMapIndex(map.incrementMapIndex());
            px = spawn_px;
            py = spawn_py;
            return;
        case TileType::Collision:
            friction = 0.05f;
            vertical_speed = 0;
            py = (ny > py) ? py : ny;
            break;
        case TileType::Ice:
            friction = 0.0f;
            vertical_speed = 0;
            py = (ny > py) ? py : ny;
            break;
        }

        // Vertical collisions
        switch (CheckCollisionBottom(px, ny))
        {
        case TileType::None:
            py = ny;
            break;
        case TileType::Damage:
            px = spawn_px;
            py = spawn_py;
            break;
        case TileType::End:
            map.setMapIndex(map.incrementMapIndex());
            px = spawn_px;
            py = spawn_py;
            break;
        case TileType::Collision:
            friction = 0.05f;
            vertical_speed = 0;
            py = (ny > py) ? py : ny;
            break;
        case TileType::Ice:
            friction = 0.0f;
            vertical_speed = 0;
            py = (ny > py) ? py : ny;
            break;
        }
    }

    void Player::offsetPlayerPos(int offset_x, int offset_y)
    {
        px += offset_x;
        py += offset_y;
    }

    void Player::getPlayerPos(int& x, int& y)
    {
        x = px;
        y = py;
    }

    void Player::setPlayerPos(int x, int y)
    {
        px = x;
        py = y;
    }

    
};

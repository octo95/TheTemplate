#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <stdio.h>

#include "game.h"
#include "player.h"

namespace Tmpl8
{
    // Variables
    Sprite player_img(new Surface("assets/tangerine.png"), 1);

    int hitbox_size = 16 - 2;
    int player_img_width = player_img.GetWidth();
    int player_img_height = player_img.GetHeight();

    // Player functions
    TileType Player::CheckCollisionBottom(const vec2& pos)
    {
        TileType type = None;

        // Bottom-left
        auto tile = map->tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Bottom-right
        tile = map->tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Player::CheckCollisionSides(const vec2& pos)
    {
        TileType type = None;

        // Left
        auto tile = map->tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        tile = map->tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Right
        tile = map->tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        tile = map->tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    void Player::movePlayer(vec2& new_pos)
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
        else
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
            // TODO: Jump Logic
        }

        // Rotation
        rotation += horizontal_speed;

        // Horizontal movement
        new_pos.x += static_cast<int>(horizontal_speed);

        // Vertical movement
        vertical_speed = gravity;
        new_pos.y += static_cast<int>(vertical_speed);

        // Clamp horizontally
        if (new_pos.x < 0) new_pos.x = 0;
        if (new_pos.x + player_img_width > SCREEN_WIDTH)
            new_pos.x = SCREEN_WIDTH - player_img_width;
    }

    void Player::setPlayerDefaultPos(const vec2& pos)
    {
        default_pos = pos;
    }

    void Player::getPlayerDefaultPos(vec2& pos)
    {
        pos = default_pos;
    }

    void Player::getPlayerPos(vec2& pos)
    {
        pos = position;
    }

    void Player::setPlayerPos(const vec2& pos)
    {
        position = pos;
    }

    bool Player::manageCollisions(vec2& new_pos, Surface* screen)
    {
        TileType CheckSides = CheckCollisionSides({ new_pos.x, position.y });
        TileType CheckBottom = CheckCollisionBottom({ position.x, new_pos.y });

        bool camShake = false;

        bool isNoneX = (CheckSides == TileType::None);
        bool isNoneY = (CheckBottom == TileType::None);
        bool isDamage = (CheckSides == TileType::Damage || CheckBottom == TileType::Damage);
        bool isEnd = (CheckSides == TileType::End || CheckBottom == TileType::End);
        bool isCollision = (CheckSides == TileType::Collision || CheckBottom == TileType::Collision);
        bool isIce = (CheckSides == TileType::Ice || CheckBottom == TileType::Ice);

        if (isNoneX) position.x = new_pos.x;
        if (isNoneY) position.y = new_pos.y;
        if (isDamage)
        {
            position = default_pos;
            camShake = true;
        }
        if (isEnd)
        {
            map->setMapIndex(map->incrementMapIndex());
            position = default_pos;
        }
        if (isCollision || isIce)
        {
            if (isIce)
                friction = 0.0f;
            else
                friction = 0.05f;

            vertical_speed = 0;
            position.y = (new_pos.y > position.y) ? position.y : new_pos.y;
        }

        return camShake;
    }

    vec2 Player::camFollowPlayer()
    {
        float camX = -TILE_SIZE;
        float camY = 0;
        int playerCenterY = static_cast<int>(position.y) + player_img_height / 2;
        int screenCenterY = SCREEN_HEIGHT / 2;
        int mapHeight = TILE_ROWS * TILE_SIZE;
        int maxCamY = SCREEN_HEIGHT - mapHeight;

        if (playerCenterY < screenCenterY)
            camY = 0;
        else
        {
            camY = -(playerCenterY - screenCenterY);

            if (camY < maxCamY)
                camY = maxCamY;
        }

        return { camX, camY };
    }
};

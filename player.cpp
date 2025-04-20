#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <stdio.h>

#include "game.h"
#include "player.h"

namespace Tmpl8
{
    Player::Player(TileMap& tmap) : 
        map(tmap) 
    {}

    // Variables
    Sprite player_img(new Surface("assets/tangerine.png"), 1);

    int hitbox_size = 16 - 2; // Tolerance of 2 pixels on the hitbox
    int player_img_width = player_img.GetWidth();
    int player_img_height = player_img.GetHeight();
    bool canJump = false;

    // Player functions
    TileType Player::CheckCollisionBottom(const vec2& pos)
    {
        TileType type = None;

        // Bottom-left
        auto tile = map.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Bottom-right
        tile = map.tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Player::CheckCollisionSides(const vec2& pos)
    {
        TileType type = None;

        // Left
        auto tile = map.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        tile = map.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Right
        tile = map.tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        tile = map.tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    void Player::movePlayer(vec2& new_pos)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            velocity.x -= ACCELERATION;
            if (velocity.x < -MAX_HORIZONTAL_SPEED) velocity.x = -MAX_HORIZONTAL_SPEED;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            velocity.x += ACCELERATION;
            if (velocity.x > MAX_HORIZONTAL_SPEED) velocity.x = MAX_HORIZONTAL_SPEED;
        }
        else
        {
            if (velocity.x > 0)
            {
                velocity.x -= friction;
                if (velocity.x < 0) velocity.x = 0;
            }
            else if (velocity.x < 0)
            {
                velocity.x += friction;
                if (velocity.x > 0) velocity.x = 0;
            }
        }

        velocity.y += gravity;
        if (velocity.y > 5) velocity.y = 5; // Clamp fall speed

        TileType CheckSides = CheckCollisionSides({ new_pos.x + velocity.x, position.y });
        TileType CheckBottom = CheckCollisionBottom({ position.x, new_pos.y + velocity.y });

        bool isCollision = (CheckSides == TileType::Collision || CheckBottom == TileType::Collision);
        bool isIce = (CheckSides == TileType::Ice || CheckBottom == TileType::Ice);
        canJump = GetAsyncKeyState(VK_UP) && (CheckBottom == 3 || CheckBottom == 4) && collectibles_collected > 0;

        if (canJump)
        {
            velocity.y += -6.0f;
            collectibles_collected--;
        }

        if (isCollision || isIce)
        {
            //if (CheckSides) {
            //    float norm = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
            //    float angle = acos(velocity.x / norm);
            //
            //    velocity.x = norm * -cos(angle);
            //    velocity.y = -norm * sin(angle);                
            //}
            //else if (CheckBottom != TileType::None) {
            //    float norm = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
            //    float angle = acos(velocity.y / norm);
            //
            //    velocity.x = norm * cos(angle);
            //    velocity.y = -norm * -sin(angle);
            //}
            //else if (!CheckBottom) {
            //    velocity.y += gravity * 0.3;
            //    if (velocity.y > 5) velocity.y = 5;
            //}

            //velocity.x *= pow(ENERGY_LOSS, 2);
            //velocity.y *= pow(ENERGY_LOSS, 2);
        }

        // Horizontal movement
        new_pos.x += velocity.x;

        // Vertical movement        
        new_pos.y += velocity.y;

        // Clamp horizontally
        if (new_pos.x < 0) new_pos.x = 0;
        if (new_pos.x + player_img_width > SCREEN_WIDTH + TILE_SIZE)
            new_pos.x = SCREEN_WIDTH - player_img_width + TILE_SIZE;
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

    bool Player::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
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
        else if (isDamage)
        {
            loadCollectiblesForMap(map.getCurrentLevel());
            position = default_pos;
            camShake = true;
        }
        else if (isEnd)
        {
            map.setMapIndex(map.incrementMapIndex());
            loadCollectiblesForMap(map.getCurrentLevel());
            position = default_pos;
        }
        else if (isCollision || isIce)
        {
            if (isIce)
                friction = 0.0f;
            else
                friction = 0.05f;

            velocity.y = 0;
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

#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "collisions.h"

namespace Tmpl8
{
    Collisions::Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef, WallMap& wallRef, Level& levelRef, Camera& cameraRef) :
        player(playerRef),
        tilemap(tilemapRef),
        ai_follow(ai_followRef),
        collectible(collectibleRef),
        wall(wallRef),
        level(levelRef),
        camera(cameraRef)
    {}

    // Player functions
    TileType Collisions::CheckCollisionBottom(const vec2& pos)
    {
        TileType type = None;

        // Bottom-left
        auto tile = tilemap.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Bottom-right
        tile = tilemap.tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Collisions::CheckCollisionTop(const vec2& pos)
    {
        TileType type = None;

        // Top-left
        auto tile = tilemap.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        // Top-right
        tile = tilemap.tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Collisions::CheckCollisionSides(const vec2& pos)
    {
        TileType type = None;

        // Left
        auto tile = tilemap.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        tile = tilemap.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Right
        tile = tilemap.tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        tile = tilemap.tile_at(static_cast<int>(pos.x) + hitbox_size * 2, static_cast<int>(pos.y) + hitbox_size * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    void Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
    {
        TileType CheckSides = CheckCollisionSides({ new_pos.x, player.position.y });
        TileType CheckBottom = CheckCollisionBottom({ player.position.x, new_pos.y + player.velocity.y});
        TileType CheckTop = CheckCollisionTop({ player.position.x, new_pos.y + player.velocity.y});

        bool isNoneX = (CheckSides == TileType::None);
        bool isNoneY = (CheckBottom == TileType::None);
        bool isDamage = (CheckSides == TileType::Damage || CheckBottom == TileType::Damage || CheckTop == TileType::Damage || ai_follow.isTouchingPlayer());
        bool isEnd = (CheckSides == TileType::End || CheckBottom == TileType::End || CheckTop == TileType::End);
        bool isCollision = (CheckSides == TileType::Collision || CheckBottom == TileType::Collision || CheckTop==TileType::Collision);
        bool isIce = (CheckBottom == TileType::Ice || CheckTop == TileType::Ice);

        if (isNoneX) player.position.x = new_pos.x;
        if (isNoneY) player.position.y = new_pos.y;
        if (isDamage)
        {
            ai_follow.setAIFollowPos(level.AI_FOLLOW_DEFAULT_POS[tilemap.getCurrentLevel()-1]);
            loadCollectiblesForMap(tilemap.getCurrentLevel());
            loadWallsForMap(tilemap.getCurrentLevel());
            player.position = player.default_pos;
            camera.setShakeState(true);
        }
        else if (isEnd)
        {
            ai_follow.setAIFollowPos(level.AI_FOLLOW_DEFAULT_POS[0]);
            tilemap.setMapIndex(tilemap.incrementMapIndex());
            loadCollectiblesForMap(tilemap.getCurrentLevel());
            player.position = player.default_pos;
        }
        else if (isCollision || isIce)
        {
            friction = isIce ? 0.0f : 0.05f;
            player.velocity.y = 0;
            player.position.y = (new_pos.y > player.position.y) ? player.position.y : new_pos.y;
        }

        if (walls_collected > 0)
        {
            walls_collected--;
            player.velocity += (player.velocity.x <= 0) ? wall_force : -wall_force;
        }
    }

    bool Collisions::getJumpState(vec2& new_pos)
    {
        bool canPlayerJump = false;
        TileType CheckSides = CheckCollisionSides({ new_pos.x + player.velocity.x, player.position.y });
        TileType CheckBottom = CheckCollisionBottom({ player.position.x, new_pos.y + player.velocity.y });

        bool isCollision = (CheckSides == TileType::Collision || CheckBottom == TileType::Collision);
        bool isIce = (CheckSides == TileType::Ice || CheckBottom == TileType::Ice);

        canPlayerJump = GetAsyncKeyState(VK_UP) && (CheckBottom == 3 || CheckBottom == 4) && collectibles_collected > 0;

        return canPlayerJump;
    }

    void Collisions::applyBouncingPhysics(vec2& new_pos)
    {
        if (this->CheckCollisionSides(vec2{ new_pos.x + player.velocity.x, new_pos.y }) != TileType::None)
        {
            float norm = sqrt(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
            float angle = acos(player.velocity.x / norm);

            player.velocity.x = norm * -cos(angle);
            player.velocity.y = norm * sin(angle);

            // Apply the power loss for the sides collisions
            player.velocity.x *= pow(player.ENERGY_LOSS, 2);
        }
        if (player.velocity.y > 2.0f && this->CheckCollisionBottom(vec2{ new_pos.x, new_pos.y + player.velocity.y }) != TileType::None)
        {
            float norm = sqrt(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
            float angle = acos(player.velocity.x / norm);

            player.velocity.x = norm * cos(angle);
            player.velocity.y = -norm * sin(angle);

            // Apply the power loss for the bottom collisions
            player.velocity.y *= pow(player.ENERGY_LOSS, 2);
        }
    }
}


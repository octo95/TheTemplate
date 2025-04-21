#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "collisions.h"

namespace Tmpl8
{
    Collisions::Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef, WallMap& wallRef, Level& levelRef) :
        player(playerRef),
        tilemap(tilemapRef),
        ai_follow(ai_followRef),
        collectible(collectibleRef),
        wall(wallRef),
        level(levelRef)
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

    bool Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
    {
        TileType CheckSides = CheckCollisionSides({ new_pos.x, player.position.y });
        TileType CheckBottom = CheckCollisionBottom({ player.position.x, new_pos.y });
        TileType CheckCenter = TileType::None;
        auto tile = tilemap.tile_at(static_cast<int>(new_pos.x) + hitbox_size / 2, static_cast<int>(new_pos.y) + hitbox_size / 2);
        if (tile.type != TileType::None) CheckCenter = tile.type;

        bool camShake = false;

        bool isNoneX = (CheckSides == TileType::None);
        bool isNoneY = (CheckBottom == TileType::None);
        bool isDamage = (CheckCenter == TileType::Damage || CheckSides == TileType::Damage || CheckBottom == TileType::Damage || playerHitAI); // need to add AI touch condition
        bool isEnd = (CheckCenter == TileType::End || CheckSides == TileType::End || CheckBottom == TileType::End);
        bool isCollision = (CheckCenter == TileType::Collision || CheckSides == TileType::Collision || CheckBottom == TileType::Collision);
        bool isIce = (CheckSides == TileType::Ice || CheckBottom == TileType::Ice);

        if (isNoneX) player.position.x = new_pos.x;
        if (isNoneY) player.position.y = new_pos.y;
        else if (isDamage)
        {
            ai_follow.setAIFollowPos(level.AI_FOLLOW_DEFAULT_POS[tilemap.getCurrentLevel()-1]);
            loadCollectiblesForMap(tilemap.getCurrentLevel());
            player.position = player.default_pos;
            camShake = true;
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

        return camShake;
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

    void Collisions::playerCollisionsAI()
    {
        float ai_rad = img_ai_follow.GetWidth() / 2.0f;
        float player_rad = player_img_width / 2.0f;

        float radii_sum = ai_rad + player_rad;

        float dx = ai_follow.position.x - player.position.x;
        float dy = ai_follow.position.y - player.position.y;
        float distance = sqrtf(dx * dx + dy * dy);

        playerHitAI = (distance <= radii_sum);
    }
}


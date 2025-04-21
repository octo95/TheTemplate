#include "collisions.h"

namespace Tmpl8
{
    Collisions::Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef) :
        player(playerRef),
        tilemap(tilemapRef),
        ai_follow(ai_followRef)
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

        bool camShake = false;

        bool isNoneX = (CheckSides == TileType::None);
        bool isNoneY = (CheckBottom == TileType::None);
        bool isDamage = (CheckSides == TileType::Damage || CheckBottom == TileType::Damage); // need to add AI touch condition
        bool isEnd = (CheckSides == TileType::End || CheckBottom == TileType::End);
        bool isCollision = (CheckSides == TileType::Collision || CheckBottom == TileType::Collision);
        bool isIce = (CheckSides == TileType::Ice || CheckBottom == TileType::Ice);

        if (isNoneX) player.position.x = new_pos.x;
        if (isNoneY) player.position.y = new_pos.y;
        else if (isDamage)
        {
            loadCollectiblesForMap(tilemap.getCurrentLevel());
            player.position = player.default_pos;
            camShake = true;
        }
        else if (isEnd)
        {
            tilemap.setMapIndex(tilemap.incrementMapIndex());
            loadCollectiblesForMap(tilemap.getCurrentLevel());
            player.position = player.default_pos;
        }
        else if (isCollision || isIce)
        {
            if (isIce)
                friction = 0.0f;
            else
                friction = 0.05f;

            player.velocity.y = 0;
            player.position.y = (new_pos.y > player.position.y) ? player.position.y : new_pos.y;
        }

        if (walls_collected > 0)
        {
            walls_collected--;
            if (player.velocity.x <= 0)
            {
                player.velocity.x += wall_force;
            }
            else if (player.velocity.x > 0)
            {
                player.velocity.x -= wall_force;
            }
        }

        return camShake;
    }
}


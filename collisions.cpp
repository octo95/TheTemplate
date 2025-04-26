#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "collisions.h"

namespace Tmpl8
{
    Collisions::Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef, WallMap& wallRef, Level& levelRef, Camera& cameraRef, GameSound& gamesoundRef) :
        player(playerRef),
        tilemap(tilemapRef),
        ai_follow(ai_followRef),
        collectible(collectibleRef),
        wall(wallRef),
        level(levelRef),
        camera(cameraRef),
        gamesound(gamesoundRef)
    {}

    TileType Collisions::CheckCollisionBottom(const vec2& pos)
    {
        TileType type = None;

        // Bottom-left
        auto tile = tilemap.tile_at((int)(pos.x), (int)(pos.y) + hitbox_radius * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Bottom-right
        tile = tilemap.tile_at((int)(pos.x) + hitbox_radius * 2, (int)(pos.y) + hitbox_radius * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Collisions::CheckCollisionLeft(const vec2& pos)
    {
        TileType type = None;

        // Top-left
        auto tile = tilemap.tile_at((int)(pos.x), (int)(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        // Bottom-left
        tile = tilemap.tile_at((int)(pos.x), (int)(pos.y) + hitbox_radius * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Collisions::CheckCollisionRight(const vec2& pos)
    {
        TileType type = None;

        // Top-right
        auto tile = tilemap.tile_at((int)(pos.x) + hitbox_radius * 2, (int)(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        // Bottom-right
        tile = tilemap.tile_at((int)(pos.x) + hitbox_radius * 2, (int)(pos.y) + hitbox_radius * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Collisions::CheckCollisionTop(const vec2& pos)
    {
        TileType type = None;

        // Top-left
        auto tile = tilemap.tile_at((int)(pos.x), (int)(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        // Top-right
        tile = tilemap.tile_at((int)(pos.x) + hitbox_radius * 2, (int)(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }


    void Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
    {
        TileType CheckLeft = CheckCollisionLeft({ new_pos.x, player.position.y });
        TileType CheckRight = CheckCollisionRight({ new_pos.x, player.position.y });
        TileType CheckBottom = CheckCollisionBottom({ player.position.x, new_pos.y + player.velocity.y });
        TileType CheckTop = CheckCollisionTop({ player.position.x, new_pos.y + player.velocity.y});

        bool isNoneX = (CheckLeft == TileType::None || CheckRight == TileType::None);
        bool isNoneY = (CheckBottom == TileType::None);
        bool isDamage = (CheckLeft == TileType::Damage || CheckRight == TileType::Damage || CheckBottom == TileType::Damage || CheckTop == TileType::Damage || ai_follow.isTouchingPlayer());
        bool isEnd = (CheckLeft == TileType::End || CheckRight == TileType::End || CheckBottom == TileType::End || CheckTop == TileType::End);
        bool isCollision = (CheckLeft == TileType::Collision || CheckRight == TileType::Collision || CheckBottom == TileType::Collision || CheckTop==TileType::Collision);
        bool isIce = (CheckBottom == TileType::Ice || CheckTop == TileType::Ice);

        bool FallNormal = player.velocity.y >= trigger_fall_normal && player.velocity.y < trigger_fall_hard;
        bool FallHard = player.velocity.y >= trigger_fall_hard;

        // SFX: if falling from a high distance play <snd_fall_strong.wav>, otherwise from a smaller one play <snd_fall.wav> and if even smaller don't play any SFX.
        if ((CheckBottom == TileType::Collision || CheckBottom == TileType::Ice) && FallNormal) 
        {
            gamesound.playSound(gamesound.snd_fall);
            //printf("fall normal: %.0f\n", player.velocity.y);
        }
        if ((CheckBottom == TileType::Collision || CheckBottom == TileType::Ice) && FallHard) 
        {
            gamesound.playSound(gamesound.snd_fall_strong);
            //printf("fall hard: %.0f\n", player.velocity.y);
        }

        if (isNoneX) player.position.x = new_pos.x;
        if (isNoneY) player.position.y = new_pos.y;
        if (isDamage)
        {
            level.loadLevel(tilemap.getCurrentLevel());
            gamesound.playSound(gamesound.snd_damage);
            camera.setShakeState(true);
        }
        else if (isEnd)
        {
            if (tilemap.getCurrentLevel() == MAP_AMOUNT) 
            {
                level.game_finished = true;
                return;
            }
            gamesound.playSound(gamesound.snd_level_finished);
            level.level_finished = true;
        }
        else if (isCollision || isIce)
        {
            player.friction = isIce ? 0.0f : 0.05f;
            player.velocity.y = 0;
            player.position.y = (new_pos.y > player.position.y) ? player.position.y : new_pos.y;
        }

        if (walls_collected > 0)
        {
            walls_collected--;
            player.velocity.x += (player.velocity.x >= 0) ? wall_force : -wall_force;
            //player.velocity.y += (player.velocity.y <= 0) ? wall_force : -wall_force;
        }

    }

    bool Collisions::getJumpState(vec2& new_pos)
    {
        bool canPlayerJump = false;
        TileType CheckBottom = CheckCollisionBottom({ player.position.x, new_pos.y + player.velocity.y });

        bool isCollision = (CheckBottom == TileType::Collision);
        bool isIce = (CheckBottom == TileType::Ice);

        // The player can jump if they press up, touch the ground and have at least 1 collectible.
        canPlayerJump = GetAsyncKeyState(VK_UP) && (CheckBottom == 3 || CheckBottom == 4) && collectibles_collected > 0;

        return canPlayerJump;
    }

    void Collisions::applyBouncingPhysics(vec2& new_pos)
    {
        bool CheckLeft = this->CheckCollisionLeft(vec2{ new_pos.x + player.velocity.x, new_pos.y }) != TileType::None;
        bool CheckRight = this->CheckCollisionRight(vec2{ new_pos.x + player.velocity.x, new_pos.y }) != TileType::None;
        bool CheckBottom = this->CheckCollisionBottom(vec2{ new_pos.x, new_pos.y + player.velocity.y }) != TileType::None;
        
        bool FallLight = player.velocity.y >= trigger_fall_light && player.velocity.y < trigger_fall_normal;

        if (CheckLeft || CheckRight)
        {
            float norm = sqrt(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
            float angle = acos(player.velocity.x / norm);

            player.velocity.x = norm * -cos(angle);
            player.velocity.y = norm * sin(angle);

            // Apply the power loss for the sides collisions
            player.velocity.x *= pow(player.ENERGY_LOSS, 2);
        }
        //printf("Bottom: %d, VelY: %f\n", (int)CheckBottom, player.velocity.y);
        if (CheckBottom && FallLight)
        {
            //printf("fall light: %.0f\n", player.velocity.y);
            float norm = sqrt(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
            float angle = acos(player.velocity.x / norm);

            player.velocity.x = norm * cos(angle);
            player.velocity.y = -norm * sin(angle);

            // Apply the power loss for the bottom collisions
            player.velocity.y *= pow(player.ENERGY_LOSS, 2);
        }
    }
}

/*

    TileType Collisions::CheckCollisionBottom(const vec2int& pos)
    {
        TileType t_left = TileType::None;
        TileType t_right = TileType::None;

        int clamp_pos_x = pos.x / TILE_radius * TILE_radius;
        int clamp_pos_y = pos.y / TILE_radius * TILE_radius;

        if (((pos.y - clamp_pos_y) + hitbox_radius * 2) >= TILE_radius) {
            auto l = tilemap.tile_at(clamp_pos_x, pos.y + TILE_radius);
            if (l.type != TileType::None) t_left = l.type;

            auto r = tilemap.tile_at((pos.x + (hitbox_radius * 2)) / TILE_radius * TILE_radius, pos.y + TILE_radius);
            if (r.type != TileType::None) t_right = r.type;
        }

        // If the player is more than half on the left
        if ((t_left == TileType::Damage || t_left == TileType::End) && (pos.x - (pos.x / TILE_radius * TILE_radius)) < hitbox_radius) {
            return t_left;
        }

        // If the player is more than half on the right
        if ((t_right == TileType::Damage || t_right == TileType::End) && (pos.x - (pos.x / TILE_radius * TILE_radius)) >= hitbox_radius) {
            return t_right;
        }

        return (t_left == TileType::Collision || t_left == TileType::Ice) ? t_left : t_right;
    }


    TileType Collisions::CheckCollisionTop(const vec2& pos)
    {
        TileType type = None;

        // Top-left
        auto tile = tilemap.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        // Top-right
        tile = tilemap.tile_at(static_cast<int>(pos.x) + hitbox_radius * 2, static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    TileType Collisions::CheckCollisionSides(const vec2int& pos)
    {
        TileType t_top_left = TileType::None;
        TileType t_bot_left = TileType::None;

        int clamp_pos_x = pos.x / TILE_radius * TILE_radius;
        int clamp_pos_y = pos.y / TILE_radius * TILE_radius;

        if ((pos.x - clamp_pos_x) <= 0) {
            auto tile = tilemap.tile_at(clamp_pos_x, pos.y);
            if (tile.type != TileType::None) t_top_left = tile.type;
        }

        if ((pos.x - clamp_pos_x) <= 0) {
            auto tile = tilemap.tile_at(clamp_pos_x, pos.y + hitbox_radius * 2);
            if (tile.type != TileType::None) t_bot_left = tile.type;
        }

        TileType t_top_right = TileType::None;
        TileType t_bot_right = TileType::None;

        if (((pos.x + hitbox_radius * 2) - clamp_pos_x) >= TILE_radius-1) {
            auto tile = tilemap.tile_at(clamp_pos_x + TILE_radius, pos.y);
            if (tile.type != TileType::None) t_top_right = tile.type;
        }

        if (((pos.x + hitbox_radius * 2) - clamp_pos_x) >= TILE_radius-1) {
            auto tile = tilemap.tile_at(clamp_pos_x + TILE_radius, pos.y + hitbox_radius * 2);
            if (tile.type != TileType::None) t_bot_right = tile.type;
        }

        TileType* check[4] = { &t_top_left, &t_bot_left, &t_top_right, &t_bot_right };
        for (int i = 0; i < 4; i++) {
            if (*check[i] != TileType::None) {
                return *check[i];
            }
        }

        return TileType::None;

        //TileType type = None;
        //
        //// Left
        //auto tile = tilemap.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y));
        //if (tile.type != TileType::None) type = tile.type;
        //
        //tile = tilemap.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y) + hitbox_radius * 2);
        //if (tile.type != TileType::None) type = tile.type;
        //
        //// Right
        //tile = tilemap.tile_at(static_cast<int>(pos.x) + hitbox_radius * 2, static_cast<int>(pos.y));
        //if (tile.type != TileType::None) type = tile.type;
        //
        //tile = tilemap.tile_at(static_cast<int>(pos.x) + hitbox_radius * 2, static_cast<int>(pos.y) + hitbox_radius * 2);
        //if (tile.type != TileType::None) type = tile.type;
        //
        //return type;
    }
*/
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

    // Player functions
    TileType Collisions::CheckCollisionBottom(const vec2int& pos)
    {
        TileType t_left = TileType::None;

        int clamp_pos_x = pos.x / TILE_SIZE * TILE_SIZE;
        int clamp_pos_y = pos.y / TILE_SIZE * TILE_SIZE;

        if (((pos.y - clamp_pos_y) + hitbox_radius * 2) % TILE_SIZE != 0) {
            auto tile = tilemap.tile_at(clamp_pos_x, clamp_pos_y + TILE_SIZE);
            if (tile.type != TileType::None) t_left = tile.type;
        }

        TileType t_right = TileType::None;

        clamp_pos_x = pos.x + (hitbox_radius * 2) * TILE_SIZE / TILE_SIZE;

        if (((pos.y - clamp_pos_y) + hitbox_radius * 2) % TILE_SIZE != 0) {
            auto tile = tilemap.tile_at(clamp_pos_x, clamp_pos_y + TILE_SIZE);
            if (tile.type != TileType::None) t_right = tile.type;
        }

        // If the player is more than half on the left
        if ((t_left == TileType::Damage || t_left == TileType::End) && (pos.x - (pos.x / TILE_SIZE * TILE_SIZE)) < hitbox_radius) {
            return t_left;
        }

        // If the player is more than half on the right
        if ((t_right == TileType::Damage || t_right == TileType::End) && (pos.x - (pos.x / TILE_SIZE * TILE_SIZE)) >= hitbox_radius) {
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

    TileType Collisions::CheckCollisionSides(const vec2& pos)
    {
        TileType type = None;

        // Left
        auto tile = tilemap.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        tile = tilemap.tile_at(static_cast<int>(pos.x), static_cast<int>(pos.y) + hitbox_radius * 2);
        if (tile.type != TileType::None) type = tile.type;

        // Right
        tile = tilemap.tile_at(static_cast<int>(pos.x) + hitbox_radius * 2, static_cast<int>(pos.y));
        if (tile.type != TileType::None) type = tile.type;

        tile = tilemap.tile_at(static_cast<int>(pos.x) + hitbox_radius * 2, static_cast<int>(pos.y) + hitbox_radius * 2);
        if (tile.type != TileType::None) type = tile.type;

        return type;
    }

    void Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
    {
        TileType CheckSides = CheckCollisionSides({ new_pos.x, player.position.y });
        TileType CheckBottom = CheckCollisionBottom({ (int)player.position.x, (int)(new_pos.y + player.velocity.y)});
        TileType CheckTop = CheckCollisionTop({ player.position.x, new_pos.y + player.velocity.y});

        bool isNoneX = (CheckSides == TileType::None);
        bool isNoneY = (CheckBottom == TileType::None);
        bool isDamage = (CheckSides == TileType::Damage || CheckBottom == TileType::Damage || CheckTop == TileType::Damage || ai_follow.isTouchingPlayer());
        bool isEnd = (CheckSides == TileType::End || CheckBottom == TileType::End || CheckTop == TileType::End);
        bool isCollision = (CheckSides == TileType::Collision || CheckBottom == TileType::Collision || CheckTop==TileType::Collision);
        bool isIce = (CheckBottom == TileType::Ice || CheckTop == TileType::Ice);

        // SFX: if falling from a high distance play <snd_fall_strong.wav>, otherwise from a smaller one play <snd_fall.wav> and if even smaller don't play any SFX.
        if ((CheckBottom == TileType::Collision || CheckBottom == TileType::Ice) && player.velocity.y > trigger_fall_normal && player.velocity.y < trigger_fall_hard) gamesound.playSound(gamesound.snd_fall);
        if ((CheckBottom == TileType::Collision || CheckBottom == TileType::Ice) && player.velocity.y >= trigger_fall_hard) gamesound.playSound(gamesound.snd_fall_strong);

        if (isNoneX) player.position.x = new_pos.x;
        if (isNoneY) player.position.y = new_pos.y;
        if (isDamage)
        {
            gamesound.playSound(gamesound.snd_damage);
            ai_follow.setAIFollowPos(level.AI_FOLLOW_DEFAULT_POS[tilemap.getCurrentLevel()-1]);
            loadCollectiblesForMap(tilemap.getCurrentLevel());
            loadWallsForMap(tilemap.getCurrentLevel());
            player.position = player.default_pos;
            camera.setShakeState(true);
        }
        else if (isEnd)
        {
            gamesound.playSound(gamesound.snd_level_finished);
            level.level_finished = true;
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
        TileType CheckBottom = CheckCollisionBottom({ (int)player.position.x, int(new_pos.y + player.velocity.y) });

        bool isCollision = (CheckSides == TileType::Collision || CheckBottom == TileType::Collision);
        bool isIce = (CheckSides == TileType::Ice || CheckBottom == TileType::Ice);

        // The player can jump if they press up, touch the ground and have at least 1 collectible.
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
        if (player.velocity.y > 2.0f && this->CheckCollisionBottom(vec2int{ (int)new_pos.x, (int)(new_pos.y + player.velocity.y) }) != TileType::None)
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

/*
* + END LEVEL LOGIC +
* 
* - setLevelState
*  > public int level_state = false; (level.h)
*  > void setLevelState(bool state) { return (state = level_state); } (level.h)
*  > bool getLevelState(bool state) { return state; } (collisions.h)
*  > collisions.setLevelState(level.getLevelState()); (game.cpp)
*  > case isEnd: 
*  > in level.cpp, called in case isEnd in collisions
* - pause game
* - pop-up for next level
* - if next level then load next level
*/
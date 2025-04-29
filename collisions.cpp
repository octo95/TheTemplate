#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "collisions.h"
#include <cmath>

namespace Tmpl8
{
    Collisions::Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef, WallMap& wallRef, Level& levelRef, Camera& cameraRef, GameSound& gamesoundRef, Bell& bellRef, AI_Patrol& ai_patrolRef, AI_Copy& ai_copyRef) :
        player(playerRef),
        tilemap(tilemapRef),
        ai_follow(ai_followRef),
        collectible(collectibleRef),
        wall(wallRef),
        level(levelRef),
        camera(cameraRef),
        gamesound(gamesoundRef),
        bell(bellRef),
        ai_patrol(ai_patrolRef),
        ai_copy(ai_copyRef)
    {}

    Sprite img_water_slide_right(new Surface("assets/images/entities/img_water_slide_right.tga"), 3);
    Sprite img_water_slide_left(new Surface("assets/images/entities/img_water_slide_left.tga"), 3);

    TileType Collisions::CheckCollisionBottom(const vec2& pos)
    {
        TileType type = TileType::None;

        // Check bottom left
        type = checkCollisionAtOffset(pos, vec2(0, hitbox_radius * 2));
        if (type != TileType::None) return type;

        // Check bottom right
        type = checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, hitbox_radius * 2));
        return type;
    }

    TileType Collisions::CheckCollisionLeft(const vec2& pos)
    {
        TileType type = TileType::None;

        // Check top-left
        type = checkCollisionAtOffset(pos, vec2(0, 0));
        if (type != TileType::None) return type;

        // Check bottom-left
        type = checkCollisionAtOffset(pos, vec2(0, hitbox_radius * 2));
        return type;
    }

    TileType Collisions::CheckCollisionRight(const vec2& pos)
    {
        TileType type = TileType::None;

        // Check top-right
        type = checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, 0));
        if (type != TileType::None) return type;

        // Check bottom-right
        type = checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, hitbox_radius * 2));
        return type;
    }

    TileType Collisions::CheckCollisionTop(const vec2& pos)
    {
        TileType type = TileType::None;

        // Check top-left
        type = checkCollisionAtOffset(pos, vec2(0, 0));
        if (type != TileType::None) return type;

        // Check top-right
        type = checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, 0));
        return type;
    }

    TileType Collisions::checkCollisionAtOffset(const vec2& pos, const vec2& offset)
    {
        vec2 adjusted_pos = pos + offset;
        auto tile = tilemap.tile_at(adjusted_pos);
        return (tile.type != TileType::None) ? tile.type : TileType::None;
    }

    void Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
    {
        TileType CheckLeft = CheckCollisionLeft({ new_pos.x, player.position.y });
        TileType CheckRight = CheckCollisionRight({ new_pos.x, player.position.y });
        TileType CheckBottom = CheckCollisionBottom({ player.position.x, new_pos.y + player.velocity.y });
        TileType CheckTop = CheckCollisionTop({ player.position.x, new_pos.y + player.velocity.y});

        bool isNoneX = (CheckLeft == TileType::None || CheckRight == TileType::None);
        bool isNoneY = (CheckBottom == TileType::None);
        bool isDamage = (CheckLeft == TileType::Damage || CheckRight == TileType::Damage || CheckBottom == TileType::Damage || CheckTop == TileType::Damage || ai_follow.isTouchingPlayer() || (ai_patrol.isTouchingPlayer() && !ai_patrol.isAILowerThanPlayer || ai_copy.isTouchingPlayer()));
        bool isEnd = bell.touchedPlayer;
        bool isCollision = (CheckLeft == TileType::Collision || CheckRight == TileType::Collision || CheckBottom == TileType::Collision || CheckTop==TileType::Collision);
        bool isIce = (CheckBottom == TileType::Ice || CheckTop == TileType::Ice);

        bool FallLight = player.velocity.y >= trigger_fall_light && player.velocity.y < trigger_fall_normal;
        bool FallNormal = player.velocity.y >= trigger_fall_normal && player.velocity.y < trigger_fall_hard;
        bool FallHard = player.velocity.y >= trigger_fall_hard;

        // SFX: if falling from a high distance play <snd_fall_strong.wav>, otherwise from a smaller one play <snd_fall.wav> and if even smaller don't play any SFX.
        if ((CheckBottom == TileType::Collision || CheckBottom == TileType::Ice) && FallLight) 
        {
            //printf("fall light: %.0f\n", player.velocity.y);
            bouncing_force = 1.0f;
        }
        if ((CheckBottom == TileType::Collision || CheckBottom == TileType::Ice) && FallNormal) 
        {
            gamesound.playSound(gamesound.snd_fall);
            //printf("fall normal: %.0f\n", player.velocity.y);
            bouncing_force = 1.5f;
        }
        if ((CheckBottom == TileType::Collision || CheckBottom == TileType::Ice) && FallHard) 
        {
            gamesound.playSound(gamesound.snd_fall_strong);
            //printf("fall hard: %.0f\n", player.velocity.y);
            bouncing_force = 10.0f;
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
            bell.touchedPlayer = false;
        }
        else if (isCollision || isIce)
        {
            player.friction = isIce ? 0.0f : 0.05f;
            player.velocity.y = 0;
            player.position.y = (new_pos.y > player.position.y) ? player.position.y : new_pos.y;
        }

        if (isIce)
        {
            isOnIce = true;
        }
        else
        {
            isOnIce = false;
        }

        if (walls_collected > 0)
        {
            walls_collected--;

            player.velocity.x = -player.velocity.x; 
            player.velocity.x += (player.velocity.x >= 0) ? wall_force : -wall_force;
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

        if (CheckLeft || CheckRight)
        {
            float norm = sqrtf(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
            float angle = acosf(player.velocity.x / norm);

            player.velocity.x = -norm * cos(angle);
            player.velocity.y = norm * sin(angle);

            // Apply the power loss for the sides collisions
            player.velocity.x *= powf(player.ENERGY_LOSS, 2);
        }
        //printf("Bottom: %d, VelY: %f\n", (int)CheckBottom, player.velocity.y);
        if (CheckBottom)
        {
            //printf("check bottom\n");
            float norm = sqrtf(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
            float angle = acosf(player.velocity.x / norm);

            player.velocity.x = norm * cos(angle);
            player.velocity.y = -norm * sin(angle);

            // Apply the power loss for the bottom collisions
            player.velocity.y *= powf(player.ENERGY_LOSS, 2);

            // Threshold of 0.5 to the velocity.y to prevent the player from bouncing when on the ground with a low velocity
            if (fabs(player.velocity.y) < 0.5f) player.velocity.y = 0.0f;
        }
    }

    void Collisions::drawSplash(Surface* screen, vec2 player_pos, float deltaTime)
    {
        if (!isOnIce) return;

        static float frame = 0.0f;
        const float animation_fps = 10.0f; 

        frame += animation_fps * deltaTime;
        if (frame >= 3.0f) frame -= 3.0f; 

        img_water_slide_right.SetFrame(frame); 
        img_water_slide_left.SetFrame(frame); 

        vec2 offset = vec2(
            img_water_slide_right.GetWidth() / 2 - player_img_width / 2,
            img_water_slide_right.GetHeight() / 2 - player_img_height / 2 + player.PLAYER_DRAW_OFFSET_Y + 1
        );

        vec2 draw_pos = player_pos + camera.getCamPos() + offset;

        if (player.velocity.x > 0)   img_water_slide_right.Draw(screen, draw_pos);
        else                         img_water_slide_left.Draw(screen, draw_pos);
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
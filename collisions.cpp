#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "collisions.h"
#include <cmath>

namespace Tmpl8
{
    Collisions::Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef, Level& levelRef, Camera& cameraRef, GameSound& gamesoundRef, AI_Patrol& ai_patrolRef, AI_Copy& ai_copyRef, Menu& menuRef) :
        player(playerRef), 
        tilemap(tilemapRef),
        ai_follow(ai_followRef),
        camera(cameraRef),
        gamesound(gamesoundRef),
        level(levelRef),
        ai_patrol(ai_patrolRef),
        ai_copy(ai_copyRef),
        menu(menuRef)
    {}

    Sprite img_water_slide_right(new Surface("assets/images/entities/img_water_slide_right.tga"), 3);
    Sprite img_water_slide_left(new Surface("assets/images/entities/img_water_slide_left.tga"), 3);

    TileType Collisions::checkCollisionBottom(const vec2& pos)
    {
        TileType type = TileType::None;

        // Check bottom left
        type = checkCollisionAtOffset(pos, vec2(0, hitbox_radius * 2));
        if (type != TileType::None) return type;

        // Check bottom right
        type = checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, hitbox_radius * 2));
        return type;
    }

    TileType Collisions::checkCollisionLeft(const vec2& pos)
    {
        TileType type = TileType::None;

        // Check top-left
        type = checkCollisionAtOffset(pos, vec2(0, 0));
        if (type != TileType::None) return type;

        // Check bottom-left
        type = checkCollisionAtOffset(pos, vec2(0, hitbox_radius * 2));
        return type;
    }

    TileType Collisions::checkCollisionRight(const vec2& pos)
    {
        TileType type = TileType::None;

        // Check top-right
        type = checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, 0));
        if (type != TileType::None) return type;

        // Check bottom-right
        type = checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, hitbox_radius * 2));
        return type;
    }

    TileType Collisions::checkCollisionTop(const vec2& pos)
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
        vec2 tiled_pos = vec2(floor(adjusted_pos.x / TILE_SIZE) * TILE_SIZE, floor(adjusted_pos.y / TILE_SIZE) * TILE_SIZE);
        auto tile = tilemap.map_collision[tiled_pos];
        return (tile != TileType::None) ? tile : TileType::None;
    }

    TileType Collisions::getCollisionType(vec2& new_pos)
    {
        TileType CheckLeft = checkCollisionLeft({ new_pos.x, player.position.y });
        TileType CheckRight = checkCollisionRight({ new_pos.x, player.position.y });
        TileType CheckBottom = checkCollisionBottom({ player.position.x, new_pos.y + player.velocity.y });
        TileType CheckTop = checkCollisionTop({ player.position.x, new_pos.y + player.velocity.y });

        printf("CheckLeft: %d, CheckRight: %d, CheckBottom: %d, CheckTop: %d\n",
            (int)CheckLeft, (int)CheckRight, (int)CheckBottom, (int)CheckTop);

        bool isNone = (CheckLeft == TileType::None || CheckRight == TileType::None || CheckBottom == TileType::None || CheckTop == TileType::None);
        bool isDamage = (CheckLeft == TileType::Damage || CheckRight == TileType::Damage || CheckBottom == TileType::Damage || CheckTop == TileType::Damage || ai_follow.isTouchingPlayer() || (ai_patrol.isTouchingPlayer() && !ai_patrol.isAILowerThanPlayer || ai_copy.isTouchingPlayer()));
        bool isCollision = (CheckLeft == TileType::Collision || CheckRight == TileType::Collision || CheckBottom == TileType::Collision || CheckTop == TileType::Collision);
        bool isIce = (CheckBottom == TileType::Ice || CheckTop == TileType::Ice);
    
        TileType type;
    
        if (isNone)             type = TileType::None;
        else if (isDamage)      type = TileType::Damage;
        else if (isCollision)   type = TileType::Collision;
        else if (isIce)         type = TileType::Ice;
    
        return type;
    }

    void Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
    {
        bool FallLight = player.velocity.y >= trigger_fall_light && player.velocity.y < trigger_fall_normal;
        bool FallNormal = player.velocity.y >= trigger_fall_normal && player.velocity.y < trigger_fall_hard;
        bool FallHard = player.velocity.y >= trigger_fall_hard;

        TileType collisionType = getCollisionType(new_pos);
        printf("Collision Type: %s (%d)\n",
            collisionType == TileType::None ? "None" :
            collisionType == TileType::Damage ? "Damage" :
            collisionType == TileType::Collision ? "Collision" :
            collisionType == TileType::Ice ? "Ice" : "Unknown",
            (int)collisionType);

        switch (getCollisionType(new_pos))
        {
        case TileType::None:
            player.position = new_pos;
            break;
        case TileType::Damage:
            level.loadLevel(tilemap.getCurrentLevel());
            gamesound.playSound(gamesound.snd_damage);
            camera.setShakeState(Camera::shakeConditions::Damage);
            menu.score -= 15.0f;
            break;
        case TileType::Collision:
            isOnIce = false;
            player.friction = 0.5f;
            player.velocity.y = 0;
            player.position.y = (new_pos.y > player.position.y) ? player.position.y : new_pos.y;
            break;
        case TileType::Ice:
            isOnIce = true;
            player.friction = 0.0f;
            player.velocity.y = 0;
            player.position.y = (new_pos.y > player.position.y) ? player.position.y : new_pos.y;
            break;
        }
    }

    bool Collisions::getJumpState(vec2& new_pos)
    {
        bool canPlayerJump = false;
        canPlayerJump = GetAsyncKeyState(VK_UP) && (getCollisionType(new_pos) == TileType::Collision || getCollisionType(new_pos) == TileType::Ice) && collectibles_collected > 0;

        TileType CheckBottom = checkCollisionBottom({ player.position.x, new_pos.y + player.velocity.y });

        bool isCollision = (CheckBottom == TileType::Collision);
        bool isIce = (CheckBottom == TileType::Ice);

        // The player can jump if they press up, touch the ground and have at least 1 collectible.
        canPlayerJump = GetAsyncKeyState(VK_UP) && (CheckBottom == 3 || CheckBottom == 4) && collectibles_collected > 0;

        return canPlayerJump;
        // return GetAsyncKeyState(VK_UP) && (getCollisionType(new_pos) == TileType::Collision || getCollisionType(new_pos) == TileType::Ice) && collectibles_collected > 0;
    }

    void Collisions::applyBouncingPhysics(vec2& new_pos)
    {
        bool CheckLeft = checkCollisionLeft(vec2{ new_pos.x + player.velocity.x, new_pos.y }) != TileType::None;
        bool CheckRight = checkCollisionRight(vec2{ new_pos.x + player.velocity.x, new_pos.y }) != TileType::None;
        bool CheckBottom = checkCollisionBottom(vec2{ new_pos.x, new_pos.y + player.velocity.y }) != TileType::None;
        bool CheckTop = checkCollisionTop(vec2{ new_pos.x, new_pos.y + player.velocity.y }) != TileType::None;

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
        if (CheckBottom ||CheckTop)
        {
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
        if (getCollisionType(player_pos) != TileType::Ice) return;

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



//if ((CheckBottom == TileType::Collision && fabs(player.velocity.x) > 2.0f))
//{
//    gamesound.playRollingSound(gamesound.snd_rolling);
//}
//else
//{
//    gamesound.stopRollingSound();
//}
// 
// SFX: if falling from a high distance play <snd_fall_strong.wav>, otherwise from a smaller one play <snd_fall.wav> and if even smaller don't play any SFX.
//if ((TileType::Collision || TileType::Ice) && FallLight) 
//{
//    printf("fall light: %.0f\n", player.velocity.y);
//    bouncing_force = 1.0f;
//}
//if ((TileType::Collision || TileType::Ice) && FallNormal) 
//{
//    gamesound.playSound(gamesound.snd_fall);
//    printf("fall normal: %.0f\n", player.velocity.y);
//    bouncing_force = 1.5f;
//}
//if ((TileType::Collision || TileType::Ice) && FallHard) 
//{
//    gamesound.playSound(gamesound.snd_fall_strong);
//    printf("fall hard: %.0f\n", player.velocity.y);
//    bouncing_force = 10.0f;
//    camera.setShakeState(Camera::shakeConditions::FallHard);
//}

/*  + OLD COLLISION CHECK SYSTEM (for documentation purpose)

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
*/
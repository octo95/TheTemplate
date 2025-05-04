#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "collisions.h"
#include <cmath>

namespace Tmpl8
{
    Collisions::Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef, Level& levelRef, Camera& cameraRef, GameSound& gamesoundRef, AI_Patrol& ai_patrolRef, AI_Copy& ai_copyRef, Menu& menuRef) :
        player(playerRef),
        tilemap(tilemapRef),
        ai_follow(ai_followRef),
        collectible(collectibleRef),
        level(levelRef),
        camera(cameraRef),
        gamesound(gamesoundRef),
        ai_patrol(ai_patrolRef),
        ai_copy(ai_copyRef),
        menu(menuRef)
    {
    }

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

    void Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
    {
        TileType CheckLeft = checkCollisionLeft({ new_pos.x, player.position.y });
        TileType CheckRight = checkCollisionRight({ new_pos.x, player.position.y });
        TileType CheckBottom = checkCollisionBottom({ player.position.x, new_pos.y + player.velocity.y });
        TileType CheckTop = checkCollisionTop({ player.position.x, new_pos.y + player.velocity.y });

        bool isNoneX = (CheckLeft == TileType::None || CheckRight == TileType::None);
        bool isNoneY = (CheckBottom == TileType::None);
        bool isDamage = (CheckLeft == TileType::Damage || CheckRight == TileType::Damage || CheckBottom == TileType::Damage || CheckTop == TileType::Damage || ai_follow.isTouchingPlayer() || (ai_patrol.isTouchingPlayer() && !ai_patrol.isAILowerThanPlayer || ai_copy.isTouchingPlayer()));
        bool isCollision = (CheckLeft == TileType::Collision || CheckRight == TileType::Collision || CheckBottom == TileType::Collision || CheckTop == TileType::Collision);
        bool isIce = (CheckBottom == TileType::Ice || CheckTop == TileType::Ice);

        bool FallLight = player.velocity.y >= trigger_fall_light && player.velocity.y < trigger_fall_normal;
        bool FallNormal = player.velocity.y >= trigger_fall_normal && player.velocity.y < trigger_fall_hard;
        bool FallHard = player.velocity.y >= trigger_fall_hard;

        if (isNoneX) player.position.x = new_pos.x;
        if (isNoneY) player.position.y = new_pos.y;
        if (isDamage)
        {
            level.loadLevel(tilemap.getCurrentLevel());
            gamesound.playSound(gamesound.snd_damage);
            camera.setShakeState(Camera::shakeConditions::Damage);
            menu.score -= 15.0f;
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



    }

    bool Collisions::getJumpState(vec2& new_pos)
    {
        bool canPlayerJump = false;
        TileType CheckBottom = checkCollisionBottom({ player.position.x, new_pos.y + player.velocity.y });

        // The player can jump if they press up, touch the ground and have at least 1 collectible.
        canPlayerJump = GetAsyncKeyState(VK_UP) && (CheckBottom == 3 || CheckBottom == 4);

        return canPlayerJump;
    }

    void Collisions::applyBouncingPhysics(vec2& new_pos)
    {
        bool CheckLeft = checkCollisionLeft(vec2{ new_pos.x + player.velocity.x, new_pos.y }) != TileType::None;
        bool CheckRight = checkCollisionRight(vec2{ new_pos.x + player.velocity.x, new_pos.y }) != TileType::None;
        bool CheckBottom = checkCollisionBottom(vec2{ new_pos.x, new_pos.y + player.velocity.y }) != TileType::None;

        float norm = sqrtf(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
        float angle = acosf(player.velocity.x / norm);

        if (CheckLeft || CheckRight)
        {
            player.velocity.x = -norm * cos(angle);
            player.velocity.y = norm * sin(angle);

            // Apply the power loss for the sides collisions
            player.velocity.x *= powf(player.ENERGY_LOSS, 2);
        }
        //printf("Bottom: %d, VelY: %f\n", (int)CheckBottom, player.velocity.y);
        if (CheckBottom)
        {

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

// AABB Version of the collisions (scrapped)
/*
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

    TileType Collisions::checkCollisionTL(const vec2& pos)
    {
        return checkCollisionAtOffset(pos, vec2(0, 0));
    }

    TileType Collisions::checkCollisionTR(const vec2& pos)
    {
        return checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, 0));
    }

    TileType Collisions::checkCollisionBR(const vec2& pos)
    {
        return checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, hitbox_radius * 2));
    }

    TileType Collisions::checkCollisionBL(const vec2& pos)
    {
        return checkCollisionAtOffset(pos, vec2(0, hitbox_radius * 2));
    }


    TileType Collisions::checkCollisionAtOffset(const vec2& pos, const vec2& offset)
    {
        vec2 adjusted_pos = pos + offset;
        vec2 tiled_pos = vec2(floor(adjusted_pos.x / TILE_SIZE) * TILE_SIZE, floor(adjusted_pos.y / TILE_SIZE) * TILE_SIZE);
        auto tile = tilemap.map_collision[tiled_pos];
        return (tile != TileType::None) ? tile : TileType::None;
    }
        const char* TileTypeToString(TileType type)
    {
        switch (type)
        {
        case TileType::None:       return "None";
        case TileType::Collision:  return "Collision";
        case TileType::Damage:     return "Damage";
        case TileType::Ice:        return "Ice";
        case TileType::End:        return "End";
        default:                   return "Unknown";
        }
    }

    TileType Collisions::getCollisionType(vec2& new_pos)
    {

        TileType CheckTL = checkCollisionTL(new_pos);
        TileType CheckTR = checkCollisionTR(new_pos);
        TileType CheckBR = checkCollisionBR(new_pos);
        TileType CheckBL = checkCollisionBL(new_pos);

        printf("-----------\n");
        printf("TL - %s\n", TileTypeToString(CheckTL));
        printf("TR - %s\n", TileTypeToString(CheckTR));
        printf("BR - %s\n", TileTypeToString(CheckBR));
        printf("BL - %s\n", TileTypeToString(CheckBL));

        bool isDamage = (
            CheckTL == TileType::Damage ||
            CheckTR == TileType::Damage ||
            CheckBL == TileType::Damage ||
            CheckBR == TileType::Damage ||
            ai_follow.isTouchingPlayer() ||
            ai_patrol.isTouchingPlayer() && !ai_patrolisAILowerThanPlayer()) ||
                ai_copy.isTouchingPlayer()
                );

                bool isNone = (
                    CheckTL == TileType::None ||
                    CheckTR == TileType::None ||
                    CheckBL == TileType::None ||
                    CheckBR == TileType::None
                    );

                bool isIce = (
                    CheckBL == TileType::Ice ||
                    CheckBR == TileType::Ice ||
                    CheckTL == TileType::Ice ||
                    CheckTR == TileType::Ice
                    );

                bool isCollision = (
                    CheckTL == TileType::Collision ||
                    CheckTR == TileType::Collision ||
                    CheckBL == TileType::Collision ||
                    CheckBR == TileType::Collision
                    );

                TileType type = TileType::None;
                bool isGrounded =

                    (CheckTL == 0 && CheckTR == 0 &&
                        CheckBL == 3 && CheckBR == 3) ||

                    (CheckTL == 3 && CheckTR == 0 &&
                        CheckBL == 3 && CheckBR == 3) ||

                    (CheckTL == 0 && CheckTR == 3 &&
                        CheckBL == 3 && CheckBR == 3) ||

                    (CheckTL == 0 && CheckTR == 0 &&
                        CheckBL == 3 && CheckBR == 0) ||

                    (CheckTL == 0 && CheckTR == 0 &&
                        CheckBL == 0 && CheckBR == 3);

                printf("Grounded: %d\n", isGrounded);

                if (isGrounded)
                {
                    // PRIORITY -> None : Player can input
                    if (isDamage)           type = TileType::Damage;
                    else if (isNone)        type = TileType::None;
                    else if (isIce)         type = TileType::Ice;
                    else if (isCollision)   type = TileType::Collision;
                }
                else
                {
                    // PRIORITY -> Collision : Player can't input
                    if (isDamage)           type = TileType::Damage;
                    else if (isIce)         type = TileType::Ice;
                    else if (isCollision)   type = TileType::Collision;
                    else if (isNone)        type = TileType::None;
                }

                return type;
                // The order at which they are checked represents the priority order, so we have the priority: Damage > None > Ice > Collision
    }

    void Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
    {
        bool FallLight = player.velocity.y >= trigger_fall_light && player.velocity.y < trigger_fall_normal;
        bool FallNormal = player.velocity.y >= trigger_fall_normal && player.velocity.y < trigger_fall_hard;
        bool FallHard = player.velocity.y >= trigger_fall_hard;

        printf("RETURNED TYPE: %s\n", TileTypeToString(getCollisionType(new_pos)));
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
        TileType CheckTL = checkCollisionTL(new_pos);
        TileType CheckTR = checkCollisionTR(new_pos);
        TileType CheckBR = checkCollisionBR(new_pos);
        TileType CheckBL = checkCollisionBL(new_pos);

        bool canJump = (CheckBL || CheckBR) != TileType::None && (CheckTL || CheckTR) == TileType::None;

        return canJump && GetAsyncKeyState(VK_UP);
    }

    void Collisions::applyBouncingPhysics(vec2& new_pos)
    {
        TileType CheckTL = checkCollisionTL(new_pos);
        TileType CheckTR = checkCollisionTR(new_pos);
        TileType CheckBR = checkCollisionBR(new_pos);
        TileType CheckBL = checkCollisionBL(new_pos);

        bool CheckX = ((CheckTL && CheckBL) || (CheckTR && CheckBR)) != TileType::None;
        bool CheckY = ((CheckBL && CheckBR) || (CheckTL && CheckTR)) != TileType::None;

        if (CheckX)
        {
            float norm = sqrtf(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
            float angle = acosf(player.velocity.x / norm);

            player.velocity.x = -norm * cos(angle);
            player.velocity.y = norm * sin(angle);

            // Apply the power loss for the sides collisions
            player.velocity.x *= powf(player.ENERGY_LOSS, 2);
        }
        //printf("Bottom: %d, VelY: %f\n", (int)CheckBottom, player.velocity.y);
        if (CheckY)
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


*/

// MIDLE EDGE Version of the collision (scrapped)
/*
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
    {
    }

    Sprite img_water_slide_right(new Surface("assets/images/entities/img_water_slide_right.tga"), 3);
    Sprite img_water_slide_left(new Surface("assets/images/entities/img_water_slide_left.tga"), 3);

    TileType Collisions::checkCollisionTop(const vec2& pos)
    {
        return checkCollisionAtOffset(pos, vec2(hitbox_radius, 0));  // Top center
    }

    TileType Collisions::checkCollisionRight(const vec2& pos)
    {
        return checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, hitbox_radius));  // Right center
    }

    TileType Collisions::checkCollisionBottom(const vec2& pos)
    {
        return checkCollisionAtOffset(pos, vec2(hitbox_radius, hitbox_radius * 2));  // Bottom center
    }

    TileType Collisions::checkCollisionLeft(const vec2& pos)
    {
        return checkCollisionAtOffset(pos, vec2(0, hitbox_radius));  // Left center
    }

    TileType Collisions::checkCollisionAtOffset(const vec2& pos, const vec2& offset)
    {
        vec2 adjusted_pos = pos + offset;
        vec2 tiled_pos = vec2(floor(adjusted_pos.x / TILE_SIZE) * TILE_SIZE, floor(adjusted_pos.y / TILE_SIZE) * TILE_SIZE);
        auto tile = tilemap.map_collision[tiled_pos];
        return (tile != TileType::None) ? tile : TileType::None;
    }

    const char* TileTypeToString(TileType type)
    {
        switch (type)
        {
        case TileType::None:       return "None";
        case TileType::Collision:  return "Collision";
        case TileType::Damage:     return "Damage";
        case TileType::Ice:        return "Ice";
        case TileType::End:        return "End";
        default:                   return "Unknown";
        }
    }

    TileType Collisions::getCollisionType(vec2& new_pos)
    {
        TileType CheckT = checkCollisionTop(new_pos);
        TileType CheckR = checkCollisionRight(new_pos);
        TileType CheckB = checkCollisionBottom(new_pos);
        TileType CheckL = checkCollisionLeft(new_pos);

        printf("-----------\n");
        printf("Top - %s\n", TileTypeToString(CheckT));
        printf("Right - %s\n", TileTypeToString(CheckR));
        printf("Bottom - %s\n", TileTypeToString(CheckB));
        printf("Left - %s\n", TileTypeToString(CheckL));

        bool isDamage = (
            CheckT == TileType::Damage ||
            CheckR == TileType::Damage ||
            CheckL == TileType::Damage ||
            CheckB == TileType::Damage ||
            ai_follow.isTouchingPlayer() ||
            ai_patrol.isTouchingPlayer() ||
                ai_copy.isTouchingPlayer()
                );

                bool isNone = (
                    CheckT == TileType::None ||
                    CheckR == TileType::None ||
                    CheckL == TileType::None ||
                    CheckB == TileType::None
                    );

                bool isIce = (
                    CheckL == TileType::Ice ||
                    CheckR == TileType::Ice ||
                    CheckT == TileType::Ice ||
                    CheckB == TileType::Ice
                    );

                bool isCollision = (
                    CheckT == TileType::Collision ||
                    CheckR == TileType::Collision ||
                    CheckL == TileType::Collision ||
                    CheckB == TileType::Collision
                    );

                TileType type = TileType::None;
                bool isGrounded =
                    (
                        CheckT == 0 &&
                        CheckL == 0 && CheckR == 0 &&
                        CheckB == 3
                        ) ||
                    (
                        CheckT == 0 &&
                        CheckL == 3 && CheckR == 0 &&
                        CheckB == 3
                        ) ||
                    (
                        CheckT == 0 &&
                        CheckL == 0 && CheckR == 3 &&
                        CheckB == 3
                        ) ||
                    (
                        CheckT == 0 &&          // <= If this happens I messed up somehow
                        CheckL == 3 && CheckR == 3 &&
                        CheckB == 3
                        );

                printf("Grounded: %d\n", isGrounded);

                if (isGrounded)
                {
                    // PRIORITY -> None : Player can input
                    if (isDamage)           type = TileType::Damage;    //
                    else if (isNone)        type = TileType::None;      // <== None
                    else if (isIce)         type = TileType::Ice;       //
                    else if (isCollision)   type = TileType::Collision; // <== Collision
                }
                else
                {
                    // PRIORITY -> Collision : Player can't input
                    if (isDamage)           type = TileType::Damage;    //
                    else if (isCollision)   type = TileType::Collision; // <== Collision
                    else if (isIce)         type = TileType::Ice;       //
                    else if (isNone)        type = TileType::None;      // <== None
                }

                return type;
                // The order at which they are checked represents the priority order, so we have the priority: Damage > None > Ice > Collision
    }

    void Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
    {
        bool FallLight = player.velocity.y >= trigger_fall_light && player.velocity.y < trigger_fall_normal;
        bool FallNormal = player.velocity.y >= trigger_fall_normal && player.velocity.y < trigger_fall_hard;
        bool FallHard = player.velocity.y >= trigger_fall_hard;

        printf("RETURNED TYPE: %s\n", TileTypeToString(getCollisionType(new_pos)));
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
        TileType CheckTop = checkCollisionTop(new_pos);
        TileType CheckRight = checkCollisionRight(new_pos);
        TileType CheckBottom = checkCollisionBottom(new_pos);
        TileType CheckLeft = checkCollisionLeft(new_pos);

        bool canJump = (CheckLeft || CheckBottom) != TileType::None && (CheckTop || CheckRight) == TileType::None;

        return canJump && GetAsyncKeyState(VK_UP);
    }

    void Collisions::applyBouncingPhysics(vec2& new_pos)
    {
        TileType CheckTop = checkCollisionTop(new_pos);
        TileType CheckRight = checkCollisionRight(new_pos);
        TileType CheckBottom = checkCollisionBottom(new_pos);
        TileType CheckLeft = checkCollisionLeft(new_pos);

        bool CheckX = ((CheckTop && CheckLeft) || (CheckRight && CheckBottom)) != TileType::None;
        bool CheckY = ((CheckLeft && CheckBottom) || (CheckTop && CheckRight)) != TileType::None;

        if (CheckX)
        {
            float norm = sqrtf(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
            float angle = acosf(player.velocity.x / norm);

            player.velocity.x = -norm * cos(angle);
            player.velocity.y = norm * sin(angle);

            // Apply the power loss for the sides collisions
            player.velocity.x *= powf(player.ENERGY_LOSS, 2);
        }

        if (CheckY)
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

        if (player.velocity.x > 0) img_water_slide_right.Draw(screen, draw_pos);
        else img_water_slide_left.Draw(screen, draw_pos);
    }

}
*/

// OTHER

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
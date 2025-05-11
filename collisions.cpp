#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "collisions.h"
#include <cmath>

namespace Tmpl8
{
    Collisions::Collisions(AIMap& ai_map, Camera& cameraRef, GameSound& gamesoundRef, Health& healthRef, Level& levelRef, Menu& menuRef, Player& playerRef, TileMap& tilemapRef) :
        ai_map(ai_map),
        camera(cameraRef),
        gamesound(gamesoundRef),
        health(healthRef),
        level(levelRef),
        menu(menuRef),
        player(playerRef),
        tilemap(tilemapRef)
    {
    }


    Sprite img_water_slide_right(new Surface("assets/images/entities/img_water_slide_right.tga"), 3);
    Sprite img_water_slide_left(new Surface("assets/images/entities/img_water_slide_left.tga"), 3);  

    vec2 Collisions::getPlayerTPos(const vec2& pos)
    {
        vec2 tpos = vec2(
            floor(pos.x / TILE_SIZE) * TILE_SIZE,
            floor(pos.y / TILE_SIZE) * TILE_SIZE
        );
        return tpos;
    }

    TileType Collisions::getTileCollision(const vec2& player_tpos, const vec2& offset)
    {
        TileType tile = tilemap.map_collision[player_tpos + offset];
        if (tile != None) return tile;
        return None;
    }

    TileType Collisions::checkCollisionT(const vec2& player_pos, bool left, bool right)
    {
        vec2 player_tpos = getPlayerTPos(player_pos);

        TileType left_tile = None;
        TileType right_tile = None;
        TileType middle_tile = None;

        bool touch_top = (player_pos.y - player_tpos.y) - player.hitbox_radius <= 0;
        bool touch_top_left = !left && (player_pos.x - player.hitbox_radius + 1) - player_tpos.x <= 0;
        bool touch_top_right = !right && (player_pos.x + player.hitbox_radius - 1) - player_tpos.x >= TILE_SIZE;

        vec2 offset_middle = vec2(0.0f, -TILE_SIZE);
        vec2 offset_left = vec2(-TILE_SIZE, -TILE_SIZE);
        vec2 offset_right = vec2(-TILE_SIZE, -TILE_SIZE);

        if (touch_top) 
        {
            middle_tile = getTileCollision(player_tpos, offset_middle);

            if (touch_top_left)  left_tile = getTileCollision(player_tpos, offset_left);
            if (touch_top_right) right_tile = getTileCollision(player_tpos, offset_right);
        };

        if (left_tile != None)      return left_tile;
        if (right_tile != None)     return right_tile;
        if (middle_tile != None)    return middle_tile;

        // If no collisions are detected, return None.
        return None;
    }

    TileType Collisions::checkCollisionB(const vec2& player_pos, bool left, bool right)
    {
        vec2 player_tpos = getPlayerTPos(player_pos);

        TileType left_tile = None;
        TileType right_tile = None;
        TileType middle_tile = None;

        vec2 offset_left = vec2(-TILE_SIZE, TILE_SIZE);
        vec2 offset_right = vec2(TILE_SIZE, TILE_SIZE);
        vec2 offset_middle = vec2(0.0f, TILE_SIZE);

        bool touch_bottom = player_pos.y - player_tpos.y + player.hitbox_radius >= TILE_SIZE;
        bool touch_bottom_left = !left && (player_pos.x - player.hitbox_radius + 1) - player_tpos.x <= 0;
        bool touch_bottom_right = !right && (player_pos.x + player.hitbox_radius - 1) - player_tpos.x >= TILE_SIZE;

        if (touch_bottom) 
        {
            middle_tile = getTileCollision(player_tpos, offset_middle);

            if (touch_bottom_left)  left_tile = getTileCollision(player_tpos, offset_left);
            if (touch_bottom_right) right_tile = getTileCollision(player_tpos, offset_right);
        };

        // Only enter damage if half of the body in it.
        if ((left_tile == Damage || right_tile == Damage) && left_tile != middle_tile && right_tile != middle_tile) {
            return middle_tile;
        }

        if (left_tile != None)      return left_tile;
        if (right_tile != None)     return right_tile;
        if (middle_tile != None)    return middle_tile;

        // If no collisions are detected, return None.
        return None;
    }

    TileType Collisions::checkCollisionL(const vec2& player_pos)
    {
        vec2 player_tpos = getPlayerTPos(player_pos);

        TileType middle_tile = None;
        TileType top_tile = None;
        TileType bottom_tile = None;

        vec2 offset_middle = vec2(-TILE_SIZE, 0.0f);
        vec2 offset_top = vec2(-TILE_SIZE, -TILE_SIZE);
        vec2 offset_bottom = vec2(-TILE_SIZE, TILE_SIZE);

        bool touch_left = (player_pos.x - player_tpos.x) - player.hitbox_radius <= 0;
        bool touch_left_top = (player_pos.y - player.hitbox_radius + 1) - player_tpos.y <= 0;
        bool touch_left_bottom = (player_pos.y + player.hitbox_radius - 1) - player_tpos.y >= TILE_SIZE;

        if (touch_left) 
        {
            if (touch_left_top)     top_tile = getTileCollision(player_tpos, offset_top);
            if (touch_left_bottom)  bottom_tile = getTileCollision(player_tpos, offset_bottom);

            middle_tile = getTileCollision(player_tpos, offset_middle);
        }

        if (top_tile != None)       return top_tile;
        if (bottom_tile != None)    return bottom_tile;
        if (middle_tile != None)    return middle_tile;

        return None;
    }

    TileType Collisions::checkCollisionR(const vec2& player_pos)
    {
        vec2 player_tpos = getPlayerTPos(player_pos);

        TileType middle_tile = None;
        TileType top_tile = None;
        TileType bottom_tile = None;

        vec2 offset_middle = vec2(TILE_SIZE, 0.0f);
        vec2 offset_top = vec2(TILE_SIZE, -TILE_SIZE);
        vec2 offset_bottom = vec2(TILE_SIZE, TILE_SIZE);

        bool touch_right = (player_pos.x - player_tpos.x) + player.hitbox_radius >= TILE_SIZE;
        bool touch_right_top = (player_pos.y - player.hitbox_radius + 1) - player_tpos.y <= 0;
        bool touch_right_bottom = (player_pos.y + player.hitbox_radius - 1) - player_tpos.y >= TILE_SIZE;

        if (touch_right)
        {
            if (touch_right_top)     top_tile = getTileCollision(player_tpos, offset_top);
            if (touch_right_bottom)  bottom_tile = getTileCollision(player_tpos, offset_bottom);

            middle_tile = getTileCollision(player_tpos, offset_middle);
        }

        if (top_tile != None)       return top_tile;
        if (bottom_tile != None)    return bottom_tile;
        if (middle_tile != None)    return middle_tile;

        return None;
    }

    void Collisions::applyBouncingPhysics(
        vec2& new_pos,
        bool left,
        bool right,
        bool bottom,
        bool top
    )
    {
        float norm = sqrtf(powf(player.velocity.x, 2) + powf(player.velocity.y, 2));

        if ((bottom || top))
        {
            float angle = acosf(player.velocity.x / norm);

            if (fabs(player.velocity.y) > 3.5f) 
            {
                player.velocity.x = norm * cosf(angle);
                player.velocity.y = -norm * sinf(angle);

                // Apply the power loss for the sides collisions
                player.velocity.y *= powf(player.ENERGY_LOSS, 2);
                new_pos += player.velocity;
            }
            else if(!top) 
            {
                // Cancel gravity when on the floor
                player.velocity.y = 0.0f;
            }            
        }
    }

    bool Collisions::manageAICollisions()
    {
        for (AI_Copy& ai : ai_map.ai_copy_map)
        {
            if (ai.isTouchingPlayer(&img_ai_copy))
            {
                return true;
            }
        }
        
        for (AI_Follow& ai : ai_map.ai_follow_map)
        {
            if (ai.isTouchingPlayer(&img_ai_follow))
            {
                return true;
            }
        }

        for (AI_Patrol& ai : ai_map.ai_patrol_map)
        {
            if (ai.isTouchingPlayer(&img_ai_patrol) && !ai.isAILowerThanPlayer)
            {
                return true;
            }
        }

        return false;
    }

    void Collisions::manageCollisions(vec2& new_pos)
    {
        TileType CheckL = checkCollisionL(new_pos);
        TileType CheckR = checkCollisionR(new_pos);
        TileType CheckB = checkCollisionB(new_pos, CheckL != None, CheckR != None);
        TileType CheckT = checkCollisionT(new_pos, CheckL != None, CheckR != None);

        bool block_x = (
            (CheckL != None && new_pos.x < player.position.x) ||
            (CheckR != None && new_pos.x > player.position.x)
        );

        bool block_y = (
            (CheckT != None && new_pos.y < player.position.y) ||
            (CheckB != None && new_pos.y > player.position.y)
        );

        if (!block_x) player.position.x = new_pos.x;
        if (!block_y) player.position.y = new_pos.y;
        
        bool isIce = (CheckB == Ice);
        bool isDamage = (CheckB == Damage || manageAICollisions());
        bool isCollision = (CheckL == Collision || CheckR == Collision || CheckB == Collision || CheckT == Collision);

        applyCollisionsSFX(CheckB, isIce);
        applyBouncingPhysics(new_pos, CheckL != None, CheckR != None, CheckB != None, CheckT != None);
        applyCollisions(isDamage, isIce, isCollision);
    }

    void Collisions::applyCollisions(bool isDamage, bool isIce, bool isCollision)
    {
        if (isDamage)
        {
            level.loadLevel(tilemap.getCurrentLevel());
            gamesound.playSound(gamesound.snd_damage);
            camera.setShakeState(Camera::shakeConditions::Damage);
            menu.score -= 20 * menu.difficulty;
            health.player_hp--;
            if (health.player_hp == 0) health.player_killed = true;
        }

        if (isIce)
        {
            isOnIce = true;
            player.friction = 0.0f;
            player.max_horizontal_speed = 3.0f;
        }

        if (isCollision)
        {
            isOnIce = false;
            player.friction = 0.05f;
            player.max_horizontal_speed = 1.5f;
        }
    }

    bool Collisions::getJumpState(vec2& new_pos)
    {
        bool canPlayerJump = false;
        canPlayerJump = checkCollisionB(new_pos, checkCollisionL(new_pos) != None, checkCollisionR(new_pos) != None) != TileType::None;
        return canPlayerJump; 
    }

    void Collisions::drawSplash(Surface* screen, vec2 player_pos, float deltaTime)
    {
        if (checkCollisionB(player_pos, false, false) == None || !isOnIce) return;

        static float frame = 0.0f;
        const float animation_fps = 10.0f;
        
        frame += animation_fps * deltaTime;
        if (frame >= 3.0f) frame -= 3.0f;
        
        img_water_slide_right.SetFrame(static_cast<int>(frame));
        img_water_slide_left.SetFrame(static_cast<int>(frame));
        
        vec2 offset = vec2(
            -player.hitbox_radius,
            -player.hitbox_radius - 2.0f
        );
        
        vec2 draw_pos = player_pos + camera.getCamPos() + offset;
        
        if (player.velocity.x > 0)   img_water_slide_right.Draw(screen, draw_pos - vec2(player.hitbox_radius, 0.0f));
        else                         img_water_slide_left.Draw(screen, draw_pos - vec2(-player.hitbox_radius, 0.0f));
    }

    void Collisions::applyCollisionsSFX(bool bottom, bool isIce)
    {
        float trigger_fall_normal = 5.0f;
        float trigger_fall_hard = 7.0f;

        FallNormal = player.velocity.y >= trigger_fall_normal && player.velocity.y < trigger_fall_hard;
        FallHard = fabs(player.velocity.y) >= trigger_fall_hard;

        if (bottom && FallNormal)
        {
            gamesound.playSound(gamesound.snd_fall);
        }
        if (bottom && FallHard)
        {
            gamesound.playSound(gamesound.snd_fall_strong);
            camera.setShakeState(Camera::shakeConditions::FallHard);
        }

        // + LAGS THE GAME, DISABLED
        //if (bottom && isIce)
        //{
        //    gamesound.playRollingSound(gamesound.snd_slide);
        //}
        //else if (bottom && !isIce && fabs(player.velocity.x) > 0.5f)
        //{
        //    gamesound.playRollingSound(gamesound.snd_rolling);
        //}
        //else
        //{
        //    gamesound.stopRollingSound();
        //}
    }
}
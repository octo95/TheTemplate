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










    //TileType Collisions::CheckCollisionBottom(const vec2int& pos)
    //{
    //    TileType t_left = TileType::None;
    //    TileType t_right = TileType::None;
    //
    //    int clamp_pos_x = pos.x / TILE_radius * TILE_radius;
    //    int clamp_pos_y = pos.y / TILE_radius * TILE_radius;
    //
    //    if (((pos.y - clamp_pos_y) + hitbox_radius * 2) >= TILE_radius) {
    //        auto l = tilemap.tile_at(clamp_pos_x, pos.y + TILE_radius);
    //        if (l.type != TileType::None) t_left = l.type;
    //
    //        auto r = tilemap.tile_at((pos.x + (hitbox_radius * 2)) / TILE_radius * TILE_radius, pos.y + TILE_radius);
    //        if (r.type != TileType::None) t_right = r.type;
    //    }
    //
    //    // If the player is more than half on the left
    //    if ((t_left == TileType::Damage || t_left == TileType::End) && (pos.x - (pos.x / TILE_radius * TILE_radius)) < hitbox_radius) {
    //        return t_left;
    //    }
    //
    //    // If the player is more than half on the right
    //    if ((t_right == TileType::Damage || t_right == TileType::End) && (pos.x - (pos.x / TILE_radius * TILE_radius)) >= hitbox_radius) {
    //        return t_right;
    //    }
    //
    //    return (t_left == TileType::Collision || t_left == TileType::Ice) ? t_left : t_right;
    //}
    

    TileType Collisions::checkCollisionTop(const vec2& pos, bool left, bool right)
    {
        vec2 tile_origin = vec2(floor(pos.x / TILE_SIZE) * TILE_SIZE, floor(pos.y / TILE_SIZE) * TILE_SIZE);

        if (((pos.y - tile_origin.y) - hitbox_radius) <= 0) {

            // Check if overlapping on the left
            if (!left && (pos.x - hitbox_radius + 1) - tile_origin.x <= 0) { // Apply a tolerance of 1 pixel to avoid shenanigans 
                TileType tile = tilemap.map_collision[vec2(tile_origin.x - TILE_SIZE, tile_origin.y - TILE_SIZE)];
                if (tile != None) return tile;
            }

            // Check if overlapping on the right
            if (!right && (pos.x + hitbox_radius - 1) - tile_origin.x >= TILE_SIZE) {
                TileType tile = tilemap.map_collision[vec2(tile_origin.x + TILE_SIZE, tile_origin.y - TILE_SIZE)];
                if (tile != None) return tile;
            }

            TileType tile = tilemap.map_collision[vec2(tile_origin.x, tile_origin.y - TILE_SIZE)];
            return tile;
        };

        return None;
    }

    TileType Collisions::checkCollisionBottom(const vec2& pos, bool left, bool right)
    {
        TileType left_tile = None;
        TileType right_tile = None;
        TileType middle_tile = None;

        vec2 tile_origin = vec2(floor(pos.x / TILE_SIZE) * TILE_SIZE, floor(pos.y / TILE_SIZE) * TILE_SIZE);

        if (((pos.y - tile_origin.y) + hitbox_radius) >= TILE_SIZE) {

            // Check if overlapping on the left
            if (!left && (pos.x - hitbox_radius + 1) - tile_origin.x <= 0) { // Apply a tolerance of 1 pixel to avoid shenanigans 
                TileType tile = tilemap.map_collision[vec2(tile_origin.x - TILE_SIZE, tile_origin.y + TILE_SIZE)];
                if (tile != None) left_tile = tile;
            }

            // Check if overlapping on the right
            if (!right && (pos.x + hitbox_radius - 1) - tile_origin.x >= TILE_SIZE) {
                TileType tile = tilemap.map_collision[vec2(tile_origin.x + TILE_SIZE, tile_origin.y + TILE_SIZE)];
                if(tile != None) right_tile = tile;
            }

            TileType tile = tilemap.map_collision[vec2(tile_origin.x, tile_origin.y + TILE_SIZE)];
            if (tile != None) middle_tile = tile;
        };

        // Only enter damage if half of the body in it
        if ((left_tile == Damage || right_tile == Damage) && left_tile != middle_tile && right_tile != middle_tile) {
            return middle_tile;
        }

        if (left_tile != None) return left_tile;
        if (right_tile != None) return right_tile;
        if (middle_tile != None) return middle_tile;

        return None;
    }

    TileType Collisions::checkCollisionLeft(const vec2& pos)
    {
        vec2 tile_origin = vec2(floor(pos.x / TILE_SIZE) * TILE_SIZE, floor(pos.y / TILE_SIZE) * TILE_SIZE);

        if (((pos.x - tile_origin.x) - hitbox_radius) <= 0) {

            // Check if overlapping on the top
            if ((pos.y - hitbox_radius + 1) - tile_origin.y <= 0) {
                TileType tile = tilemap.map_collision[vec2(tile_origin.x - TILE_SIZE, tile_origin.y - TILE_SIZE)];
                if (tile != None) return tile;
            }

            // Check if overlapping on the bottom
            if ((pos.y + hitbox_radius - 1) - tile_origin.y >= TILE_SIZE) {
                TileType tile = tilemap.map_collision[vec2(tile_origin.x - TILE_SIZE, tile_origin.y + TILE_SIZE)];
                if (tile != None) return tile;
            }

            TileType tile = tilemap.map_collision[vec2(tile_origin.x - TILE_SIZE, tile_origin.y)];
            return tile;
        };

        return None;
    }

    TileType Collisions::checkCollisionRight(const vec2& pos)
    {
        vec2 tile_origin = vec2(floor(pos.x / TILE_SIZE) * TILE_SIZE, floor(pos.y / TILE_SIZE) * TILE_SIZE);

        if (((pos.x - tile_origin.x) + hitbox_radius) >= TILE_SIZE) {

            // Check if overlapping on the top
            if ((pos.y - hitbox_radius + 1) - tile_origin.y <= 0) {
                TileType tile = tilemap.map_collision[vec2(tile_origin.x + TILE_SIZE, tile_origin.y - TILE_SIZE)];
                if (tile != None) return tile;
            }

            // Check if overlapping on the bottom
            if ((pos.y + hitbox_radius - 1) - tile_origin.y >= TILE_SIZE) {
                TileType tile = tilemap.map_collision[vec2(tile_origin.x + TILE_SIZE, tile_origin.y + TILE_SIZE)];
                if (tile != None) return tile;
            }

            TileType tile = tilemap.map_collision[vec2(tile_origin.x + TILE_SIZE, tile_origin.y)];
            return tile;
        };

        return None;
    }

    TileType Collisions::checkCollisionAtOffset(const vec2& pos, const vec2& offset)
    {
        vec2 adjusted_pos = pos + offset;
        vec2 tiled_pos = vec2(floor(adjusted_pos.x / TILE_SIZE) * TILE_SIZE, floor(adjusted_pos.y / TILE_SIZE) * TILE_SIZE);
        auto tile = tilemap.map_collision[tiled_pos];
        return (tile != TileType::None) ? tile : TileType::None;
    }

    void Collisions::applyBouncingPhysics(
        vec2& new_pos,
        bool left,
        bool right,
        bool bottom,
        bool top
    )
    {
        float norm = sqrtf(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));

        if ((bottom || top))
        {
            float angle = acosf(player.velocity.x / norm);

            if (fabs(player.velocity.y) > 3.5f) {
                player.velocity.x = norm * cos(angle);
                player.velocity.y = -norm * sin(angle);

                // Apply the power loss for the sides collisions
                player.velocity.y *= powf(player.ENERGY_LOSS, 2);
                new_pos += player.velocity;
            }
            else if(!top) {
                // Cancel gravity when on the floor
                player.velocity.y = 0.0f;
            }            
        }
    }

    void Collisions::manageCollisions(vec2& new_pos)
    {
        TileType CheckL = checkCollisionLeft(new_pos);
        TileType CheckR = checkCollisionRight(new_pos);
        TileType CheckB = checkCollisionBottom(new_pos, CheckL != None, CheckR != None);
        TileType CheckT = checkCollisionTop(new_pos, CheckL != None, CheckR != None);

        // Block on collisions
        player.position.x = (CheckL != None || CheckR != None) ? 
            (((new_pos.x < player.position.x && CheckL != None) || (new_pos.x > player.position.x && CheckR != None)) ? player.position.x : new_pos.x)
            : new_pos.x;
        player.position.y = (CheckB != None || CheckT != None) ? 
            (((new_pos.y < player.position.y && CheckT != None) || (new_pos.y > player.position.y && CheckB != None)) ? player.position.y : new_pos.y)
            : new_pos.y;
        
        applyBouncingPhysics(
            new_pos,
            CheckL != None,
            CheckR != None,
            CheckB != None,
            CheckT != None
        );

        bool isDamage = 
        (
            CheckL == Damage ||
            CheckR == Damage ||
            CheckB == Damage ||
            CheckT == Damage ||
            ai_follow.isTouchingPlayer() ||
            ai_patrol.isTouchingPlayer() && !ai_patrol.isAILowerThanPlayer ||
            ai_copy.isTouchingPlayer()
        );

        bool isIce =
        (
            CheckL == Ice ||
            CheckR == Ice ||
            CheckB == Ice ||
            CheckT == Ice
        );

        bool isCollision =
        (
            CheckL == Collision ||
            CheckR == Collision ||
            CheckB == Collision ||
            CheckT == Collision
        );
        
        if (isDamage)
        {
            level.loadLevel(tilemap.getCurrentLevel());
            gamesound.playSound(gamesound.snd_damage);
            camera.setShakeState(Camera::shakeConditions::Damage);
            menu.score -= 15.0f;
        }

        if(isIce)
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
        canPlayerJump = checkCollisionBottom(new_pos, checkCollisionLeft(new_pos) != None, checkCollisionRight(new_pos) != None) != TileType::None;
        return canPlayerJump; 
    }

    void Collisions::drawSplash(Surface* screen, vec2 player_pos, float deltaTime)
    {
        if (!isOnIce) return;
        printf("aaa");

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
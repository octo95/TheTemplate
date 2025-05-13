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
    {}

    // Importing the sprites for the slide collision effect
    Sprite img_water_slide_right(new Surface("assets/images/entities/img_water_slide_right.tga"), 3);
    Sprite img_water_slide_left(new Surface("assets/images/entities/img_water_slide_left.tga"), 3);  

    // Helper function to convert the player's coordinates to tile coordinates for grid snapping
    vec2 Collisions::getPlayerTPos(const vec2& pos)
    {
        vec2 tpos = vec2(
            floor(pos.x / TILE_SIZE) * TILE_SIZE,
            floor(pos.y / TILE_SIZE) * TILE_SIZE
        );
        return tpos;
    }

    // Helper function to get the tile's type the player is touching at a determined offset.
    TileType Collisions::getTileCollision(const vec2& player_tpos, const vec2& offset)
    {
        return tilemap.map_collision[player_tpos + offset];
    }

    // Check the collisions for the top of the player.
    TileType Collisions::checkCollisionT(const vec2& player_pos, bool left, bool right)
    {
        // Gather the tile position of the player
        vec2 player_tpos = getPlayerTPos(player_pos);

        // Seperate the logic in 3 checks on the top: left, middle, right
        TileType left_tile = None;
        TileType right_tile = None;
        TileType middle_tile = None;

        // Do we enter the tile top from the middle.
        bool touch_top = (player_pos.y - player_tpos.y) - player.hitbox_radius <= 0;

        // Do we enter the tile from the left or right.
        bool overlap_tile_left = left && (player_pos.x - player.hitbox_radius + 1) - player_tpos.x <= 0;
        bool overlap_tile_right = right && (player_pos.x + player.hitbox_radius - 1) - player_tpos.x >= TILE_SIZE;

        // Determine the offsets to use to check the tiles at the desired offsets (left/middle/right)
        vec2 offset_middle = vec2(0.0f, -TILE_SIZE);
        vec2 offset_left = vec2(-TILE_SIZE, -TILE_SIZE);
        vec2 offset_right = vec2(-TILE_SIZE, -TILE_SIZE);

        // If we touch the tile on top, we want to check if we overlap on the
        // left or right to know which tile we want to return.
        if (touch_top) 
        {
            // By default, will always touch at least the middle if touches the top.
            middle_tile = getTileCollision(player_tpos, offset_middle);

            if (overlap_tile_left)  left_tile = getTileCollision(player_tpos, offset_left);
            if (overlap_tile_right) right_tile = getTileCollision(player_tpos, offset_right);
        };

        // Return the type of the tile that detects a collision.
        if (left_tile != None)      return left_tile;
        if (right_tile != None)     return right_tile;
        if (middle_tile != None)    return middle_tile;

        // If no collisions are detected, return None.
        return None;
    }

    TileType Collisions::checkCollisionB(const vec2& player_pos, bool left, bool right)
    {
        // Follows the same logic as the other checkCollision(..)
        vec2 player_tpos = getPlayerTPos(player_pos);

        TileType left_tile = None;
        TileType right_tile = None;
        TileType middle_tile = None;

        vec2 offset_left = vec2(-TILE_SIZE, TILE_SIZE);
        vec2 offset_right = vec2(TILE_SIZE, TILE_SIZE);
        vec2 offset_middle = vec2(0.0f, TILE_SIZE);

        bool touch_bottom = player_pos.y - player_tpos.y + player.hitbox_radius >= TILE_SIZE;
        bool overlap_tile_left = left && (player_pos.x - player.hitbox_radius + 1) - player_tpos.x <= 0;
        bool overlap_tile_right = right && (player_pos.x + player.hitbox_radius - 1) - player_tpos.x >= TILE_SIZE;

        if (touch_bottom) 
        {
            middle_tile = getTileCollision(player_tpos, offset_middle);

            if (overlap_tile_left)  left_tile = getTileCollision(player_tpos, offset_left);
            if (overlap_tile_right) right_tile = getTileCollision(player_tpos, offset_right);
        };

        // Only enter damage if half of the body in it for a bottom check.
        if ((left_tile == Damage || right_tile == Damage) && left_tile != middle_tile && right_tile != middle_tile) {
            return middle_tile;
        }

        if (left_tile != None)      return left_tile;
        if (right_tile != None)     return right_tile;
        if (middle_tile != None)    return middle_tile;

        return None;
    }

    TileType Collisions::checkCollisionL(const vec2& player_pos)
    {
        // Follows the same logic as the other checkCollision(..)
        vec2 player_tpos = getPlayerTPos(player_pos);

        TileType middle_tile = None;
        TileType top_tile = None;
        TileType bottom_tile = None;

        vec2 offset_middle = vec2(-TILE_SIZE, 0.0f);
        vec2 offset_top = vec2(-TILE_SIZE, -TILE_SIZE);
        vec2 offset_bottom = vec2(-TILE_SIZE, TILE_SIZE);

        bool touch_left = (player_pos.x - player_tpos.x) - player.hitbox_radius <= 0;
        bool overlap_tile_top = (player_pos.y - player.hitbox_radius + 1) - player_tpos.y <= 0;
        bool overlap_tile_bottom = (player_pos.y + player.hitbox_radius - 1) - player_tpos.y >= TILE_SIZE;

        if (touch_left) 
        {
            if (overlap_tile_top)     top_tile = getTileCollision(player_tpos, offset_top);
            if (overlap_tile_bottom)  bottom_tile = getTileCollision(player_tpos, offset_bottom);

            middle_tile = getTileCollision(player_tpos, offset_middle);
        }

        if (top_tile != None)       return top_tile;
        if (bottom_tile != None)    return bottom_tile;
        if (middle_tile != None)    return middle_tile;

        return None;
    }

    TileType Collisions::checkCollisionR(const vec2& player_pos)
    {
        // Follows the same logic as the other checkCollision(..)
        vec2 player_tpos = getPlayerTPos(player_pos);

        TileType middle_tile = None;
        TileType top_tile = None;
        TileType bottom_tile = None;

        vec2 offset_middle = vec2(TILE_SIZE, 0.0f);
        vec2 offset_top = vec2(TILE_SIZE, -TILE_SIZE);
        vec2 offset_bottom = vec2(TILE_SIZE, TILE_SIZE);

        bool touch_right = (player_pos.x - player_tpos.x) + player.hitbox_radius >= TILE_SIZE;
        bool overlap_tile_top = (player_pos.y - player.hitbox_radius + 1) - player_tpos.y <= 0;
        bool overlap_tile_bottom = (player_pos.y + player.hitbox_radius - 1) - player_tpos.y >= TILE_SIZE;

        if (touch_right)
        {
            if (overlap_tile_top)     top_tile = getTileCollision(player_tpos, offset_top);
            if (overlap_tile_bottom)  bottom_tile = getTileCollision(player_tpos, offset_bottom);

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
        // Get the norm of the velocity.
        float norm = sqrtf(powf(player.velocity.x, 2) + powf(player.velocity.y, 2));

        if ((bottom || top))
        {
            // By trigonometry: cos(angle) = vel.x / norm => angle = arcos(vel.x / norm)
            float angle = acosf(player.velocity.x / norm);

            // Apply the bouncing physics only if the player reaches a high enough vertical velocity
            if (fabs(player.velocity.y) > 3.5f) 
            {
                // Determine the velocity by trigonometry.
                player.velocity.x = norm * cosf(angle);
                player.velocity.y = -norm * sinf(angle);

                // Apply power loss.
                player.velocity.y *= powf(player.ENERGY_LOSS, 2);

                // Once the physics calculations done, we can update the player's new position with the newly calculated velocity.
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
        // Goes through all the active AIs and checks if there is collision with the player.
        // If there is, we return true which will be used to apply damage to the player in manageCollisions(...)

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
        // Gather the collision checks: what TileType each side of the player's hitbox detects.
        TileType CheckL = checkCollisionL(new_pos);
        TileType CheckR = checkCollisionR(new_pos);
        TileType CheckB = checkCollisionB(new_pos, CheckL != None, CheckR != None);
        TileType CheckT = checkCollisionT(new_pos, CheckL != None, CheckR != None);


        // If the player is stuck on a wall either on the top, left or right, push them back slightly to avoid sticking to walls.
        float push_back = 1.0f;
        if (CheckL != None && CheckB != None && CheckT == None)         // Unstuck left.
        {
            player.position.x += push_back; 
            new_pos.x = player.position.x;
        }
        else if (CheckR != None && CheckB != None && CheckT == None)    // Unstuck right.
        {
            player.position.x -= push_back;
            new_pos.x = player.position.x;
        }
        else if (CheckT != None && CheckB == None)                      // Unstuck top.
        {
            player.jumping = false;
            player.velocity.y = 0.0f;
            player.position.y += push_back;
            new_pos.y = player.position.y;
        }

        // If the player touches a side and enters it, block the player.
        bool block_x = (
            (CheckL != None && new_pos.x < player.position.x) ||
            (CheckR != None && new_pos.x > player.position.x)
        );
        if (!block_x) player.position.x = new_pos.x;

        // If the player touches top or bottom and enters it, block the player.
        bool block_y = (
            (CheckT != None && new_pos.y < player.position.y) ||
            (CheckB != None && new_pos.y > player.position.y)
        );
        if (!block_y) player.position.y = new_pos.y;

        // Apply ice sliding physics if the player touches a <TileType::Ice> from the bottom.
        bool isIce = (CheckB == Ice);

        // Apply damage if the player touches a <TileType::Damage> from the bottom or if an AI enemy touches them.
        bool isDamage = (CheckB == Damage || manageAICollisions());

        // Apply collision if any side touches a <TileType::Collision>.
        bool isCollision = (CheckL == Collision || CheckR == Collision || CheckB == Collision || CheckT == Collision);

        // Apply SFX, physics and collision management.
        applyCollisionsSFX(CheckB, isIce);
        applyBouncingPhysics(new_pos, CheckL != None, CheckR != None, CheckB != None, CheckT != None);
        applyCollisions(isDamage, isIce, isCollision);
    }

    void Collisions::applyCollisions(bool isDamage, bool isIce, bool isCollision)
    {
        // If the player gets damaged:
        /*----------------------------
        * - Reload the level.
        * - Play a damage SFX.
        * - Shake the camera.
        * - Reduce the score.
        * - Remove 1HP to the player.
        * - Set the player's state to dead if reaching 0 HP.
        */
        if (isDamage)
        {
            level.loadLevel(tilemap.getCurrentLevel());
            gamesound.playSound(gamesound.snd_damage);
            camera.setShakeState(Camera::shakeConditions::Damage);
            menu.addScore(-20);
            health.player_hp--;
            if (health.player_hp == 0) health.player_killed = true;
        }

        // If the player touches ice:
        /*----------------------------
        * - Set the Ice state to true to draw the splash effect.
        * - Set the friction really low to make the player slide.
        * - Increase the max_horizontal_speed to increase the sliding effect.
        */
        if (isIce)
        {
            isOnIce = true;
            player.friction = 0.005f;
            player.max_horizontal_speed = 4.0f;
        }

        // If the player touches a collision:
        /*------------------------------------
        * - Set the Ice state to false to not draw the splash effect.
        * - Set the friction to 0.05 to make the player stop sliding after some time.
        * - Set the max_horizontal_speed to its default value.
        */
        if (isCollision)
        {
            isOnIce = false;
            player.friction = 0.1f;
            player.max_horizontal_speed = 2.5f;
        }
    }

    bool Collisions::getJumpState(vec2& new_pos)
    {
        // The player can jump if they are on the ground.
        return checkCollisionB(new_pos, checkCollisionL(new_pos) != None, checkCollisionR(new_pos) != None) != TileType::None;
    }

    void Collisions::drawSplash(Surface* screen, vec2 player_pos, float deltaTime)
    {
        // If the player is in the air or is not on Ice, don't draw anything.
        if (checkCollisionB(player_pos, false, false) == None || !isOnIce) return;

        static float frame = 0.0f;
        const float animation_fps = 10.0f;
        
        // Go through a loop timer to make the animation of the ice splash effect loop like a gif.
        frame += animation_fps * deltaTime;
        if (frame >= 3.0f) frame -= 3.0f;
        
        // Update the frame that will be drawn based on the current frame in the loop timer.
        img_water_slide_right.SetFrame(static_cast<int>(frame));
        img_water_slide_left.SetFrame(static_cast<int>(frame));
        
        // Apply an offset to draw the effect a bit to the side of the player.
        vec2 offset = vec2(
            -player.hitbox_radius,
            -player.hitbox_radius - 2.0f
        );
        
        vec2 draw_pos = player_pos + camera.getCamPos() + offset;
        
        // If the player's horizontal velocity is positive, the player is going right and we can draw the effect to the right, otherwise, draw it on the left.
        if (player.velocity.x > 0)   img_water_slide_right.Draw(screen, draw_pos - vec2(player.hitbox_radius, 0.0f));
        else                         img_water_slide_left.Draw(screen, draw_pos - vec2(-player.hitbox_radius, 0.0f));
    }

    void Collisions::applyCollisionsSFX(bool bottom, bool isIce)
    {
        float trigger_fall_normal = 5.0f;
        float trigger_fall_hard = 7.0f;

        FallNormal = player.velocity.y >= trigger_fall_normal && player.velocity.y < trigger_fall_hard;
        FallHard = fabs(player.velocity.y) >= trigger_fall_hard;

        // We have 2 different SFX depending on how hard the player falls.

        // If the player touches the ground with a velocity clamped within FallNormal, play <snd_fall>.
        if (bottom && FallNormal)
        {
            gamesound.playSound(gamesound.snd_fall);
        }
        // If the player touches the ground with a velocity clamped within FallHard, play <snd_fall_strong> and shake the camera.
        if (bottom && FallHard)
        {
            gamesound.playSound(gamesound.snd_fall_strong);
            camera.setShakeState(Camera::shakeConditions::FallHard);
        }
    }
}
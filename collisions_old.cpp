//#define WIN32_LEAN_AND_MEAN
//#include "windows.h"
//#include "collisions.h"
//#include <cmath>
//
//namespace Tmpl8
//{
//    Collisions::Collisions(Player& playerRef, TileMap& tilemapRef, AI_Follow& ai_followRef, Level& levelRef, Camera& cameraRef, GameSound& gamesoundRef, AI_Patrol& ai_patrolRef, AI_Copy& ai_copyRef, Menu& menuRef) :
//        player(playerRef),
//        tilemap(tilemapRef),
//        ai_follow(ai_followRef),
//        camera(cameraRef),
//        gamesound(gamesoundRef),
//        level(levelRef),
//        ai_patrol(ai_patrolRef),
//        ai_copy(ai_copyRef),
//        menu(menuRef)
//    {
//    }
//
//    Sprite img_water_slide_right(new Surface("assets/images/entities/img_water_slide_right.tga"), 3);
//    Sprite img_water_slide_left(new Surface("assets/images/entities/img_water_slide_left.tga"), 3);
//
//    TileType Collisions::checkCollisionTop(const vec2& pos)
//    {
//        return checkCollisionAtOffset(pos, vec2(hitbox_radius, 0));  // Top center
//    }
//
//    TileType Collisions::checkCollisionRight(const vec2& pos)
//    {
//        return checkCollisionAtOffset(pos, vec2(hitbox_radius * 2, hitbox_radius));  // Right center
//    }
//
//    TileType Collisions::checkCollisionBottom(const vec2& pos)
//    {
//        return checkCollisionAtOffset(pos, vec2(hitbox_radius, hitbox_radius * 2));  // Bottom center
//    }
//
//    TileType Collisions::checkCollisionLeft(const vec2& pos)
//    {
//        return checkCollisionAtOffset(pos, vec2(0, hitbox_radius));  // Left center
//    }
//
//    TileType Collisions::checkCollisionAtOffset(const vec2& pos, const vec2& offset)
//    {
//        vec2 adjusted_pos = pos + offset;
//        vec2 tiled_pos = vec2(floor(adjusted_pos.x / TILE_SIZE) * TILE_SIZE, floor(adjusted_pos.y / TILE_SIZE) * TILE_SIZE);
//        auto tile = tilemap.map_collision[tiled_pos];
//        return (tile != TileType::None) ? tile : TileType::None;
//    }
//
//    const char* TileTypeToString(TileType type)
//    {
//        switch (type)
//        {
//        case TileType::None:       return "None";
//        case TileType::Collision:  return "Collision";
//        case TileType::Damage:     return "Damage";
//        case TileType::Ice:        return "Ice";
//        case TileType::End:        return "End";
//        default:                   return "Unknown";
//        }
//    }
//    const char* TouchTypeToString(TouchType type)
//    {
//        switch (type)
//        {
//        case TouchType::None:       return "None";
//        case TouchType::NoneX:      return "NoneX";
//        case TouchType::NoneY:      return "NoneY";
//        case TouchType::Collision:  return "Collision";
//        case TouchType::Damage:     return "Damage";
//        case TouchType::Ice:        return "Ice";
//        default:                    return "Unknown";
//        }
//    }
//    void Collisions::manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles)
//    {
//        // Check tile types for each side of the player
//        TileType CheckT = checkCollisionTop(new_pos);
//        TileType CheckR = checkCollisionRight(new_pos);
//        TileType CheckB = checkCollisionBottom(new_pos);
//        TileType CheckL = checkCollisionLeft(new_pos);
//
//        printf("-----------\n");
//        printf("Top - %s\n", TileTypeToString(CheckT));
//        printf("Right - %s\n", TileTypeToString(CheckR));
//        printf("Bottom - %s\n", TileTypeToString(CheckB));
//        printf("Left - %s\n", TileTypeToString(CheckL));
//
//        // Check for damaging tiles and AI interaction
//        bool isDamage = (
//            CheckT == TileType::Damage ||
//            CheckR == TileType::Damage ||
//            CheckL == TileType::Damage ||
//            CheckB == TileType::Damage ||
//            ai_follow.isTouchingPlayer() ||
//            ai_patrol.isTouchingPlayer() ||
//            ai_copy.isTouchingPlayer()
//            );
//
//        // Check for tiles where the player can pass freely (None or Ice)
//        bool isNone = (
//            CheckT == TileType::None ||
//            CheckR == TileType::None ||
//            CheckL == TileType::None ||
//            CheckB == TileType::None
//            );
//
//        bool isIce = (
//            CheckL == TileType::Ice ||
//            CheckR == TileType::Ice ||
//            CheckT == TileType::Ice ||
//            CheckB == TileType::Ice
//            );
//
//        // Check for solid collision tiles
//        bool isCollision = (
//            CheckT == TileType::Collision ||
//            CheckR == TileType::Collision ||
//            CheckL == TileType::Collision ||
//            CheckB == TileType::Collision
//            );
//
//        // Determine if the player is grounded based on collision with the bottom
//        bool isGrounded = (CheckB == TileType::Collision);
//
//        printf("Grounded: %d\n", isGrounded);
//
//        TouchType type = TouchType::None;
//
//        // Decide the collision type based on whether the player is grounded or not
//        if (isGrounded)
//        {
//            // If the player is grounded, prioritize different types
//            if (isDamage)           type = TouchType::Damage;
//            else if (isNone)        type = TouchType::None;
//            else if (isIce)         type = TouchType::Ice;
//            else if (isCollision)   type = TouchType::Collision;
//        }
//        else
//        {
//            // If the player is not grounded, prioritize different collision types
//            if (isDamage)           type = TouchType::Damage;
//            else if (isCollision)   type = TouchType::Collision;
//            else if (isIce)         type = TouchType::Ice;
//            else if (isNone)        type = TouchType::None;
//        }
//
//        bool FallLight = player.velocity.y >= trigger_fall_light && player.velocity.y < trigger_fall_normal;
//        bool FallNormal = player.velocity.y >= trigger_fall_normal && player.velocity.y < trigger_fall_hard;
//        bool FallHard = player.velocity.y >= trigger_fall_hard;
//
//        printf("RETURNED TYPE: %s\n", TouchTypeToString(type));
//
//        switch (type)
//        {
//        case TouchType::None:
//            // Player is not colliding; update position freely
//            if (isGrounded)
//            {
//                player.position.x = new_pos.x;
//                player.velocity.y = 0;
//            }
//            else
//            {
//                player.position = new_pos;
//            }
//            break;
//
//        case TouchType::Damage:
//            // Handle damage, reset level, etc.
//            level.loadLevel(tilemap.getCurrentLevel());
//            gamesound.playSound(gamesound.snd_damage);
//            camera.setShakeState(Camera::shakeConditions::Damage);
//            menu.score -= 15.0f;
//            break;
//
//        case TouchType::Collision:
//            // Handle collision (top, bottom, left, right)
//            isOnIce = false;
//            player.friction = 0.5f;
//
//            if (CheckB == TileType::Collision)
//            {
//                // Standing on the ground
//                player.velocity.y = 0;
//                player.position.y = new_pos.y;  // Prevent falling through ground
//            }
//            else if (CheckT == TileType::Collision)
//            {
//                // Hitting the ceiling (invert vertical velocity to bounce)
//                player.velocity.y = -player.velocity.y;
//            }
//            else if (CheckL == TileType::Collision)
//            {
//                // Colliding with left wall (stop horizontal movement)
//                player.velocity.x = 0;
//                new_pos.x = player.position.x;  // Prevent moving through wall
//            }
//            else if (CheckR == TileType::Collision)
//            {
//                // Colliding with right wall (stop horizontal movement)
//                player.velocity.x = 0;
//                new_pos.x = player.position.x;  // Prevent moving through wall
//            }
//
//            // Update position after collision handling
//            player.position = new_pos;
//            break;
//
//        case TouchType::Ice:
//            // Ice behavior: low friction and sliding
//            isOnIce = true;
//            player.friction = 0.0f;
//            player.velocity.y = 0;
//            player.position.y = (new_pos.y > player.position.y) ? player.position.y : new_pos.y;
//            break;
//        }
//    }
//
//
//    bool Collisions::getJumpState(vec2& new_pos)
//    {
//        TileType CheckTop = checkCollisionTop(new_pos);
//        TileType CheckRight = checkCollisionRight(new_pos);
//        TileType CheckBottom = checkCollisionBottom(new_pos);
//        TileType CheckLeft = checkCollisionLeft(new_pos);
//
//        bool canJump = (CheckLeft || CheckBottom) != TileType::None && (CheckTop || CheckRight) == TileType::None;
//
//        return canJump && GetAsyncKeyState(VK_UP);
//    }
//
//    void Collisions::applyBouncingPhysics(vec2& new_pos)
//    {
//        //TileType CheckTop = checkCollisionTop(new_pos);
//        //TileType CheckRight = checkCollisionRight(new_pos);
//        //TileType CheckBottom = checkCollisionBottom(new_pos);
//        //TileType CheckLeft = checkCollisionLeft(new_pos);
//        //
//        //bool CheckX = ((CheckTop && CheckLeft) || (CheckRight && CheckBottom)) != TileType::None;
//        //bool CheckY = ((CheckLeft && CheckBottom) || (CheckTop && CheckRight)) != TileType::None;
//        //
//        //if (CheckX)
//        //{
//        //    float norm = sqrtf(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
//        //    float angle = acosf(player.velocity.x / norm);
//        //
//        //    player.velocity.x = -norm * cos(angle);
//        //    player.velocity.y = norm * sin(angle);
//        //
//        //    // Apply the power loss for the sides collisions
//        //    player.velocity.x *= powf(player.ENERGY_LOSS, 2);
//        //}
//        //
//        //if (CheckY)
//        //{
//        //    float norm = sqrtf(pow(player.velocity.x, 2) + pow(player.velocity.y, 2));
//        //    float angle = acosf(player.velocity.x / norm);
//        //
//        //    player.velocity.x = norm * cos(angle);
//        //    player.velocity.y = -norm * sin(angle);
//        //
//        //    // Apply the power loss for the bottom collisions
//        //    player.velocity.y *= powf(player.ENERGY_LOSS, 2);
//        //
//        //    // Threshold of 0.5 to the velocity.y to prevent the player from bouncing when on the ground with a low velocity
//        //    if (fabs(player.velocity.y) < 0.5f) player.velocity.y = 0.0f;
//        //}
//    }
//
//    void Collisions::drawSplash(Surface* screen, vec2 player_pos, float deltaTime)
//    {
//        //if (getCollisionType(player_pos) != TouchType::Ice) return;
//        //
//        //static float frame = 0.0f;
//        //const float animation_fps = 10.0f;
//        //
//        //frame += animation_fps * deltaTime;
//        //if (frame >= 3.0f) frame -= 3.0f;
//        //
//        //img_water_slide_right.SetFrame(frame);
//        //img_water_slide_left.SetFrame(frame);
//        //
//        //vec2 offset = vec2(
//        //    img_water_slide_right.GetWidth() / 2 - player_img_width / 2,
//        //    img_water_slide_right.GetHeight() / 2 - player_img_height / 2 + player.PLAYER_DRAW_OFFSET_Y + 1
//        //);
//        //
//        //vec2 draw_pos = player_pos + camera.getCamPos() + offset;
//        //
//        //if (player.velocity.x > 0) img_water_slide_right.Draw(screen, draw_pos);
//        //else img_water_slide_left.Draw(screen, draw_pos);
//    }
//
//}
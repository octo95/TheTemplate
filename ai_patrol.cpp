#include "ai_patrol.h"
#include "collisions.h"
#include "tile.h"

namespace Tmpl8
{
    Sprite img_ai_patrol(new Surface("assets/images/entities/img_ai_patrol.png"), 1);

    void AI_Patrol::getStomped()
    {
        isAILowerThanPlayer = (position.y + img_ai_patrol.GetHeight() / 2.0f) >= (player.position.y + TILE_SIZE / 1.5);
        if (isTouchingPlayer(&img_ai_patrol) && isAILowerThanPlayer)
        {
			player.velocity.y -= 6.0f;
            isDead = true;
        }
    }

    void AI_Patrol::Patrol(float deltaTime, Collisions* collisions, TileMap* tilemap)
    {
        if (isDead) return;
        
        getStomped();
        float spawn_x = this->position.x;
        
        vec2 center_pos = position + vec2(img_ai_patrol.GetWidth() / 2, img_ai_patrol.GetHeight() / 2);
        bool CheckL = collisions->checkCollisionL(center_pos) != None;
        bool CheckR = collisions->checkCollisionR(center_pos) != None;

        float position_speed = 100.0f;
        float rotation_speed = 3.0f;
        
        if (stop) position_speed = 0.0f;

        // Unused
        //bool conditionTurnRight =   (direction != Direction::LEFT && direction != Direction::RIGHT) ||  // If default case           => TURN RIGHT
        //                            (CheckL && direction == Direction::LEFT) ||                         // If blocked on the left
        //                            (EdgeRight && direction == Direction::LEFT) ||                      // If on the right edge
        //                            (EdgeLeft && direction == Direction::LEFT);                         // If on the left edge
        //
        //bool conditionTurnLeft =    ((CheckR && direction == Direction::RIGHT) || EdgeRight) ||         // If blocked on the right   => TURN LEFT
        //                            (EdgeRight && direction == Direction::RIGHT) ||                     // If on the right edge
        //                            (EdgeRight && direction == Direction::RIGHT) || 				    // If on the right edge
        //                            (EdgeLeft && direction == Direction::RIGHT);                        // If on the left edge

        bool conditionTurnRight =   (direction != Direction::LEFT && direction != Direction::RIGHT) ||  // If default case
                                    (position.x <= 0 && direction == Direction::RIGHT) ||               // If touches left screen boundary
                                    (CheckL && direction == Direction::LEFT);                           // If touches left collision
        

        bool conditionTurnLeft =    ((CheckR && direction == Direction::RIGHT)) ||                                              // If touches right
                                    (position.x + img_ai_patrol.GetWidth() > tilemap->current_map_data_read->GetWidth() && direction == Direction::RIGHT);    // If touches right screen boundary
        
        // Set the direction
        if (conditionTurnRight)
			direction = Direction::RIGHT;
        else if (conditionTurnLeft)
            direction = Direction::LEFT;
        
        // Set the motion
        if (!CheckR && direction == Direction::RIGHT)
            position.x += deltaTime * position_speed;  
        else if (!CheckL && direction == Direction::LEFT)
            position.x -= deltaTime * position_speed; 
        
        angle += (position.x - spawn_x) * rotation_speed;
    }
}


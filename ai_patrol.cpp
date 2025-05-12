#include "ai_patrol.h"
#include "collisions.h"
#include "tilemap.h"

namespace Tmpl8
{
    Sprite img_ai_patrol(new Surface("assets/images/entities/img_ai_patrol.png"), 1);

    void AI_Patrol::getStomped()
    {
        // The AI patrol can get stomped and killed if jumped on. 
        // This is detected if the player touches the AI and is at a higher vertical position.
        isAILowerThanPlayer = (position.y + img_ai_patrol.GetHeight() / 2.0f) >= (player.position.y + TILE_SIZE / 1.5);
        if (isTouchingPlayer(&img_ai_patrol) && isAILowerThanPlayer)
        {
            // If stomping, bounce the player back and set the AI's state to dead.
			player.velocity.y -= 6.0f;
            isDead = true;
        }
    }

    void AI_Patrol::Patrol(float deltaTime, Collisions* collisions, TileMap* tilemap)
    {
        // If the AI is stopped (debug feature), stop its logic.
        if (stop) return;
        
        // While patroling, check if it is getting stomped with the helper funciton.
        getStomped();

        // Store the AI's spawn x position to later calculate its angular acceleration.
        float spawn_x = this->position.x;
        
        // The AI patrol will detect side collisions using the same logic detection the player does.
        // Since the player's position is calculated around their center, we need to offset the calculations for our AI to a center position as well.
        vec2 center_pos = position + vec2(img_ai_patrol.GetWidth() / 2, img_ai_patrol.GetHeight() / 2);
        bool CheckL = collisions->checkCollisionL(center_pos) != None;
        bool CheckR = collisions->checkCollisionR(center_pos) != None;

        // Determine how fast the AI moves and rotates on its own.
        float position_speed = 100.0f;
        float rotation_speed = 3.0f;

        // Define the conditions that can make the AI turn right.
        bool conditionTurnRight =   (direction != Direction::LEFT && direction != Direction::RIGHT) ||  // By default, go right (if not any direction is assigned)
                                    (position.x <= 0 && direction == Direction::RIGHT) ||               // If touches left screen boundary
                                    (CheckL && direction == Direction::LEFT);                           // If touches left collision
        

        // Define the conditions that can make the AI turn left.
        bool conditionTurnLeft =    ((CheckR && direction == Direction::RIGHT)) ||                                                                          // If touches right
                                    (position.x + img_ai_patrol.GetWidth() > tilemap->current_map_data_read->GetWidth() && direction == Direction::RIGHT);  // If touches right screen boundary
        
        // Set the direction.
        if (conditionTurnRight)
			direction = Direction::RIGHT;
        else if (conditionTurnLeft)
            direction = Direction::LEFT;
        
        // Set the motion.
        if (!CheckR && direction == Direction::RIGHT)
            position.x += deltaTime * position_speed;  
        else if (!CheckL && direction == Direction::LEFT)
            position.x -= deltaTime * position_speed; 
        
        // Calculate the angle to draw the AI.
        angle += (position.x - spawn_x) * rotation_speed;
    }
}


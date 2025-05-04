#include "ai_patrol.h"
#include "collisions.h"
#include "tile.h"

namespace Tmpl8
{
    Sprite img_ai_patrol(new Surface("assets/images/entities/img_ai_patrol.png"), 1);

    void AI_Patrol::getStomped()
    {
        isAILowerThanPlayer = (position.y + img_ai_patrol.GetHeight() / 2.0f) >= (player.position.y + hitbox_radius + TILE_SIZE / 1.5);
        if (isTouchingPlayer() && isAILowerThanPlayer)
        {
			player.velocity.y -= 12.0f;
            isDead = true;
        }
    }

    void AI_Patrol::Patrol(float deltaTime, Collisions* collisions)
    {
        if (isDead) return;

        getStomped();
        float spawn_x = this->position.x;

        bool CheckLeft = collisions->checkCollisionLeft(position) == TileType::Collision;
        bool CheckRight = collisions->checkCollisionRight(position) == TileType::Collision;
        
        bool EdgeRight = collisions->checkCollisionBottom(vec2(position.x + TILE_SIZE, position.y + TILE_SIZE)) == TileType::None;
		bool EdgeLeft = collisions->checkCollisionBottom(vec2(position.x - TILE_SIZE, position.y + TILE_SIZE)) == TileType::None;
        
        float position_speed = 100.0f;
        float rotation_speed = 3.0f;
        
        if (stop) position_speed = 0.0f;
        
        bool conditionTurnRight =   (direction != Direction::LEFT && direction != Direction::RIGHT) ||  // If default case           => TURN RIGHT
                                    (CheckLeft && direction == Direction::LEFT) ||                      // If blocked on the left
                                    (EdgeRight && direction == Direction::LEFT) ||                      // If on the right edge
                                    (EdgeLeft && direction == Direction::LEFT);                         // If on the left edge
        
        bool conditionTurnLeft =    ((CheckRight && direction == Direction::RIGHT) || EdgeRight) ||     // If blocked on the right   => TURN LEFT
                                    (EdgeRight && direction == Direction::RIGHT) ||                     // If on the right edge
                                    (EdgeRight && direction == Direction::RIGHT) || 				    // If on the right edge
                                    (EdgeLeft && direction == Direction::RIGHT);                        // If on the left edge
        
        // Set the direction
        if (conditionTurnRight)
			direction = Direction::RIGHT;
        else if (conditionTurnLeft)
            direction = Direction::LEFT;
        
        // Set the motion
        if (!CheckRight && direction == Direction::RIGHT)
            position.x += deltaTime * position_speed;  
        else if (!CheckLeft && direction == Direction::LEFT)
            position.x -= deltaTime * position_speed; 
        
        angle += (position.x - spawn_x) * rotation_speed;
    }

    bool AI_Patrol::isTouchingPlayer()
    {
        float ai_rad = img_ai_patrol.GetWidth() / 2.0f;
        float player_rad = player_img_width / 2.0f;

        float radii_sum = ai_rad + player_rad;

        // AI center
        float ai_center_x = this->position.x + ai_rad;
        float ai_center_y = this->position.y + ai_rad;

        // Player center
        float player_center_x = player.position.x + player_rad;
        float player_center_y = player.position.y + player_rad;

        // Distance between AI's center and the player's one.
        float dx = ai_center_x - player_center_x;
        float dy = ai_center_y - player_center_y;
        float distance = sqrtf(dx * dx + dy * dy);

        bool touched_player = distance <= radii_sum;
        player.is_hurt = touched_player ? true : false;

        return (touched_player);
    }
}


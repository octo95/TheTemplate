#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "ai_patrol.h"
#include <cmath>
#include "tile.h"
#include "collisions.h"

namespace Tmpl8
{

    AI_Patrol::AI_Patrol(Player& playerRef, Camera& cameraRef) :
        camera(cameraRef),
        player(playerRef)
    {}

    Sprite img_ai_patrol(new Surface("assets/images/entities/img_ai_patrol.png"), 1);

    void AI_Patrol::Patrol(float deltaTime, Collisions* collisions)
    {
        float spawn_x = this->position.x;
        bool CheckLeft = collisions->CheckCollisionLeft(position) == TileType::Collision;
        bool CheckRight = collisions->CheckCollisionRight(position) == TileType::Collision;
        float position_speed = 100.0f;
        float rotation_speed = 200.0f;

        if (stop) printf("stop\n"), position_speed = 0.0f;
        printf("stop real value: %d\n", (int)stop);

        // Initialize the direction to right
        if (direction != Direction::LEFT && direction != Direction::RIGHT)
        {
            direction = Direction::RIGHT;  
        }

        if (!CheckRight && direction == Direction::RIGHT)
        {
            position.x += deltaTime * position_speed;  
        }
        if (!CheckLeft && direction == Direction::LEFT)
        {
            position.x -= deltaTime * position_speed; 
        }
        if (CheckRight && direction == Direction::RIGHT)
        {
            direction = Direction::LEFT;
        }
        if (CheckLeft && direction == Direction::LEFT)
        {
            direction = Direction::RIGHT;
        }
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

        return (distance <= radii_sum);
    }

}


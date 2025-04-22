#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <stdio.h>

#include "game.h"
#include "player.h"
#include "camera.h"
#include "collisions.h"

namespace Tmpl8
{
    Player::Player(Camera& cameraRef) :
        camera(cameraRef)
    {}

    // Variables
    Sprite player_img(new Surface("assets/tangerine.png"), 1);
    int hitbox_size = 16 - 2; // Tolerance of 2 pixels on the hitbox
    int player_img_width = player_img.GetWidth();
    int player_img_height = player_img.GetHeight();
    bool canJump = false;

    void Player::movePlayer(vec2& new_pos, vec2& half_velocity, Collisions* collisions)
    {
        // Left
        if (GetAsyncKeyState(VK_LEFT))
        {
            velocity.x -= ACCELERATION;
            if (velocity.x < -MAX_HORIZONTAL_SPEED) velocity.x = -MAX_HORIZONTAL_SPEED;
        }

        // Right
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            velocity.x += ACCELERATION;
            if (velocity.x > MAX_HORIZONTAL_SPEED) velocity.x = MAX_HORIZONTAL_SPEED;
        }

        // If no direction, slide
        else
        {
            if (velocity.x > 0)
            {
                velocity.x -= friction;
                if (velocity.x < 0) velocity.x = 0;
            }
            else if (velocity.x < 0)
            {
                velocity.x += friction;
                if (velocity.x > 0) velocity.x = 0;
            }
        }

        // Clamp fall speed
        velocity.y += gravity;
        if (velocity.y > MAX_VERTICAL_SPEED) velocity.y = MAX_VERTICAL_SPEED;

        half_velocity = velocity;
        collisions->applyBouncingPhysics(new_pos);

        // Jump
        if (can_jump)
        {
            velocity.y += -6.0f;
            collectibles_collected--;
        }
    
        // Pass the velocity to the camera to make the player rotate while moving
        camera.setAngleAcceleration(velocity.x * rotation_speed);

        // Apply horizontal movement
        new_pos.x += velocity.x;

        // Apply vertical movement        
        new_pos.y += velocity.y;

        // Clamp horizontally to not go out of bounds
        if (new_pos.x < 0) new_pos.x = 0;
        if (new_pos.x + player_img_width > SCREEN_WIDTH + TILE_SIZE)
            new_pos.x = SCREEN_WIDTH - player_img_width + TILE_SIZE;
    }

    vec2 Player::camFollowPlayer()
    {
        float camX = -TILE_SIZE;
        float camY = 0;
        int playerCenterY = static_cast<int>(position.y) + player_img_height / 2;
        int screenCenterY = SCREEN_HEIGHT / 2;
        int mapHeight = TILE_ROWS * TILE_SIZE;
        int maxCamY = SCREEN_HEIGHT - mapHeight;

        if (playerCenterY < screenCenterY)
            camY = 0;
        else
        {
            camY = -(playerCenterY - screenCenterY);

            if (camY < maxCamY)
                camY = maxCamY;
        }

        return { camX, camY };
    }
};

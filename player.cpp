#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "game.h"
#include "player.h"

namespace Tmpl8
{
    Player::Player(Camera& cameraRef) :
        camera(cameraRef)
    {}

    // Variables
    Sprite img_player(new Surface("assets/images/entities/img_player.png"), 1);

    int hitbox_radius = 16 - 2; // Tolerance of 2 pixels on the hitbox
    int player_img_width = img_player.GetWidth();
    int player_img_height = img_player.GetHeight();
    bool canJump = false;

    vec2 Player::movePlayer(Collisions* collisions, float deltaTime)
    {

        // Left
        if (move_cooldown > 0.0f) move_cooldown -= deltaTime;

        if (GetAsyncKeyState(VK_LEFT))
        {
            if (move_cooldown <= 0.0f)
            {
                velocity.x -= ACCELERATION / deltaTime;
                if (velocity.x < -max_horizontal_speed) velocity.x = -max_horizontal_speed;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            if (move_cooldown <= 0.0f)
            {
                velocity.x += ACCELERATION / deltaTime;
                if (velocity.x > max_horizontal_speed) velocity.x = max_horizontal_speed;
            }
        }

        // If no direction, slide
        else
        {
            if (velocity.x > 0)
            {
                velocity.x -= friction ;
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
        if (velocity.y > max_vertical_speed) velocity.y = max_vertical_speed;

        // Jump
        if (GetAsyncKeyState(VK_UP) & 0x8000 && can_jump && !jumping)
        {
            jumping = true;
            jumping_cooldown = 0.0f;
        }

        float jumping_max_time = 0.3f;
        static float jumping_vel_factor = 2.0f;

        if (jumping)
        {
            jumping_cooldown += deltaTime;

            if (GetAsyncKeyState(VK_UP) & 0x8000 && jumping_cooldown < jumping_max_time)
            {
                jumping_vel_factor -= 0.05f;
                velocity.y = -1.5f;
                
            }
            else
            {
                jumping = false;
                jumping_vel_factor = 5.0f;
            }
        }
        // Pass the velocity to the camera to make the player rotate while moving
        angular_acceleration = velocity.x * 270.0f;

        dash();

        return position + velocity;
    }

    vec2 Player::camFollowPlayer(TileMap* map)
    {
        vec2 camPos = vec2(0.0f, 0.0f); // Offset the camera by one tile to the right

        vec2 playerCenter = vec2(
            position.x + player_img_width / 2.0f,
            position.y + player_img_height / 2.0f
        );

        vec2 screenCenter = vec2(
            SCREEN_WIDTH / 2.0f,
            SCREEN_HEIGHT / 2.0f
        );

        vec2 mapSize = vec2(
            map->current_map_data_read->GetWidth(),
            map->current_map_data_read->GetHeight()
        );

        vec2 maxCam = vec2(
            SCREEN_WIDTH - mapSize.x,
            SCREEN_HEIGHT - mapSize.y
        );

        // Vertical
        if (playerCenter.y < screenCenter.y)
        {
            camPos.y = 0.0f;
        }
        else
        {
            camPos.y = -(playerCenter.y - screenCenter.y);
            if (camPos.y < maxCam.y)
            {
                camPos.y = maxCam.y;
            }
        }

        // Horizontal
        if (playerCenter.x < screenCenter.x)
        {
            camPos.x = 0.0f;
        }
        else
        {
            camPos.x = -(playerCenter.x - screenCenter.x);
            if (camPos.x < maxCam.x)
            {
                camPos.x = maxCam.x;
            }
        }

        // + Clamp to not go out of bounds horizontally
        if (position.x < 0) position.x = 0;
        if (position.x + player_img_width > mapSize.x)
            position.x = mapSize.x - player_img_width;

        return camPos;
    }

    void Player::dash()
    {
        if (GetAsyncKeyState('X'))
        {
           if (GetAsyncKeyState(VK_RIGHT))
            {
                position.x += 10.0f;
            }
            if (GetAsyncKeyState(VK_LEFT))
            {
                position.x -= 10.0f;
            }
        }
    }

};

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

    void Player::movePlayer(vec2& new_pos, Collisions* collisions, float deltaTime)
    {

        // Left
        if (move_cooldown > 0.0f) move_cooldown -= deltaTime;

        if (GetAsyncKeyState(VK_LEFT))
        {
            if (move_cooldown <= 0.0f || velocity.x < 0)
            {
                velocity.x -= ACCELERATION / deltaTime;
                if (velocity.x < -MAX_HORIZONTAL_SPEED) velocity.x = -MAX_HORIZONTAL_SPEED;
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            if (move_cooldown <= 0.0f || velocity.x > 0)
            {
                velocity.x += ACCELERATION / deltaTime;
                if (velocity.x > MAX_HORIZONTAL_SPEED) velocity.x = MAX_HORIZONTAL_SPEED;
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
        if (velocity.y > MAX_VERTICAL_SPEED) velocity.y = MAX_VERTICAL_SPEED;

        collisions->applyBouncingPhysics(new_pos);

        // Jump
        if (can_jump)
        {
            velocity.y = -4.0f;
            collectibles_collected--;
        }

        // Pass the velocity to the camera to make the player rotate while moving
        angular_acceleration = velocity.x * 270.0f;

        new_pos += velocity;
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

        // + Clamp to not go out of bounds

        // Horizontally
        if (position.x < 0) position.x = 0;
        if (position.x + player_img_width > mapSize.x)
            position.x = mapSize.x - player_img_width;

        return camPos;
    }


};

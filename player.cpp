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

    vec2 Player::movePlayer(Collisions* collisions, float deltaTime)
    {
        // move_cooldown allows to stop player's input temporarily, for example like when hiting a wall.
        if (move_cooldown > 0.0f) move_cooldown -= deltaTime;

        // * LEFT INPUT
        if (GetAsyncKeyState(VK_LEFT))
        {
            // If no cooldown...
            if (move_cooldown <= 0.0f)
            {
                // Update the horizontal velocity based on the acceleration and deltaTime.
                velocity.x -= ACCELERATION / deltaTime;

                // Clamp it within a max_horizontal_speed.
                if (velocity.x < -max_horizontal_speed) velocity.x = -max_horizontal_speed;
            }
        }
        // * RIGHT INPUT
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            // If no cooldown...
            if (move_cooldown <= 0.0f)
            {
                // Update the vertical velocity based on the acceleration and deltaTime.
                velocity.x += ACCELERATION / deltaTime;

                // Clamp it within a max_vertical_speed.
                if (velocity.x > max_horizontal_speed) velocity.x = max_horizontal_speed;
            }
        }

        // * NO DIRECTION : slide
        else
        {
            // If the player goes to the right, reduce its friction to this side until it reaches a value below 0 to clamp it to 0.
            if (velocity.x >= 0)
            {
                velocity.x -= friction ;
                if (velocity.x < 0) velocity.x = 0;
            }
            // If the player goes to the left, reduce its friction to this side until it reaches a value above 0 to clamp it to 0.
            else if (velocity.x < 0)
            {
                velocity.x += friction;
                if (velocity.x > 0) velocity.x = 0;
            }
        }
        // Pass the velocity to the camera to make the player rotate while moving
        angular_acceleration = velocity.x * 270.0f;

        return position + velocity;
    }

    void Player::applyGravity(float deltaTime)
    {
        // Clamp fall speed depending on the gravity and deltaTime.
        velocity.y += GRAVITY / deltaTime / 120.0f;
        if (velocity.y > max_vertical_speed) velocity.y = max_vertical_speed;
    }

    void Player::manageJump(float deltaTime)
    {
        // If the player presses <ARROW_UP>, can jump and is not already jumping we can initialize the jump.
        if (GetAsyncKeyState(VK_UP) & 0x8000 && can_jump && !jumping)
        {
            jumping = true;
            jumping_cooldown = 0.0f;
        }

        float jumping_max_time = 0.2f;

        // If jumping, start timer
        if (jumping)
        {
            // Increase the timer
            jumping_cooldown += deltaTime;

            // We check again if the player is still pressing <ARROW_UP> to allow for variable jump height depending on key press.
            // We also have to make sure we are still going through the timer, if so we can adjust the player's vertical velocity to apply to jump.
            if (GetAsyncKeyState(VK_UP) & 0x8000 && jumping_cooldown < jumping_max_time)
            {
                velocity.y = -2.5f;
            }
            else
            {
                jumping = false;
            }
        }
    }

    void Player::restrictPlayerInMap(TileMap* tilemap)
    {
        vec2 mapSize = vec2(
            tilemap->current_map_data_read->GetWidth(),
            tilemap->current_map_data_read->GetHeight()
        );

        // Clamp the player on screen with the map size to prevent them from going out of bounds

        if (position.x - player_img_width / 2 < 0) position.x = player_img_width / 2;   // On the left
        if (position.x + player_img_width / 2 > mapSize.x)                              // On the right
            position.x = mapSize.x - player_img_width / 2;

        float offset = hitbox_radius - TILE_SIZE / 1.4f;        // Let the player be able to go a bit out of the boundaries by a little extra without letting them able to clip out of bounds.
        if (position.y - offset < 0.0f) position.y = offset;    // On the left
    }

    vec2 Player::camFollowPlayer(TileMap* tilemap)
    {
        // We first gather the positions of the camera, player, screen and map.
        vec2 camPos = vec2(0.0f, 0.0f);

        vec2 playerCenter = vec2(
            position.x + player_img_width / 2.0f,
            position.y + player_img_height / 2.0f
        );

        vec2 screenCenter = vec2(
            SCREEN_WIDTH / 2.0f,
            SCREEN_HEIGHT / 2.0f
        );

        vec2 mapSize = vec2(
            tilemap->current_map_data_read->GetWidth(),
            tilemap->current_map_data_read->GetHeight()
        );

        vec2 maxCam = vec2(
            SCREEN_WIDTH - mapSize.x,
            SCREEN_HEIGHT - mapSize.y
        );

        // * VERTICAL CAMERA CLAMP

        // Clamp the camera to 0 if the player is on the upper half of the screen.
        if (playerCenter.y < screenCenter.y)
        {
            camPos.y = 0.0f;
        }
        else
        {
            // Otherwise, make the camera follow the player's vertical movement.
            camPos.y = -(playerCenter.y - screenCenter.y);

            // If it reaches the bottom of the screen, stop panning down.
            if (camPos.y < maxCam.y)
            {
                camPos.y = maxCam.y;
            }
        }

        // * HORIZONTAL CAMERA CLAMP

        // Clamp the camera to 0 if the player is on the left of the screen.
        if (playerCenter.x < screenCenter.x)
        {
            camPos.x = 0.0f;
        }
        else
        {
            // Otherwise, make the camera follow the player's horizontal movement.
            camPos.x = -(playerCenter.x - screenCenter.x);

            // If it reaches the right of the screen, stop panning right.
            if (camPos.x < maxCam.x)
            {
                camPos.x = maxCam.x;
            }
        }
        return camPos;
    }

    void Player::manageDash(float deltaTime)
    {
        float dashing_max_time = 0.2f;
        float direction = 1.0f;
        bool can_dash = dash_count > 0;

        // If the player's velocity is positive the player is moving right and left if negative.
        if (velocity.x >= 0) direction =  1.0f;
        if (velocity.x < 0)  direction = -1.0f;

        static bool xPreviouslyPressed = false;
        bool xCurrentlyPressed = (GetAsyncKeyState('X') & 0x8000);

        // If <X> is pressed once, the player can dash and is not already dashing then initialize the dash.
        if (xCurrentlyPressed && !xPreviouslyPressed && can_dash && !dashing)
        {
            dashing = true;
            dashing_cooldown = 0.0f;
            move_cooldown = dashing_max_time;
            dash_count--;
        }
        xPreviouslyPressed = xCurrentlyPressed;

        // If the player is dashing then start the dashing timer.
        if (dashing)
        {
            velocity.y = 0.1f; // Stabilize the Y velocity to a low value for a more straight dash movement
            dashing_cooldown += deltaTime;

            // During the timer, update the velocity based on its direction. We also change the max_horizontal_speed
            // for a better control of the dash movement.
            if (dashing_cooldown < dashing_max_time)
            {
                max_horizontal_speed = 1.5f;
                velocity.x = direction * 5.0f;
            }
            else
            {
                dashing = false;
            }
        }
    }

};

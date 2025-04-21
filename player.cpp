#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <stdio.h>

#include "game.h"
#include "player.h"
#include "camera.h"

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

    void Player::movePlayer(vec2& new_pos)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            velocity.x -= ACCELERATION;
            if (velocity.x < -MAX_HORIZONTAL_SPEED) velocity.x = -MAX_HORIZONTAL_SPEED;
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            velocity.x += ACCELERATION;
            if (velocity.x > MAX_HORIZONTAL_SPEED) velocity.x = MAX_HORIZONTAL_SPEED;
        }
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

        velocity.y += gravity;
        if (velocity.y > 5) velocity.y = 5; // Clamp fall speed

        /* + JUMP LOGIC +
        TileType CheckSides = CheckCollisionSides({ new_pos.x + velocity.x, position.y });
        TileType CheckBottom = CheckCollisionBottom({ position.x, new_pos.y + velocity.y });

        bool isCollision = (CheckSides == TileType::Collision || CheckBottom == TileType::Collision);
        bool isIce = (CheckSides == TileType::Ice || CheckBottom == TileType::Ice);
        canJump = GetAsyncKeyState(VK_UP) && (CheckBottom == 3 || CheckBottom == 4) && collectibles_collected > 0;

        if (canJump)
        {
            velocity.y += -6.0f;
            collectibles_collected--;
        }

        if (isCollision || isIce)
        {
            //if (CheckSides) {
            //    float norm = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
            //    float angle = acos(velocity.x / norm);
            //
            //    velocity.x = norm * -cos(angle);
            //    velocity.y = -norm * sin(angle);                
            //}
            //else if (CheckBottom != TileType::None) {
            //    float norm = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
            //    float angle = acos(velocity.y / norm);
            //
            //    velocity.x = norm * cos(angle);
            //    velocity.y = -norm * -sin(angle);
            //}
            //else if (!CheckBottom) {
            //    velocity.y += gravity * 0.3;
            //    if (velocity.y > 5) velocity.y = 5;
            //}

            //velocity.x *= pow(ENERGY_LOSS, 2);
            //velocity.y *= pow(ENERGY_LOSS, 2);
        }
        */

        camera.setAngleAcceleration(velocity.x * rotation_speed);

        // Horizontal movement
        new_pos.x += velocity.x;

        // Vertical movement        
        new_pos.y += velocity.y;

        // Clamp horizontally
        if (new_pos.x < 0) new_pos.x = 0;
        if (new_pos.x + player_img_width > SCREEN_WIDTH + TILE_SIZE)
            new_pos.x = SCREEN_WIDTH - player_img_width + TILE_SIZE;
    }


    void Player::setPlayerDefaultPos(const vec2& pos)
    {
        default_pos = pos;
    }

    void Player::getPlayerDefaultPos(vec2& pos)
    {
        pos = default_pos;
    }

    void Player::getPlayerPos(vec2& pos)
    {
        pos = position;
    }

    void Player::setPlayerPos(const vec2& pos)
    {
        position = pos;
    }

    void Player::setTouchStateFollowAI(bool isTouched)
    {
        is_touched_follow_ai = isTouched;
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

    void Player::manageDefaultPos(int index)
    {
        switch(index)
        {
            case 1: 
                setPlayerDefaultPos(vec2(400.0f, 10.0f));
                break;      
            case 2:
                setPlayerDefaultPos(vec2(500.0f, 10.0f));
                break;
            case 3:
                setPlayerDefaultPos(vec2(600.0f, 10.0f));
                break;
        }
    }
};

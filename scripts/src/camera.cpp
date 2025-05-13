#include "../include/camera.h"

namespace Tmpl8
{
    void Camera::shakeCamera(float deltaTime)
    {
        // Frequency and amplitude null by default.
        static float frequency = 0.0f;
        static float amplitude = 0.0f;

        // Depending on different conditions we tweak the shaking for different visual effects.
        if (shake_conditions != shakeConditions::None && total_time <= 0.0f)
        {
            switch (shake_conditions)
            {
            // If the player is damaged.
            case shakeConditions::Damage:
                total_time = 0.6f;
                frequency = 20.0f;
                amplitude = 2.5f;
                break;
            // If the player falls with a high Y velocity.
            case shakeConditions::FallHard:
                total_time = 1.7f;
                frequency = 3.5f;
                amplitude = 2.3f;
                break;
            // If the player collides with the bell.
            case shakeConditions::Bell:
                total_time = 2.0f;
                frequency = 3.0f;
                amplitude = 1.5;
            }

            // By default, don't shake.
            shake_conditions = shakeConditions::None;
        }

        // (!) The following shaking math was made with the help of the lecturer Jeremiah on the 3dgep.com Discord server.

        // If the timer is not gone, continue it by decrementing deltaTime to total_time.
        // If the shakeConditions is None this will stop the shake even if it's not done.
        if (total_time > 0.0f && shake_conditions != shakeConditions::None)
        {
            total_time -= deltaTime;

            shake.x = std::sin(std::exp(total_time) * frequency) * amplitude;
            shake.y = std::cos(std::exp(total_time) * frequency) * amplitude;
        }
        else
        {
            shake = { 0.0f, 0.0f };
        }
    }

    // A helper function to draw objects on screen with the camera offset so that it follows its movement.
    void Camera::drawWithCam(Sprite* img, Surface* screen, vec2 pos)
    {
        vec2 draw_pos;
        draw_pos = pos + getCamPos();
        img->Draw(screen, draw_pos);
    }

    // The player is drawn with the camera and rotates depending on its horizontal acceleration
    void Camera::drawPlayer(Sprite* img, Surface* screen, vec2 pos, float deltaTime, float acceleration)
    {
        player_angle += deltaTime * acceleration;
        pos += getCamPos();
        // The player's center coordinates are in the center of the sprite, to draw the sprite 
        // properly we need to offset it by half its x and y size.
        img->DrawRotated(screen, pos + vec2(-img->GetWidth() / 2, -img->GetHeight() / 2), player_angle);
    }

    // Following the same logic as the player, the AI that copies its movement is drawn depending 
    // on the player's past acceleration and follows the camera.
    void Camera::drawAICopy(Sprite* img, Surface* screen, vec2 pos, float deltaTime, float acceleration)
    {
        ai_copy_angle += deltaTime * acceleration;
        pos += getCamPos() - vec2(0.0f, 4.0f);
        img->DrawRotated(screen, pos, ai_copy_angle);
    }
};
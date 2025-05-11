#include "camera.h"

namespace Tmpl8
{
    void Camera::shakeCamera(float deltaTime)
    {
        static float frequency = 0.0f;
        static float amplitude = 0.0f;

        if (shake_conditions != shakeConditions::None && total_time <= 0.0f)
        {
            switch (shake_conditions)
            {
            case shakeConditions::Damage:
                total_time = 0.6f;
                frequency = 20.0f;
                amplitude = 2.5f;
                break;
            case shakeConditions::FallHard:
                total_time = 1.7f;
                frequency = 3.5f;
                amplitude = 2.3f;
                break;
            case shakeConditions::Bell:
                total_time = 2.0f;
                frequency = 3.0f;
                amplitude = 1.5;
            }
            shake_conditions = shakeConditions::None;
        }

        if (total_time > 0.0f && shake_conditions != shakeConditions::None)
        {
            total_time -= deltaTime;

            shake.x = std::sin(std::exp(total_time) * frequency) * amplitude;
            shake.y = std::cos(std::exp(total_time) * frequency) * amplitude;
        }
        else
        {
            shake = { 0, 0 };
        }
    }

    void Camera::drawWithCam(Sprite* img, Surface* screen, vec2 pos)
    {
        vec2 draw_pos;
        draw_pos = pos + getCamPos();
        img->Draw(screen, draw_pos);
    }

    void Camera::drawPlayer(Sprite* img, Surface* screen, vec2 pos, float deltaTime, float acceleration)
    {
        player_angle += deltaTime * acceleration;
        pos += getCamPos();
        img->DrawRotated(screen, pos + vec2(-img->GetWidth() / 2, -img->GetHeight() / 2), player_angle);
    }

    void Camera::drawAICopy(Sprite* img, Surface* screen, vec2 pos, float deltaTime, float acceleration)
    {
        ai_copy_angle += deltaTime * acceleration;
        pos += getCamPos() - vec2(0.0f, 4.0f);
        img->DrawRotated(screen, pos, ai_copy_angle);
    }
};
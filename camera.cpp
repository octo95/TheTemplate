#include "camera.h"

namespace Tmpl8
{
    void Camera::shakeCamera(float deltaTime)
    {
        float shakeTime = 0.6f;
        float frequency = 20.0f;
        float amplitude = 2.5;

        if (shake_state)
        {
            total_time = shakeTime;
            shake_state = false;
        }

        total_time -= deltaTime;

        if (total_time > 0.0f)
        {
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
        pos += getCamPos() - vec2(0,4) ;
        img->DrawRotated(screen, pos, player_angle);
    }

    void Camera::drawAICopy(Sprite* img, Surface* screen, vec2 pos, float deltaTime, float acceleration)
    {
        ai_copy_angle += deltaTime * acceleration;
        pos += getCamPos() - vec2(0, 4);
        img->DrawRotated(screen, pos, ai_copy_angle);
    }
};
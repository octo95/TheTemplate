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

    void Camera::drawWithCam(Sprite* img, Surface* screen, int x, int y)
    {
        x += getCamPos().x;
        y += getCamPos().y;
        img->Draw(screen, x, y);
    }

    void Camera::drawWithCam(Sprite* img, Surface* screen, vec2 pos)
    {
        img->Draw(screen, pos + getCamPos());
    }

    void Camera::drawPlayer(Sprite* img, Surface* screen, int x, int y, float deltaTime)
    {
        player_angle += deltaTime * acceleration;
        x += getCamPos().x;
        y += getCamPos().y;
        img->DrawRotated(screen, x, y, player_angle);
    }

    void Camera::drawPlayer(Sprite* img, Surface* screen, vec2 pos, float deltaTime)
    {
        player_angle += deltaTime * acceleration;
        pos.x += getCamPos().x;
        pos.y += getCamPos().y;
        img->DrawRotated(screen, pos.x, pos.y - 4, player_angle);
    }
};
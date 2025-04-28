#include "camera.h"

namespace Tmpl8
{
    void Camera::setCamPos(const vec2& position)
    { 
        this->position = position;
    }

    vec2 Camera::getCamPos() const
    {
        return position + shake;
    }

    void Camera::setShakeState(bool is_shaking)
    {
        shake_state = is_shaking;
    }

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

    void Camera::drawPlayer(Sprite* img, Surface* screen, int x, int y, float deltaTime)
    {
        player_angle += deltaTime * acceleration;
        x += getCamPos().x;
        y += getCamPos().y;
        img->DrawRotated(screen, x, y, player_angle);
    }
};
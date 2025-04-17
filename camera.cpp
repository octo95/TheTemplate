#include <cmath>

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

    void Camera::camShake(float deltatime)
    {
        total_time -= deltatime;
        const float frequency = 20.0f;
        const float amplitude = 2.5f;
        if (total_time > 0.0f)
        {
            shake.x = std::sin(exp(total_time) * frequency) * amplitude; // TODO : total_time / max_time
            shake.y = std::cos(exp(total_time) * frequency) * amplitude;
        }
        else
        {
            shake = { 0, 0 };
        }
    }

    void Camera::Shake()
    {
        total_time = 0.6f;
    }

    void Camera::drawWithCam(Sprite* img, Surface* screen, int x, int y)
    {
        x += getCamPos().x;
        y += getCamPos().y;
        img->Draw(screen, x, y);
    }

};
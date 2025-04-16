#include "camera.h"
#include <cmath>

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
        const float frequency = 10.0f;
        const float amplitude = 10.0f;
        if (total_time > 0.0f)
        {
            shake.x = std::sin(total_time * frequency) * amplitude; // TODO : total_time / max_time
            shake.y = std::cos(total_time * frequency) * amplitude;
        }
        else
        {
            shake = { 0, 0 };
        }
    }

    void Camera::Shake()
    {
        total_time = 2.0f;
    }
};
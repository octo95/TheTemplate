#include "ai_follow.h"

namespace Tmpl8
{
    Sprite img_ai_follow(new Surface("assets/images/entities/img_ai_follow.png"), 1);

    void AI_Follow::followPlayer(float deltaTime)
    {
        if (stop) return;

        const float delayAmplifier = 0.35f;

        float diffX = player.position.x - this->position.x;
        float diffY = player.position.y - this->position.y;

        // Calculate the angle to the player
        angle = atan2(diffY, diffX) * 180.0f / 3.1415f + 90.0f; 

        // Convert the angle from radians to degrees
        float angleInDegrees = angle * 180.0f / 3.1415f;

        this->position.x += diffX * deltaTime * delayAmplifier;
        this->position.y += diffY * deltaTime * delayAmplifier;
    }
}
#include "ai_follow.h"

namespace Tmpl8
{
    Sprite img_ai_follow(new Surface("assets/images/entities/img_ai_follow.png"), 1);

    void AI_Follow::followPlayer(float deltaTime)
    {
        if (!is_following) return;

        const float delayAmplifier = 0.5f;

        float diffX = player.position.x - this->position.x;
        float diffY = player.position.y - this->position.y;

        // Calculate the angle to the player
        angle = atan2(diffY, diffX) * 180.0f / 3.1415f + 90.0f; 

        // Convert the angle from radians to degrees
        float angleInDegrees = angle * 180.0f / 3.1415f;

        this->position.x += diffX * deltaTime * delayAmplifier;
        this->position.y += diffY * deltaTime * delayAmplifier;
    }

    bool AI_Follow::isTouchingPlayer()
    {
        float ai_rad = img_ai_follow.GetWidth() / 2.0f;
        float player_rad = hitbox_radius;
        float tolerance = 3.0f;

        float radii_sum = ai_rad + player_rad + tolerance;

        float dx = (this->position.x + ai_rad) - (player.position.x);
        float dy = (this->position.y + ai_rad) - (player.position.y);
        float distance = sqrtf(dx * dx + dy * dy);

        bool touched_player = distance <= radii_sum;
        player.is_hurt = touched_player ? true : false;

        return (touched_player);
    }
}
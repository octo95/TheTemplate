#include "ai_copy.h"

namespace Tmpl8
{
    Sprite img_ai_copy(new Surface("assets/images/entities/img_ai_copy.png"), 1);

    void AI_Copy::setProperties()
    {
        if (stop) return;

        if (copyTimer > 0.0f)
        {
            copyTimer -= 1.0f / 60.0f;
            return;
        }

        PlayerState pastState = playerBuffer.read(); 
        this->position = pastState.position + vec2(-hitbox_radius, -hitbox_radius);
        this->acceleration = pastState.acceleration;
    }


    //bool AI_Copy::isTouchingPlayer()
    //{
    //    float ai_rad = img_ai_copy.GetWidth() / 2.0f;

    //    float radii_sum = ai_rad + hitbox_radius;

    //    // AI center
    //    float ai_center_x = this->position.x + ai_rad;
    //    float ai_center_y = this->position.y + ai_rad;

    //    // Distance between AI's center and the player's one.
    //    float dx = ai_center_x - player.position.x;
    //    float dy = ai_center_y - player.position.y;
    //    float distance = sqrtf(dx * dx + dy * dy);

    //    bool touched_player = distance <= radii_sum;

    //    return (touched_player);
    //}
}


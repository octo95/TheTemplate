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
        this->position = pastState.position + vec2(-player.hitbox_radius, -player.hitbox_radius);
        this->acceleration = pastState.rotation_acceleration;
    }

    void AI_Copy::updatePlayerBuffer() {
        this->playerBuffer.add(player.position, player.angular_acceleration);
    }
}


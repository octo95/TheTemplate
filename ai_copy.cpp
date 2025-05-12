#include "ai_copy.h"

namespace Tmpl8
{
    Sprite img_ai_copy(new Surface("assets/images/entities/img_ai_copy.png"), 1);

    void AI_Copy::setProperties()
    {
        // If the AI is stopped (debug feature), stop its logic.
        if (stop) return;

        // copyTimer is the time it will take before the AI copy will start following the player.
        if (copyTimer > 0.0f)
        {
            copyTimer -= 1.0f / 60.0f;
            return;
        }

        // Once done going through the timer, the AI copy can start its logic, it gathers the player's previous position from 
        // <copyTime> seconds ago and applies them thanks to a circular buffer (see circular_buffer.cpp for more information).
        // We also gather the player's past angular acceleration to draw the AI copy with the correct angle.

        PlayerState pastState = playerBuffer.read(); 
        this->position = pastState.position + vec2(-player.hitbox_radius, -player.hitbox_radius);
        this->angular_acceleration = pastState.rotation_acceleration;
    }

    void AI_Copy::updatePlayerBuffer() {
        // Update the playerBuffer with their position and acceleration using the head of the circular buffer.
        this->playerBuffer.add(player.position, player.angular_acceleration);
    }
}


#include "ai.h"

namespace Tmpl8
{
    bool AI::isTouchingPlayer(Sprite* img)
    {
        float ai_rad = img->GetWidth() / 2.0f;

        // AI center
        vec2 ai_pos = this->position + vec2(ai_rad, ai_rad);

        // Distance between AI's center and the player's one (the player's anchor point being already in the middle).
        vec2 diff = ai_pos - player.position;

        float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);
        float radii_sum = ai_rad + hitbox_radius;

        // The AI touches the player if its distance is inferior to the sum of the radii
        bool touch = distance <= radii_sum;

        return touch;
    }
}

#pragma once
#include "ai.h"
#include "player.h"
#include "circular_buffer.h"

namespace Tmpl8
{
    extern Sprite img_ai_copy;

    // Inherit from AI.
    class AI_Copy : public AI
    {
    public:
        // The AI copy needs a circular buffer to copy the previous position of the player, for more information check <circular_buffer>.
        CircularBuffer playerBuffer;
        float copyTimer;

        // Constructor
        AI_Copy(
            Player& playerRef,
            float& timer
        ) :
            AI(playerRef, vec2(-500.0f,-500.0f)),   // Make the AI appear out of bounds until its copyTimer starts.
            copyTimer(timer)
        {
        };

        void setProperties();
        void updatePlayerBuffer();
    };
}
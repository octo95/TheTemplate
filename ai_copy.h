#pragma once
#include "ai.h"
#include "player.h"
#include "circular_buffer.h"

namespace Tmpl8
{
    extern Sprite img_ai_copy;

    class AI_Copy : public AI
    {
    public:
        CircularBuffer playerBuffer;
        float copyTimer;

        // Constructor
        AI_Copy(
            Player& playerRef,
            float& timer
        ) :
            AI(playerRef, vec2(-500.0f,-500.0f)),
            copyTimer(timer)
        {
        };

        void setProperties();
        void updatePlayerBuffer();
    };
}
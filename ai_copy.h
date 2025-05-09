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
        float copyTimer = 4.0f;     // Wait 4 seconds before starting to read the buffer when loading a new level

        // Constructor
        AI_Copy(
            Player& playerRef,
            float& timer
        ) :
            AI(playerRef, vec2(0,0)),
            copyTimer(timer)
        {
        };

        void setProperties();
        void updatePlayerBuffer();
    };
}
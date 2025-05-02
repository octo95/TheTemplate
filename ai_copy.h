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
        float copyTimer = 3.0f;     // Wait 3 seconds before starting to read the buffer when loading a new level

        // Constructor
        AI_Copy(
            Player& playerRef,
            vec2 spawn_pos
        ) :
            AI(playerRef, spawn_pos)
        {
        };

        bool isTouchingPlayer();

        void setProperties();
    };
}
#pragma once
#include "player.h"
#include "circular_buffer.h"

namespace Tmpl8
{
    extern Sprite img_ai_copy;

    class AI_Copy 
    {
        public:
            CircularBuffer playerBuffer;
            float copyTimer = 3.0f;     // Wait 3 seconds before starting to read the buffer when loading a new level
            bool stop = false;          // Stops the AI if true (for debug)

		    // Constructor
            AI_Copy(
                Player& playerRef
            );
        
		    // Variables
            float acceleration = 0;
            vec2 default_pos = { -100, -100 }; // Make the AI appear out of bounds when not on screen
            vec2 position = { 0, 0 };

		    // Functions
            bool isTouchingPlayer();
            void setProperties();
      
        private:
            Player& player;
    };
}

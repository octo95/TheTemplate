#pragma once
#include "camera.h"
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

		    // Constructor
            AI_Copy(
                Player& playerRef, 
                Camera& cameraRef
            );
        
		    // Variables
            float angle = 0;
            vec2 default_pos = { 0, 0 };
            vec2 position = { 0, 0 };

		    // Functions
            bool isTouchingPlayer();
            void setPos();
      
        private:
            Player& player;
            Camera& camera;
    };
}

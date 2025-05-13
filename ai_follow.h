#pragma once
#include "ai.h"
#include "camera.h"
#include "player.h"

namespace Tmpl8
{
    extern Sprite img_ai_follow;

    // Inherit from AI.
    class AI_Follow: public AI
    {
        public:
            // Constructor
            AI_Follow(
                Player& playerRef,
                vec2 spawn_pos,
                Camera& cameraRef
            ) : 
                AI(playerRef, spawn_pos), 
                camera(cameraRef)
            {
            };

		    // Variables
            float angle = 0.0f;  // Angle to draw the AI at.
            Camera& camera;

            // Functions
            void followPlayer(float deltaTime);
    };
}

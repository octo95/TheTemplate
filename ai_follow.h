#pragma once
#include "ai.h"
#include "camera.h"
#include "player.h"

namespace Tmpl8
{
    extern Sprite img_ai_follow;

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
            float angle = 0.0f;
            bool is_following = true;
            Camera& camera;

            // Functions
            void followPlayer(float deltaTime);
            void setAIFollowDefaultPos(const vec2& pos) { default_pos = pos; }
            void setAIFollowPos(const vec2& pos) { position = pos; }
            void getAIFollowPos(vec2& pos) { pos = position; }
    };
}

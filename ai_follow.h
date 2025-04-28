#pragma once
#include "camera.h"
#include "player.h"

namespace Tmpl8
{
    extern Sprite img_ai_follow;

    class AI_Follow 
    {
        public:
            // Constructor
            AI_Follow(
                Player& playerRef, 
                Camera& cameraRef
            );

		    // Variables
            vec2 default_pos = { 0, 0 };
            vec2 position = default_pos;
            float angle = 0.0f;
            bool is_following = true;

            // Functions
            void followPlayer(float deltaTime);
            void setAIFollowDefaultPos(const vec2& pos) { default_pos = pos; }
            void setAIFollowPos(const vec2& pos) { position = pos; }
            void getAIFollowPos(vec2& pos) { pos = position; }
            bool isTouchingPlayer();

        private:
            Player& player;
            Camera& camera;
    };
}

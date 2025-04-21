#pragma once
#include "player.h"
#include "camera.h"

namespace Tmpl8
{
    extern Sprite img_ai_follow;
    extern vec2 ai_follow_pos;

    const vec2 AI_FOLLOW_DEFAULT_POS[3] = 
    {
        vec2 {700,10},
        vec2 {100,300},
        vec2 {0,0}
    };

    class AI_Follow {
    public:
        AI_Follow(Player& playerRef, Camera& cameraRef);
        void followPlayer(float deltaTime);
        void setTouchingPlayer();
        void manageDefaultPosAI_Follow(int index);
    private:
        Player& player;
        Camera& camera;
    };
}

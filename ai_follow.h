#pragma once
#include "player.h"
#include "camera.h"

namespace Tmpl8
{
    extern Sprite img_ai_follow;
    extern vec2 ai_follow_pos;

    class AI_Follow {
    public:
        AI_Follow(Player& playerRef, Camera& cameraRef);
        void followPlayer(float deltaTime);
    private:
        Player& player;
        Camera& camera;
    };
}

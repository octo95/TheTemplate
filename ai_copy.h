#pragma once
#include "player.h"
#include "camera.h"

namespace Tmpl8
{
    extern Sprite img_ai_copy;

    class AI_Copy {
    public:
        AI_Copy(Player& playerRef, Camera& cameraRef);

        float angle = 0;
        vec2 default_pos = { 0, 0 };
        vec2 position = { 0, 0 };
        bool isTouchingPlayer();
        void setPos();
      
    private:
        Player& player;
        Camera& camera;
    };
}

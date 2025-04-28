#pragma once
#include "player.h"
#include "camera.h"

namespace Tmpl8
{
    extern Sprite img_ai_patrol;

    class AI_Patrol {
    public:
        float angle = 0;
        bool stop = false;
        vec2 default_pos = { 0, 0 };
        vec2 position = { 0, 0 };
        AI_Patrol(Player& playerRef, Camera& cameraRef);
        void setAIPatrolPos(const vec2& pos) { position = pos; }
        bool isTouchingPlayer();
        void Patrol(float deltaTime, Collisions* collisions);
    private:
        Player& player;
        Camera& camera;

        enum class Direction
        {
            LEFT,
            RIGHT
        };

        Direction direction;

    };
}

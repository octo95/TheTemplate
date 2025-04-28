#pragma once
#include "player.h"
#include "camera.h"

namespace Tmpl8
{
    extern Sprite img_ai_patrol;

    class AI_Patrol {
    public:
        AI_Patrol(Player& playerRef, Camera& cameraRef);
        ~AI_Patrol(); 

        float angle = 0;
        bool stop = false;
        bool isDead = false;
        bool isAILowerThanPlayer = true;
        vec2 default_pos = { 0, 0 };
        vec2 position = { 0, 0 };
        void setAIPatrolPos(const vec2& pos) { position = pos; }
        bool isTouchingPlayer();
        void getStomped();
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

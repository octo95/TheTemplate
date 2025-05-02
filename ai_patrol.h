#pragma once
#include "ai.h"
#include "camera.h"
#include "player.h"

namespace Tmpl8
{
    extern Sprite img_ai_patrol;

    class AI_Patrol: public AI
    {
        public:
            // Constructor
            AI_Patrol(
                Player& playerRef,
                vec2 spawn_pos,
                Camera& cameraRef
            ) :
                AI(playerRef, spawn_pos),
                camera(cameraRef)
            {
            };

            // Variables
            float angle = 0;
            bool stop = false;
            bool isDead = false;
            bool isAILowerThanPlayer = true;
            vec2 default_pos = { 0, 0 };
            vec2 position = { 0, 0 };

            // Functions
            void setAIPatrolPos(const vec2& pos) { position = pos; }
            bool isTouchingPlayer();
            void getStomped();
            void Patrol(float deltaTime, Collisions* collisions);

        private:
            Camera& camera;
            enum class Direction
            {
                LEFT,
                RIGHT
            };
            Direction direction = Direction::RIGHT;
    };
}

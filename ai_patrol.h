#pragma once
#include "ai.h"
#include "camera.h"
#include "player.h"
#include "tilemap.h"

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

            // Functions
            void setAIPatrolPos(const vec2& pos) { position = pos; }
            void getStomped();
            void Patrol(float deltaTime, Collisions* collisions, TileMap* tilemap);

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

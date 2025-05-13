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
            void getStomped();
            void Patrol(float deltaTime, Collisions* collisions, TileMap* tilemap);

        private:
            Camera& camera;

            // To determine what direction the AI is going.
            enum class Direction{
                LEFT,
                RIGHT
            };
            Direction direction = Direction::RIGHT; // Default direction of the AI patrol on the right.
    };
}

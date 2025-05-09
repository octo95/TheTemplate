#pragma once
#include "player.h"

namespace Tmpl8 {

    enum AIType {
        Follow,
        Copy,
        Patrol
    };

    class Collisions;
    class AI_Copy;
    class AI_Patrol;
    class AI_Follow;

    class AI
    {
    public:
        // Constructor
        AI(
            Player& playerRef,
            vec2 spawn_pos
        ) :
            player(playerRef),
            position(spawn_pos)
        {
        };

        // Variables
        float acceleration = 0;
        bool stop = false;                  // Stops the AI if true (for debug)
        vec2 default_pos = { -500, -500 };  // Make the AI appear out of bounds when not on screen
        vec2 position;
        Player& player;

        // Functions
        bool isTouchingPlayer(Sprite* img);
        void setProperties() {};
    };

    struct AIMap {
        std::vector<AI_Copy> ai_copy_map;
        std::vector<AI_Follow> ai_follow_map;
        std::vector<AI_Patrol> ai_patrol_map;
    };

    void workAI(AIMap* ai_map, float& localTime, Collisions& collisions);
    void drawAI(AIMap* ai_map, Surface* screen, float& deltaTime, Camera& camera);
}
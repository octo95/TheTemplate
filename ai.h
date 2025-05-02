#pragma once
#include "player.h"

namespace Tmpl8 {

    enum AIType {
        Follow,
        Copy,
        Patrol
    };

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
        bool stop = false;          // Stops the AI if true (for debug)
        Player& player;
        float acceleration = 0;
        vec2 default_pos = { -500, -500 }; // Make the AI appear out of bounds when not on screen
        vec2 position;

        // Functions
        bool isTouchingPlayer() { return false; };
        void setProperties() {};
    };
}
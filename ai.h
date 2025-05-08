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
        float acceleration = 0;
        bool stop = false;                  // Stops the AI if true (for debug)
        vec2 default_pos = { -500, -500 };  // Make the AI appear out of bounds when not on screen
        vec2 position;
        Player& player;

        // Functions
        bool isTouchingPlayer(Sprite* img);
        void setProperties() {};
    };
}
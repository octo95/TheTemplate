#pragma once
#include "surface.h"
#include "camera.h"
#include "player.h"
#include "level.h"
#include "gamesound.h"

namespace Tmpl8
{
    extern Sprite img_bell;

    class Bell 
    {
        public:
            // Constructor
            Bell(Level& level);

            // Functions
            void isBellTouchingPlayer(Player* player, GameSound* gamesound);
            void drawBell(Surface* screen, Camera* camera, int map_index, float deltaTime);

        private:
            float frame = 0.0f;             // To determine the frame drawn when the bell rings.
            int bell_loop_index = 0;        // bell_loop_index helps us to determine how many time it rung so that we can make it ring faster on the first loop.
            bool player_touch_bell = false;
            const vec2 BELL_SIZE = img_bell.GetSize();

            Level& level;
            vec2 BELL_POS[5] =              // Place the bell in each level (in tile coordinates for convenience).
            {
                vec2 {21,15},   // LVL 1
                vec2 {1,27},    // LVL 2
                vec2 {48,15},   // LVL 3
                vec2 {20,31},   // LVL 4
                vec2 {51,37}    // LVL 5
            };
            vec2 bell_current_pos = { 0,0 }; // Initialize at (0, 0).
    };
}

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
            void drawBell(Surface* screen, Camera* camera, int map_index);

        private:
            Level& level;
            vec2 BELL_POS[5] =
            {
                vec2 {21,15},
                vec2 {1,26},
                vec2 {48,15},
                vec2 {20,31},
                vec2 {51,37}
            };
            vec2 bell_current_pos = { 0,0 };
    };
}

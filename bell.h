#pragma once
#include "surface.h"
#include "camera.h"
#include "player.h"

namespace Tmpl8
{
    extern Sprite img_bell;

    class Bell 
    {
        public:
            // Constructor
            Bell();

            // Variables
            bool touchedPlayer = false;

            // Functions
            void isBellTouchingPlayer(Player* player);
            void drawBell(Surface* screen, Camera* camera, int map_index);

        private:
            vec2 BELL_POS[5] =
            {
                vec2 {22,30},
                vec2 {0,10},
                vec2 {0,10},
                vec2 {0,30},
                vec2 {2,3}
            };
            vec2 bell_current_pos = { 0,0 };
    };
}

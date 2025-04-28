#pragma once
#include "player.h"
#include "menu.h"

namespace Tmpl8
{
	// External variables
    extern Sprite img_heart;

    class Health 
    {
        public:

			// Constructor
            Health(
                Player& playerRef
            );
			// Functions
            void drawHealthBar(Surface* screen, Menu* menu);

        private:
            Player& player;
    };
}

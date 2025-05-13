#pragma once
#include "player.h"
#include "menu.h"
#include "gamesound.h"

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
            void drawHealthBar(Surface* screen, Menu* menu, GameSound* gamesound, float deltaTime);
            void initHealth(Menu* menu);

            // Variables
            int player_hp = 15;
            bool hp_initialized = false; 
            bool player_killed = false;

        private:
            Player& player;

    };
}
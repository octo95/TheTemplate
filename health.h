#pragma once
#include "player.h"
#include "menu.h"

namespace Tmpl8
{
    extern Sprite img_heart;

    class Health {
    public:
        Health(Player& playerRef);
        void drawHealthBar(Surface* screen, Menu* menu);
    private:
        Player& player;
    };
}

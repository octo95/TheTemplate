#include "health.h"

namespace Tmpl8
{
    Health::Health(Player& playerRef) :
        player(playerRef)
    {}

    Sprite img_heart(new Surface("assets/images/UI/img_heart.png"), 1);

    void Health::drawHealthBar(Surface* screen, Menu* menu)
    {
        if (menu->start_game)
        {
            img_heart.Draw(screen, 0, 0);
        }
    }
}

#include "health.h"

namespace Tmpl8
{
    Health::Health(Player& playerRef) :
        player(playerRef)
    {}

    Sprite img_heart(new Surface("assets/images/UI/img_heart.png"), 1);

    void Health::drawHealthBar(Surface* screen, Menu* menu, GameSound* gamesound)
    {
        if (!menu->start_game) return;

        if (!hp_initialized)
        {
            initHealth(menu);
            hp_initialized = true;
        }

        float offset = 5.0f;
        float healthBarWidth = player_hp * (img_heart.GetWidth() + 5.0f);

        for (int i = 0; i < player_hp; i++)
        {
            vec2 draw_pos = vec2(
                screen->GetWidth() - healthBarWidth + i * (img_heart.GetWidth() + offset),
                offset
            );

            img_heart.Draw(screen, draw_pos);
        }

        if (player_killed)
        {
            gamesound->playSound(gamesound->snd_game_over);
            menu->overMenuOpen = true;
            player_killed = false;
        }

        if (menu->overMenuOpen)
        {
            menu->resume_game = false;
            menu->openEndMenu(screen);
        }
    }

    void Health::initHealth(Menu* menu)
    {
        switch (menu->difficulty)
        {
        case 1: player_hp = 15; break;
        case 2: player_hp = 10; break;
        case 3: player_hp = 1;  break;
        }
    }

}

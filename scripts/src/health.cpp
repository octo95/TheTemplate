#include "../include/health.h"

namespace Tmpl8
{
    Health::Health(Player& playerRef) :
        player(playerRef)
    {}

    // Importing the sprites
    Sprite img_heart(new Surface("assets/images/UI/img_heart.png"), 1);

    void Health::drawHealthBar(Surface* screen, Menu* menu, GameSound* gamesound, float deltaTime)
    {
        // If the game is not started yet or paused, don't show the health bar.
        if (!menu->start_game || menu->pauseMenuOpen) return;

        // If the health is not initialized yet, do so.
        if (!hp_initialized)
        {
            initHealth(menu);
            hp_initialized = true;
        }

        float offset = 5.0f;
        float healthBarWidth = player_hp * (img_heart.GetWidth() + 5.0f);

        // Draw all the hearts
        for (int i = 0; i < player_hp; i++)
        {
            // The drawing position is horizontally offset by i to draw every heart next to 
            // each other with a gap between each.

            vec2 draw_pos = vec2(
                screen->GetWidth() - healthBarWidth + i * (img_heart.GetWidth() + offset),
                offset
            );

            img_heart.Draw(screen, draw_pos);
        }

        // If the player is killed, play the game over SFX, open the Game Over Menu and reset the player's killed state.
        if (player_killed)
        {
            gamesound->playSound(gamesound->snd_game_over);
            menu->overMenuOpen = true;
            player_killed = false;
        }

        // If the game over menu is opened, pause the game and call its function.
        if (menu->overMenuOpen)
        {
            menu->resume_game = false;
            menu->openEndMenu(screen, deltaTime);
        }
    }

    void Health::initHealth(Menu* menu)
    {
        // Initizalises the player's HP based on the difficulty:
        // Easy: 15, Normal: 10, Hard: 5.
        switch (menu->difficulty)
        {
        case 1: player_hp = 15; break;
        case 2: player_hp = 10; break;
        case 3: player_hp = 5;  break;
        }
    }

}

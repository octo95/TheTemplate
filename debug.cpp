#define WIN32_LEAN_AND_MEAN
#include "debug.h"
#include "surface.h"
#include "windows.h"
#include "player.h"
#include <stdio.h>

namespace Tmpl8
{
    // Debug functions
    void Debug::drawHitbox(int x, int y, Surface* screen)
    {
        int squareTop = y + player_img_width / 2 - hitbox_size;
        int squareRight = x + player_img_width / 2 + hitbox_size;
        int squareBottom = y + player_img_width / 2 + hitbox_size;
        int squareLeft = x + player_img_width / 2 - hitbox_size;

        screen->Box(squareLeft, squareTop, squareRight, squareBottom, 0x00FF00);
    }
    void Debug::displayDebug(Surface* screen)
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            // Display the player's hitbox
            drawHitbox(px, py, screen);

            // Display the player's screen coordinates
            char coords[100];
            sprintf(coords, "px: %d, py: %d", px, py);
            screen->Print(coords, 10, 10, 0xFFFF00);
        }
    }

};

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "debug.h"
#include "game.h"
#include "player.h"

namespace Tmpl8
{
    void Debug::drawHitbox(int x, int y, Surface* screen)
    {
        int squareTop = y + player_img_width / 2 - hitbox_size + camera->getCamPos().y;
        int squareRight = x + player_img_width / 2 + hitbox_size + camera->getCamPos().x;
        int squareBottom = y + player_img_width / 2 + hitbox_size + camera->getCamPos().y;
        int squareLeft = x + player_img_width / 2 - hitbox_size + camera->getCamPos().x;

        screen->Box(squareLeft, squareTop, squareRight, squareBottom, 0xFF0000);
    }

    void Debug::displayDebug(Surface* screen, float deltaTime)
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            // PRESS <R> : Teleports player back to default position of the level.
            if (GetAsyncKeyState('R') & 0x8000) defaultPos();

            // PRESS <TAB> : Switches to the next level.
            nextDebugMap();

            // Display the player's hitbox
            drawHitbox(px, py, screen);

            // Display the player's hitbox
            char debug_active_coords[100];
            sprintf(debug_active_coords, "-- DEBUG MODE --");
            screen->Print(debug_active_coords, 10, 10, 0x00FF00);

            // Display the player's screen coordinates
            char player_pos_coords[100];
            sprintf(player_pos_coords, "px: %d, py: %d", px, py);
            screen->Print(player_pos_coords, 10, 30, 0xFFFF00);

            // Display the current map level alongside its default spawn coordinates
            char map_lvl_coords[100];
            sprintf(map_lvl_coords, "current map: %d - (%d, %d)", map.getCurrentLevel(), spawn_px, spawn_py);
            screen->Print(map_lvl_coords, 10, 50, 0xFFFF00);

            // Display the FPS
            char FPS_coords[100];
            sprintf(FPS_coords, "FPS: %d", getFPS(deltaTime));
            screen->Print(FPS_coords, 10, 70, 0xFFFF00);
        }
    }

    int Debug::getFPS(float deltaTime)
    {
        static float timeAccumulator = 0.0f;
        static int frameCounter = 0;
        static int lastFPS = 0;
        static float refreshRate = 0.1f;

        timeAccumulator += deltaTime;
        frameCounter++;

        if (timeAccumulator >= refreshRate)
        {
            lastFPS = (int)(frameCounter / timeAccumulator);
            timeAccumulator = 0.0f;
            frameCounter = 0;
        }

        return lastFPS;
    }

    void Debug::defaultPos()
    {
        Player player;
        int x = spawn_px;
        int y = spawn_py;
        player.setPlayerPos(x, y);
    }

    bool tabPressedLastFrame = false;

    void Debug::nextDebugMap()
    {
        bool isTabDown = GetAsyncKeyState(VK_TAB) & 0x8000;
        if (isTabDown && !tabPressedLastFrame)
        {
            map.setMapIndex(map.incrementMapIndex());
            defaultPos();
        }
        tabPressedLastFrame = isTabDown;
    }
};

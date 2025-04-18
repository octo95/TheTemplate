#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "debug.h"
#include "game.h"
#include "player.h"

namespace Tmpl8
{
    void Debug::drawHitbox(const vec2& pos, Surface* screen)
    {
        int squareTop = (int)(pos.y + player_img_width / 2 - hitbox_size + camera->getCamPos().y);
        int squareRight = (int)(pos.x + player_img_width / 2 + hitbox_size + camera->getCamPos().x);
        int squareBottom = (int)(pos.y + player_img_width / 2 + hitbox_size + camera->getCamPos().y);
        int squareLeft = (int)(pos.x + player_img_width / 2 - hitbox_size + camera->getCamPos().x);
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

            // Get the player position
            vec2 playerPos;
            player->getPlayerPos(playerPos);

            // Display the player's hitbox
            drawHitbox(playerPos, screen);

            // Display debug text
            char debug_active_coords[100];
            sprintf(debug_active_coords, "-- DEBUG MODE --");
            screen->Print(debug_active_coords, 10, 10, 0x00FF00);

            // Display player's position
            char player_pos_coords[100];
            sprintf(player_pos_coords, "px: %.0f, py: %.0f", playerPos.x, playerPos.y);
            screen->Print(player_pos_coords, 10, 30, 0xFFFF00);

            // Display current map level and spawn point
            char map_lvl_coords[100];
            vec2 defaultPos;
            player->getPlayerDefaultPos(defaultPos);
            sprintf(map_lvl_coords, "current map: %d - (%.0f, %.0f)", map->getCurrentLevel(), defaultPos.x, defaultPos.y);
            screen->Print(map_lvl_coords, 10, 50, 0xFFFF00);

            // Display FPS
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
        vec2 defaultPos;
        player->getPlayerDefaultPos(defaultPos);
        player->setPlayerPos(defaultPos);
    }

    bool tabPressedLastFrame = false;

    void Debug::nextDebugMap()
    {
        bool isTabDown = GetAsyncKeyState(VK_TAB) & 0x8000;
        if (isTabDown && !tabPressedLastFrame)
        {
            map->setMapIndex(map->incrementMapIndex());
            defaultPos();
        }
        tabPressedLastFrame = isTabDown;
    }
}

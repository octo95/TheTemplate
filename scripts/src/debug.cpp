#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "../include/debug.h"
#include <cmath>

namespace Tmpl8
{
    Debug::Debug(AIMap& ai_map, Camera& cameraRef, CollectibleMap& collectibleRef, Collisions& collisionRef, Level& levelRef, Menu& menuRef, Player& playerRef, TileMap& tilemapRef, WallMap& wallRef) :
        ai_map(ai_map),
        camera(cameraRef),
        collectible(collectibleRef),
        collisions(collisionRef),
        level(levelRef),
        menu(menuRef),
        player(playerRef),
        tilemap(tilemapRef),
        wall(wallRef)
    {}
    void Debug::displayDebug(Surface* screen, float deltaTime)
    {
        // Enables debug visuals and allows to enable cheats for debugging.
        // Calls all the helper function of this class and additional elements, it is the main debug function.

        if (GetAsyncKeyState(VK_SPACE))
        {
            // PRESS <R> : Teleports player back to restart the current level.
            restartCurrentLevel();

            // PRESS <TAB> : Switches to the next level.
            nextDebugMap();

            // PRESS <S> : Stop the AIs' movement.
            stopAIs();

            // PRESS <D> : Get infinite dashes.
            giveDashes();

            // Display the entities' hitboxes and their distance to the player
            drawPlayerHitbox(player.position, screen);
            drawPlayerTileHitbox(player.position, screen);
            for (AI_Follow& ai : ai_map.ai_follow_map)
            {
                drawHitbox(ai.position, &img_ai_follow, screen);
                drawDistancePlayerToAI(ai.position, img_ai_follow.GetWidth(), screen);
            }
            for (AI_Copy& ai : ai_map.ai_copy_map)
            {
                drawHitbox(ai.position, &img_ai_copy, screen);
                drawDistancePlayerToAI(ai.position, img_ai_copy.GetWidth(), screen);
            }
            for (AI_Patrol& ai : ai_map.ai_patrol_map)
            {
                drawHitbox(ai.position, &img_ai_patrol, screen);
                drawDistancePlayerToAI(ai.position, img_ai_patrol.GetWidth(), screen);
            }

            // Display debug text
            char debug_active_txt[100];
            sprintf(debug_active_txt, "-- DEBUG MODE --");
            screen->Print(debug_active_txt, 10, 10, 0x00FF00);

            // Display player's position
            char player_pos_txt[100];
            sprintf(player_pos_txt, "px: %.0f, py: %.0f", player.position.x, player.position.y);
            screen->Print(player_pos_txt, 10, 30, 0xFFFF00);

            // Display player's tile position
            char player_tpos_txt[100];
            sprintf(player_tpos_txt, "tx: %.0f, ty: %.0f", floor(player.position.x / TILE_SIZE), floor(player.position.y / TILE_SIZE));
            screen->Print(player_tpos_txt, 10, 50, 0xFFFF00);

            // Display current map level and spawn point
            char map_lvl_txt[100];
            sprintf(map_lvl_txt, "current map: %d - (%.0f, %.0f)", tilemap.getCurrentLevel(), player.default_pos.x, player.default_pos.y);
            screen->Print(map_lvl_txt, 10, 70, 0xFFFF00);

            // Display velocity on the player as a line and print it on screen
            drawVelocityNorm(screen);
            
            // Display FPS
            char FPS_txt[100];
            sprintf(FPS_txt, "FPS: %d", getFPS(deltaTime));
            screen->Print(FPS_txt, 10, 110, 0xFFFF00);
        }
    }

    // Draw the player's hitbox in screen coordinates
    void Debug::drawPlayerHitbox(const vec2& pos, Surface* screen)
    {
        vec2 pos1 = pos + vec2(-player.hitbox_radius, -player.hitbox_radius) + camera.getCamPos();
        vec2 pos2 = pos + vec2(player.hitbox_radius, player.hitbox_radius) + camera.getCamPos();

        screen->Box(pos1, pos2, 0xFF0000);
        screen->Box(pos + vec2(-2,-2) + camera.getCamPos(), pos + vec2(2, 2) + camera.getCamPos(), 0x5555DF);
    }

    // Draw the a square around the tile the player is detected in, can be also called the display of the player's tile position.
    void Debug::drawPlayerTileHitbox(const vec2& pos, Surface* screen)
    {
        vec2 floorPos = vec2(std::floor(pos.x / TILE_SIZE), std::floor(pos.y / TILE_SIZE));
        vec2 pos1 =  floorPos * TILE_SIZE + camera.getCamPos();
        vec2 pos2 = pos1 + vec2(TILE_SIZE, TILE_SIZE);

        screen->Box(pos1, pos2, 0x0FF000);
    }

    // Generic drawHitbox function to display the hitbox of the AIs.
    void Debug::drawHitbox(const vec2& pos, Sprite* img, Surface* screen)   
    {
        vec2 pos1 = pos + camera.getCamPos();
        vec2 pos2 = pos1 + vec2(img->GetWidth(), img->GetHeight());

        screen->Box(pos1, pos2, 0xFF0000);
    }

    // Stop the AIs logic if pressing <S>
    void Debug::stopAIs()
    {
        static bool s_wasPressed = false;

        if (GetAsyncKeyState('S') & 0x8000) {
            if (!s_wasPressed) 
            {
                for (AI_Follow& ai : ai_map.ai_follow_map)
                {
                    ai.stop = !ai.stop;
                }
                for (AI_Copy& ai : ai_map.ai_copy_map)
                {
                    ai.stop = !ai.stop;
                }
                for (AI_Patrol& ai : ai_map.ai_patrol_map)
                {
                    ai.stop = !ai.stop;
                }
                s_wasPressed = true;
            }
        }
        else 
        {
            s_wasPressed = false;
        }
    }

    // Get the current FPS of the game based on deltaTime
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
            lastFPS = static_cast<int>(frameCounter / timeAccumulator);
            timeAccumulator = 0.0f;
            frameCounter = 0;
        }
        return lastFPS;
    }

    // Helper function to put back the player to its default position.
    void Debug::defaultPos()
    {
        vec2 defaultPos;
        player.getPlayerDefaultPos(defaultPos);
        player.setPlayerPos(defaultPos);
    }

    // Allows to skip to the next level by pressing <TAB>
    void Debug::nextDebugMap()
    {
        static bool tabPressedLastFrame = false;
        bool isTabDown = GetAsyncKeyState(VK_TAB) & 0x8000;
        if (isTabDown && !tabPressedLastFrame)
        {
            tilemap.incrementMapIndex();
            level.loadLevel(tilemap.getCurrentLevel());
        }
        tabPressedLastFrame = isTabDown;
    }

    // Draws the player's velocity norm at the player's center.
    void Debug::drawVelocityNorm(Surface* screen)
    { 
        float lineSize = 10.0f;
        float start_x = player.position.x + camera.getCamPos().x;
        float start_y = player.position.y + camera.getCamPos().y;
        float end_x = start_x + player.velocity.x * lineSize;
        float end_y = start_y + player.velocity.y * lineSize;

        // Display velocity on screen
        char velocity_txt[100];
        sprintf(velocity_txt, "velocity: (x : %.2f, y : %.2f)", player.velocity.x, player.velocity.y);
        screen->Print(velocity_txt, 10, 90, 0xFFFF00);

        screen->Line(start_x, start_y, end_x, end_y, 0x33F8FF);
    }

    // Restart the level if pressing <R> by reloading it using loadLevel(...)
    void Debug::restartCurrentLevel()
    {
        static bool rKeyWasDown = false;
        bool rKeyIsDown = (GetAsyncKeyState('R') & 0x8000);

        if (rKeyIsDown && !rKeyWasDown)
        {
            level.loadLevel(tilemap.getCurrentLevel());
        }

        rKeyWasDown = rKeyIsDown;
    }

    // Draws a line from the player to the AI.
    void Debug::drawDistancePlayerToAI(vec2 ai_pos, float size, Surface* screen)
    {
        float start_x = player.position.x + camera.getCamPos().x;
        float start_y = player.position.y  - 4.0f + camera.getCamPos().y;
        float end_y = ai_pos.y + size / 2.0f + camera.getCamPos().y;
        float end_x = ai_pos.x + size / 2.0f + camera.getCamPos().x;

        screen->Line(start_x, start_y, end_x, end_y, 0x00FF00);
    }

    // Give the player 9999 dashes if pressing <D>
    void Debug::giveDashes()
    {
        if (GetAsyncKeyState('D') & 0x8000) player.dash_count = 9999;
    }
}

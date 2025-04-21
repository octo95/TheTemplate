#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "debug.h"
#include "game.h"
#include "player.h"

namespace Tmpl8
{
    Debug::Debug(Camera& cameraRef, TileMap& tilemapRef, Player& playerRef, CollectibleMap& collectibleRef, WallMap& wallRef, AI_Follow& ai_followRef, Level& levelRef) :
        camera(cameraRef),
        tilemap(tilemapRef),
        player(playerRef),
        collectible(collectibleRef),
        wall(wallRef),
        ai_follow(ai_followRef),
        level(levelRef)
    {}
    
    void Debug::drawHitbox(const vec2& pos, Surface* screen)
    {
        int squareTop = (int)(pos.y + player_img_width / 2 - hitbox_size + camera.getCamPos().y);
        int squareRight = (int)(pos.x + player_img_width / 2 + hitbox_size + camera.getCamPos().x);
        int squareBottom = (int)(pos.y + player_img_width / 2 + hitbox_size + camera.getCamPos().y);
        int squareLeft = (int)(pos.x + player_img_width / 2 - hitbox_size + camera.getCamPos().x);
        screen->Box(squareLeft, squareTop, squareRight, squareBottom, 0xFF0000);
    }

    void Debug::displayDebug(Surface* screen, float deltaTime)
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            // PRESS <R> : Teleports player back to restart the current level.
            restartCurrentLevel();

            // PRESS <TAB> : Switches to the next level.
            nextDebugMap();

            // Get the player position
            vec2 playerPos;
            player.getPlayerPos(playerPos);

            // Display the entities' hitboxes
            drawHitbox(playerPos, screen);
            drawHitbox(ai_follow.position, screen);

            // Draw the distance between the player and an AI to specify below
            drawDistancePlayerToAI(ai_follow.position, screen);

            // Display debug text
            char debug_active_coords[100];
            sprintf(debug_active_coords, "-- DEBUG MODE --");
            screen->Print(debug_active_coords, 10, 10, 0x00FF00);

            // Display player's position
            char player_pos_coords[100];
            sprintf(player_pos_coords, "px: %.0f, py: %.0f", playerPos.x, playerPos.y);
            screen->Print(player_pos_coords, 10, 30, 0xFFFF00);

            // Display player's position
            char player_tpos_coords[100];
            sprintf(player_tpos_coords, "tx: %.0f, ty: %.0f", playerPos.x / 32, playerPos.y / 32);
            screen->Print(player_tpos_coords, 10, 50, 0xFFFF00);

            // Display current map level and spawn point
            char map_lvl_coords[100];
            vec2 defaultPos;
            player.getPlayerDefaultPos(defaultPos);
            sprintf(map_lvl_coords, "current map: %d - (%.0f, %.0f)", tilemap.getCurrentLevel(), defaultPos.x, defaultPos.y);
            screen->Print(map_lvl_coords, 10, 70, 0xFFFF00);

            // Display velocity on the player as a line and print it on screen
            drawVelocityNorm(screen);

            // Display the collectibles collected
            char collectibles_coords[100];
            sprintf(collectibles_coords, "Jumps left: %d", collectibles_collected);
            screen->Print(collectibles_coords, 10, 110, 0xFFFF00);
            
            // Display FPS
            char FPS_coords[100];
            sprintf(FPS_coords, "FPS: %d", getFPS(deltaTime));
            screen->Print(FPS_coords, 10, 130, 0xFFFF00);
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
        player.getPlayerDefaultPos(defaultPos);
        player.setPlayerPos(defaultPos);
    }

    bool tabPressedLastFrame = false;

    void Debug::nextDebugMap()
    {
        bool isTabDown = GetAsyncKeyState(VK_TAB) & 0x8000;
        if (isTabDown && !tabPressedLastFrame)
        {
            tilemap.incrementMapIndex();
            level.loadLevel(tilemap.getCurrentLevel());
            defaultPos();
        }
        tabPressedLastFrame = isTabDown;
    }

    void Debug::drawVelocityNorm(Surface* screen)
    { 
        float lineSize = 10.0f;
        float start_x = player.position.x + camera.getCamPos().x + player_img_width / 2;
        float start_y = player.position.y + camera.getCamPos().y + player_img_height / 2 - 4;
        float end_x = start_x + player.velocity.x * lineSize;
        float end_y = start_y + player.velocity.y * lineSize;

        // Display velocity on screen
        char velocity_coords[100];
        sprintf(velocity_coords, "velocity: (x : %.2f, y : %.2f)", player.velocity.x, player.velocity.y);
        screen->Print(velocity_coords, 10, 90, 0xFFFF00);

        screen->Line(start_x, start_y, end_x, end_y, 0x33F8FF);
    }

    void Debug::restartCurrentLevel()
    {
        if (GetAsyncKeyState('R') & 0x8000)
        {
            ai_follow.setAIFollowPos(level.AI_FOLLOW_DEFAULT_POS[tilemap.getCurrentLevel()-1]);
            loadCollectiblesForMap(tilemap.getCurrentLevel());
            loadWallsForMap(tilemap.getCurrentLevel());
            defaultPos();
        }
    }

    void Debug::drawDistancePlayerToAI(vec2 ai_pos, Surface* screen)
    {
        int start_x = player.position.x + player_img_width / 2 + camera.getCamPos().x;
        int start_y = player.position.y + (player_img_height / 2 - 4) + camera.getCamPos().y;
        int end_y = ai_pos.y + img_ai_follow.GetHeight() / 2 + camera.getCamPos().y;
        int end_x = ai_pos.x + img_ai_follow.GetWidth() / 2 + camera.getCamPos().x;

        screen->Line(start_x, start_y, end_x, end_y, 0x00FF00);
    }
}

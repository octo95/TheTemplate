#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "debug.h"
#include <cmath>

namespace Tmpl8
{
    Debug::Debug(Camera& cameraRef, TileMap& tilemapRef, Player& playerRef, CollectibleMap& collectibleRef, WallMap& wallRef, AI_Follow& ai_followRef, Level& levelRef, Collisions& collisionRef, Menu& menuRef, AI_Patrol& ai_patrolRef, AI_Copy& ai_copyRef) :
        camera(cameraRef),
        tilemap(tilemapRef),
        player(playerRef),
        collectible(collectibleRef),
        wall(wallRef),
        ai_follow(ai_followRef),
        level(levelRef),
        collisions(collisionRef),
        menu(menuRef),
        ai_patrol(ai_patrolRef),
        ai_copy(ai_copyRef)
    {}
    
    void Debug::drawPlayerHitbox(const vec2& pos, Surface* screen)
    {
        //vec2 offset(player_img_width / 2.0f, player_img_height / 2.0f); 
        //vec2 hitbox_size(hitbox_radius, hitbox_radius);
        //vec2 center = pos + camera.getCamPos() + offset;

        vec2 pos1 = pos + vec2(-hitbox_radius, -hitbox_radius) + camera.getCamPos();
        vec2 pos2 = pos + vec2(hitbox_radius, hitbox_radius) + camera.getCamPos();

        screen->Box(pos1, pos2, 0xFF0000);
        screen->Box(pos + vec2(-2,-2) + camera.getCamPos(), pos + vec2(2, 2) + camera.getCamPos(), 0x5555DF);
    }


    void Debug::drawPlayerTileHitbox(const vec2& pos, Surface* screen)
    {
        vec2 floorPos = vec2(std::floor(pos.x / TILE_SIZE), std::floor(pos.y / TILE_SIZE));
        vec2 pos1 =  floorPos * TILE_SIZE + camera.getCamPos();
        vec2 pos2 = pos1 + vec2(TILE_SIZE, TILE_SIZE);

        screen->Box(pos1, pos2, 0x0FF000);
    }

    void Debug::drawHitbox(const vec2& pos, Sprite* img, Surface* screen)   
    {
        vec2 pos1 = pos + camera.getCamPos();
        vec2 pos2 = pos1 + vec2(img->GetWidth(), img->GetHeight());

        screen->Box(pos1, pos2, 0xFF0000);
    }

    void Debug::displayDebug(Surface* screen, float deltaTime)
    {
        if (GetAsyncKeyState(VK_SPACE))
        {
            // PRESS <R> : Teleports player back to restart the current level.
            restartCurrentLevel();

            // PRESS <TAB> : Switches to the next level.
            nextDebugMap();

            // PRESS <S> : Stop the AIs' movement.
            stopAIs();

            // PRESS <D> : Get infinite dashes.
            toggleInfiniteDashes();

            // Display the entities' hitboxes
            drawPlayerHitbox(player.position, screen);
            drawPlayerTileHitbox(player.position, screen);
            drawHitbox(ai_copy.position, &img_ai_copy, screen);
            drawHitbox(ai_patrol.position, &img_ai_patrol, screen);
            drawHitbox(ai_follow.position, &img_ai_follow, screen);

            // Draw the distance between the player and an AI to specify below
            drawDistancePlayerToAI(ai_copy.position, img_ai_copy.GetWidth(), screen);
            drawDistancePlayerToAI(ai_follow.position, img_ai_follow.GetWidth(), screen);
            drawDistancePlayerToAI(ai_patrol.position, img_ai_patrol.GetWidth(), screen);

            // Display debug text
            char debug_active_txt[100];
            sprintf(debug_active_txt, "-- DEBUG MODE --");
            screen->Print(debug_active_txt, 10, 10, 0x00FF00);

            // Display player's position
            char player_pos_txt[100];
            sprintf(player_pos_txt, "px: %.0f, py: %.0f", player.position.x, player.position.y);
            screen->Print(player_pos_txt, 10, 30, 0xFFFF00);

            // Display player's position
            char player_tpos_txt[100];
            sprintf(player_tpos_txt, "tx: %.0f, ty: %.0f", floor(player.position.x / 32), floor(player.position.y / 32));
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

    void Debug::stopAIs()
    {
        static bool s_wasPressed = false;

        if (GetAsyncKeyState('S') & 0x8000) {
            if (!s_wasPressed) 
            {
                ai_follow.is_following = !ai_follow.is_following;
                ai_patrol.stop = !ai_patrol.stop;
                ai_copy.stop = !ai_copy.stop;
                s_wasPressed = true;
            }
        }
        else 
        {
            s_wasPressed = false;
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
            lastFPS = frameCounter / timeAccumulator;
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
        }
        tabPressedLastFrame = isTabDown;
    }

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

    void Debug::restartCurrentLevel()
    {
        if (GetAsyncKeyState('R') & 0x8000) level.loadLevel(tilemap.getCurrentLevel());
    }

    void Debug::drawDistancePlayerToAI(vec2 ai_pos, int size, Surface* screen)
    {
        int start_x = player.position.x + camera.getCamPos().x;
        int start_y = player.position.y  - 4 + camera.getCamPos().y;
        int end_y = ai_pos.y + size / 2 + camera.getCamPos().y;
        int end_x = ai_pos.x + size / 2 + camera.getCamPos().x;

        screen->Line(start_x, start_y, end_x, end_y, 0x00FF00);
    }

    const char* getTileTypeName(TileType type)
    {
        switch (type)
        {
        case TileType::Collision: return "Collision";
        case TileType::Ice: return "Ice";
        case TileType::Damage: return "Damage";
        case TileType::End: return "End";
        case TileType::None: return "None";
        default: return "Unknown";
        }
    }

    void Debug::toggleInfiniteDashes()
    {
        if (GetAsyncKeyState('D') & 0x8000) player.dash_count = 9999;
    }
}

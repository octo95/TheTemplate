#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "camera.h"
#include "collectible.h"
#include "debug.h"
#include "game.h"
#include "menu.h"
#include "player.h"
#include "tile.h"
#include "ai_follow.h"
#include "tilemap.h"
#include "gamesound.h"
#include <Audio/Sound.hpp>
#include <cstdio>
#include <iostream>
#include <unordered_map>

namespace Tmpl8
{
    // + MAIN GAME LOGIC 


    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert deltaTime to seconds

        // * Clear the screen black every tick
        screen->Clear(0);

        // * Starting the game logic
        if (menu.start_game)
        {
            if (menu.resume_game)
            {
                // * Initialize game logic
                
                // Player logic
                player.getPlayerPos(player_pos);
                player.movePlayer(player_pos, &collisions);
                player.setJumpState(collisions.getJumpState(player_pos));
        
                // Collisions logic
                collisions.manageCollisions(player_pos, screen, &collectible);
                manageWallCollision(player_pos, &gamesound);
                manageCollectibleCollision(player_pos, &gamesound);
        
                // AI logic
                ai_follow.followPlayer(deltaTime);
        
                // Camera logic
                camera.setCamPos(player.camFollowPlayer());
                camera.shakeCamera(deltaTime);

                manageCollectibleRespawn(deltaTime);
            }
            else
            {
                // Pause the time if the game is paused
                deltaTime = 0.0f;
            }
        
            // * Draw the objects on screen
            tilemap.drawMap(screen, camera);
            camera.drawWithCamAndAngle(&img_player, screen, static_cast<int>(player_pos.x), static_cast<int>(player_pos.y + player.PLAYER_DRAW_OFFSET_Y), deltaTime);
            camera.drawWithCamAndAngle(&img_ai_follow, screen, static_cast<int>(ai_follow.position.x), static_cast<int>(ai_follow.position.y), deltaTime);
            drawCollectibleMap(&camera, screen);
            drawWallMap(&camera, screen, &this->wall);
            collisions.drawSplash(screen, player_pos, deltaTime);
            menu.manageMenus(screen);
        
            // * DEBUG: Enabled if pressing <SPACEBAR>
            debug.displayDebug(screen, deltaTime);
        }
        else
        {
            menu.openMainMenu(screen); // As long as we don't start the game, stay in the menu screen
        }
    }

    // + INITIALIZER / SHUTDOWN
    void Game::Init() 
    {
        gamesound.playMusic(gamesound.mus_menu);
    }
    void Game::Shutdown() {}
}
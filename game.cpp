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
#include "ai_patrol.h"

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
                manageCollectibleRespawn(deltaTime);
        
                // AI logic
                ai_follow.followPlayer(deltaTime);
        
                // Camera logic
                camera.setCamPos(player.camFollowPlayer());
                camera.shakeCamera(deltaTime);

            }
            else
            {
                // Pause the time if the game is paused
                deltaTime = 0.0f;
            }
        
            // * Draw the objects on screen
            tilemap.drawMap(screen, camera);            
            drawWallMap(&camera, screen, &this->wall);  
            drawCollectibleMap(&camera, screen);        
            camera.drawWithCamAndAngle(&img_player, screen, (int)player_pos.x, (int)(player_pos.y + player.PLAYER_DRAW_OFFSET_Y), deltaTime, player.angle);
            camera.drawWithCamAndAngle(&img_ai_follow, screen, (int)ai_follow.position.x, (int)ai_follow.position.y, deltaTime, 0);
            camera.drawWithCamAndAngle(&img_ai_patrol, screen, (int)ai_patrol.position.x, (int)ai_patrol.position.y, deltaTime, ai_patrol.angle);
            ai_patrol.Patrol(deltaTime, &collisions);
            collisions.drawSplash(screen, player_pos, deltaTime); 
            bell.drawBell(screen, &camera, tilemap.getCurrentLevel());
            bell.isBellTouchingPlayer(&player);
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
        tilemap.readImageToCharMap();
        gamesound.playMusic(gamesound.mus_menu);
    }
    void Game::Shutdown() {}
}
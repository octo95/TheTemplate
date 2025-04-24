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

// +-----------------------+
// |        TODO           |
// +-----------------------+

/*
* - drawRotated redo to fix black pixels and redo from the ground up
* - do the evil AI
* - load a font to do a counter (otherwise if too hard to do, will do UI with sprites
* 
* + Homework:
* Print on screen collision
* Stop frame by frame logic or do a menu
*/



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
                manageWallCollision(player_pos, &wall);
                manageCollectibleCollision(player_pos, &collectible);
        
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
            camera.drawWithCamAndAngle(&player_img, screen, static_cast<int>(player_pos.x), static_cast<int>(player_pos.y), deltaTime);
            camera.drawWithCamAndAngle(&img_ai_follow, screen, static_cast<int>(ai_follow.position.x), static_cast<int>(ai_follow.position.y), deltaTime);
            drawCollectibleMap(&camera, screen, &this->collectible);
            drawWallMap(&camera, screen, &this->wall);
            menu.manageNextMenu(screen);
        
            // * DEBUG: Enabled if pressing <SPACEBAR>
            debug.displayDebug(screen, deltaTime);
        }
        else
        {
            menu.openMainMenu(screen); // As long as we don't start the game, stay in the menu screen
        }
    }

    // + INITIALIZER / SHUTDOWN
    void Game::Init() {}
    void Game::Shutdown() {}
}

// + NOTES +
// Look up std_font
// Look up scalefont on the server pins
// Move the physics part of move in collisions.cpp to be called at the proper time (move should just do the += to its positions)

// + FIXES +

/*
* - Physics collisions (mostly horizontal)
* - Tiles collisions
* - Manage walls defaults
*/
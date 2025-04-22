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
        deltaTime /= 1000.0f;
        menu.skipAFrame(isTDown);
        // * Clear the screen black every tick
        screen->Clear(0);

        // * Starting the game logic
        if (menu.manageGameStart())
        {
            if (menu.manageGamePause())
            {
                // * Initialize game logic
            
                // Player logic
                player.getPlayerPos(player_pos);
                vec2 half_velocity;
                player.movePlayer(player_pos, half_velocity, &collisions);
                player.setJumpState(collisions.getJumpState(player_pos));

                // Collisions logic
                collisions.manageCollisions(player_pos, half_velocity, screen, &collectible);
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
            camera.drawWithCamAndAngle(&player_img, screen, static_cast<int>(player_pos.x), static_cast<int>(player_pos.y - 4), deltaTime);
            camera.drawWithCamAndAngle(&img_ai_follow, screen, static_cast<int>(ai_follow.position.x), static_cast<int>(ai_follow.position.y - 4), deltaTime);
            drawCollectibleMap(&camera, screen, &this->collectible);
            drawWallMap(&camera, screen, &this->wall);

            if (!menu.manageGamePause())
            {
                static float desaturationMax = 0.5f;
                static float desaturationAmount = 0.0f;
                static float desaturationTime = 0.5f;

                // Increment the amount over <desaturationTime> seconds
                desaturationAmount += (desaturationMax / desaturationTime) * deltaTime; 

                // Stop the incrementation once reaching <desaturationMax>
                if (desaturationAmount > desaturationMax) desaturationAmount = desaturationMax;

                screen->ReduceSaturation(desaturationAmount);

            }
            
            // * DEBUG: Enabled if pressing <SPACEBAR>
            debug.displayDebug(screen, deltaTime);
        }
        else
        {
            menu.drawMenu(screen); // As long as we don't start the game, stay in the menu screen
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
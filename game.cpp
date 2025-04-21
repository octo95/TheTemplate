#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "camera.h"
#include "collectible.h"
#include "debug.h"
#include "game.h"
#include "menu.h"
#include "player.h"
#include "tile.h"
#include "tilemap.h"
#include "ai_follow.h"

#include <unordered_map>

// +-----------------------+
// |        TODO           |
// +-----------------------+

/*
* - drawRotated redo to fix black pixels and redo from the ground up
* - make setPlayerPos and getPlayerPos (same for default functions) cleaner, the default ones should have in parameter the index of the map to remove the vec2 in init
* - work on physics bounces
* - do the evil AI
* - put playerDefaultPos and aiDefaultPos in arrays in tilemap.h
* - load a font to do a counter (otherwise if too hard to do, will do UI with sprites
* - mouse hover enter button
*/

namespace Tmpl8
{
    // + Initializer / Shutdown
    void Game::Init()
    {
        vec2 initial_pos = { 400, 10 };
        player.setPlayerDefaultPos(initial_pos);
        player.setPlayerPos(initial_pos);
        tilemap.loadLevel(1);
    }

    void Game::Shutdown() {}

    // + MAIN GAME LOGIC 
    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert deltaTime to seconds

        // * Clear the screen black every tick
        screen->Clear(0);

        // * Starting the game logic
        if (menu.startGame())
        {
            vec2 new_pos;
            player.getPlayerPos(new_pos);

            // * Initialize game logic
            camera.setCamPos(player.camFollowPlayer());
            ai_follow.followPlayer(deltaTime);
            player.movePlayer(new_pos);
            bool is_colliding = player.manageCollisions(new_pos, screen, &collectible);

            ai_follow.setTouchingPlayer();
            manageWallCollision(new_pos, &wall);
            manageCollectibleCollision(new_pos, &collectible);
            if (is_colliding) camera.Shake();
            camera.camShake(deltaTime);  

            // * Draw the objects on screen
            tilemap.drawMap(screen, camera);
            camera.drawWithCamAndAngle(&player_img, screen, static_cast<int>(new_pos.x), static_cast<int>(new_pos.y - 4), deltaTime);
            camera.drawWithCamAndAngle(&img_ai_follow, screen, static_cast<int>(ai_follow_pos.x), static_cast<int>(ai_follow_pos.y - 4), deltaTime);
            drawCollectibleMap(&camera, screen, &this->collectible);
            drawWallMap(&camera, screen, &this->wall);

            // * DEBUG: Enabled if pressing <spacebar>
            debug.displayDebug(screen, deltaTime);

        }
        else
        {
            menu.drawMenu(screen); // As long as we don't start the game, stay in the menu screen
        }
    }
}
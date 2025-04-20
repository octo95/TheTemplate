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

#include <unordered_map>

// +-----------------------+
// |        TODO           |
// +-----------------------+
// 
// - drawRotated redo to fix black pixels and redo from the ground up
// - fix defaultPos (for the 10th time)
// - work on physics bounces
// - do the evil AI

namespace Tmpl8
{
    // + Initializer / Shutdown
    void Game::Init()
    {
        tilemap.loadLevel(1);
    }

    void Game::Shutdown() {}

    // + MAIN GAME LOGIC 
    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert deltaTime to seconds

        // * Clear the screen black every tick
        screen->Clear(0);

        // * Stay in the menu until the player starts the game
        // if (GetAsyncKeyState(VK_RETURN)) start_game = true;

        // * Starting the game logic
        if (menu.startGame())
        {
            vec2 new_pos;
            player.getPlayerPos(new_pos); // Fetch current player position to modify it

            // * Initialize game logic
            camera.setCamPos(player.camFollowPlayer());
            player.movePlayer(new_pos);
            bool is_colliding = player.manageCollisions(new_pos, screen, &collectible);

            manageWallCollision(new_pos, &wall);
            manageCollectibleCollision(new_pos, &collectible);
            if (is_colliding) camera.Shake();
            camera.camShake(deltaTime);  

            // * Draw the objects on screen
            tilemap.drawMap(screen, camera);
            camera.drawWithCamAndAngle(&player_img, screen, static_cast<int>(new_pos.x), static_cast<int>(new_pos.y - 4), deltaTime);
            drawCollectibleMap(&camera, screen, &this->collectible);
            drawWallMap(&camera, screen, &this->wall);

            // * DEBUG: Enabled if pressing <spacebar>
            debug.displayDebug(screen, deltaTime);

            // ROTATION TEST
            // player.rotatePlayer(screen, deltaTime * 40.0f);
        }
        else
        {
            menu.drawMenu(screen); // As long as we don't start the game, stay in the menu screen
        }
    }
}
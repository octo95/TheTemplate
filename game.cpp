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



namespace Tmpl8
{
    // + Initializer / Shutdown
    void Game::Init()
    {
        loadAllCollectibles(); 
        tilemap.setMapIndex(1);
        loadCollectiblesForMap(1);
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

            manageCollectibleCollision(new_pos, &collectible);
            if (is_colliding) camera.Shake();
            camera.camShake(deltaTime);  

            // * Draw the objects on screen
            tilemap.drawMap(screen, camera);
            camera.drawWithCam(&player_img, screen, static_cast<int>(new_pos.x), static_cast<int>(new_pos.y-4));
            drawCollectibleMap(&camera, screen, &this->collectible);

            // * DEBUG: Enabled if pressing <spacebar>
            debug.displayDebug(screen, deltaTime);
        }
        else
        {
            menu.drawMenu(screen); // As long as we don't start the game, stay in the menu screen
        }
    }
}
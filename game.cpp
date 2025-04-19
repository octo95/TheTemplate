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
        tilemap.setMapIndex(1); // Default: start on the map of Level 1
        this->collectibles = initializeCollectibleMap(1);
    }

    void Game::Shutdown() {}

    // + MAIN GAME LOGIC 
    void Game::Tick(float deltaTime)
    {
        Game* game = this;

        deltaTime /= 1000.0f; // Convert deltaTime to seconds

        // * Clear the screen black every tick
        screen->Clear(0);

        // * Stay in the menu until the player starts the game
        if (GetAsyncKeyState(VK_RETURN)) start_game = true;

        // * Starting the game logic
        if (start_game)
        {
            vec2 new_pos;
            player.getPlayerPos(new_pos); // Fetch current player position to modify it

            // * Initialize game logic
            player.setMap(&tilemap);
            debug.setMap(&tilemap);
            tilemap.setPlayer(&player);
            camera.setCamPos(player.camFollowPlayer());
            player.movePlayer(new_pos);
            bool is_colliding = player.manageCollisions(new_pos, screen, &collectibles);

            manageCollectibleCollision(new_pos, &collectibles);
            if (is_colliding) camera.Shake();
            camera.camShake(deltaTime);

            
            // game.setTileMap(tilemap);

            // * Draw the objects on screen
            tilemap.drawMap(screen, camera);
            camera.drawWithCam(&player_img, screen, static_cast<int>(new_pos.x), static_cast<int>(new_pos.y-4));
            drawCollectibleMap(&camera, screen, &this->collectibles);

            // * DEBUG: Enabled if pressing <spacebar>
            debug.setPlayer(&player);
            debug.setCamera(&camera);
            debug.displayDebug(screen, deltaTime);
        }
        else
        {
            menu.drawMenu(screen); // As long as we don't start the game, stay in the menu screen
        }
    }
}


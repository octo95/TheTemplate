// +------------+
// |    TODO    |
// +------------+

/*
* - Better physics
* - Jump button
* - Add timer
* - Add collectible
*/

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

namespace Tmpl8
{
    // Variables
    bool start_game = false;

    // + Initializer / Shutdown
    void Game::Init() 
    {
        map.setMapIndex(1); // Default: start on the map of Level 1
    }
    void Game::Shutdown() {}

    // + MAIN OBJECTS
    Player player;
    Debug debug;
    TileMap map;
    Menu menu;
    Collectible collectible;

    // + MAIN GAME LOGIC 
    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert deltaTime in seconds.

        // * Clear the screen black every tick.
        screen->Clear(0);

        // * Stay in the menu until the player starts the game.
        if (GetAsyncKeyState(VK_RETURN)) start_game = true;

        // * Starting the game logic.
        if (start_game)
        {
            int nx = px, ny = py; // Update the player's new position every tick.

            // * Initialize game logic
            camera.setCamPos(player.camFollowPlayer());
            player.movePlayer(nx, ny);
            player.manageCollisions(nx, ny, screen);
            if (player.manageCollisions(nx, ny, screen)) camera.Shake();
            camera.camShake(deltaTime);

            // * Draw the objects on screen
            map.drawMap(screen, camera);
            camera.drawWithCam(&player_img, screen, px, py);
            camera.drawWithCam(&img_collectible, screen, collectible.setCPos(13), collectible.setCPos(5));

            // * DEBUG: Enabled if pressing <spacebar>.
            debug.setCamera(&camera);
            debug.displayDebug(screen, deltaTime);
        }
        else menu.drawMenu(screen); // As long as we don't start the game, stay in the menu screen.
    }
}
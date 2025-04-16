// +------------+
// |    TODO    |
// +------------+

/*
* - Fix git missing sdl2.lib
* - Better physics
* - Jump button
* - Add timer
* - Add collectible
*/

#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "SDL_events.h"
#include <stdio.h>
#include <iostream>
#include "surface.h"
#include "template.h"
#include "game.h"
#include "tile.h"
#include "tilemap.h"
#include "player.h"
#include "debug.h"
#include "menu.h"
#include "camera.h"

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
    // Debug debug;
    TileMap map;
    Menu menu;

    void Game::startGame(float deltaTime)
    {
        if (GetAsyncKeyState(VK_RETURN)) start_game = true;
        if (start_game)
        {

            camera.setCamPos(player.camFollowPlayer());

            int nx = px, ny = py; // Update the player's new position every tick.
     
            player.movePlayer(nx, ny);
            player.manageCollisions(nx, ny, screen);
            if (player.manageCollisions(nx, ny, screen))
            {
                camera.Shake();
            }
            camera.camShake(deltaTime);

            map.drawMap(screen, camera);
            player_img.Draw(screen, px + camera.getCamPos().x, py + camera.getCamPos().y);

            //// * DEBUG: Enabled if pressing <spacebar>.
            //debug.displayDebug(screen);
        }
        else menu.drawMenu(screen);
    }

    // + MAIN GAME LOGIC 
    void Game::Tick(float deltaTime)
    {
        // * Clear the screen black every tick and start the game.
        deltaTime /= 1000.0f;
        screen->Clear(0);
        startGame(deltaTime);
    }
}
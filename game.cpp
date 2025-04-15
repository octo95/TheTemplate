// +------------+
// |    TODO    |
// +------------+

/*
* - Fix git missing sdl2.lib
* - Do camera.cpp / camera.h
* - Better physics
* - Jump button
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

    void startGame(Surface* screen)
    {
        if (GetAsyncKeyState(VK_RETURN)) start_game = true;
        if (start_game)
        {
            // * Draw the map
            map.drawMap(screen);

            // * Player logic.
            int nx = px, ny = py; // Update the player's new position every tick.
            player.movePlayer(nx, ny);
            player_img.Draw(screen, px + CAM_OFFSET_X, py + CAM_OFFSET_Y);
            player.manageCollisions(nx, ny, screen);

            // * DEBUG: Enabled if pressing <spacebar>.
            debug.displayDebug(screen);
        }
        else menu.drawMenu(screen);
    }

    // + MAIN GAME LOGIC 
    void Game::Tick(float deltaTime)
    {
        // * Clear the screen black every tick and start the game.
        screen->Clear(0);
        startGame(screen);
    }
}
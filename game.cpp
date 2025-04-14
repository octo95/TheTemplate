// +------------+
// |    TODO    |
// +------------+

/*
* - Fix git missing sdl2.lib
* - Implement vertical camera
* - Better physics
* - Jump button
*/

#define WIN32_LEAN_AND_MEAN
#include "surface.h"
#include "template.h"
#include "game.h"
#include "tile.h"
#include "tilemap.h"
#include "windows.h"
#include "player.h"
#include "debug.h"
#include <stdio.h>

namespace Tmpl8
{
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

    // + MAIN GAME LOGIC 
    void Game::Tick(float deltaTime)
    {
        // * Clear the screen black every tick and draw the map.
        screen->Clear(0);
        map.drawMap(screen);

        // * Player logic.
        int nx = px, ny = py; // Update the player's new position every tick.
        player.movePlayer(nx, ny);
        player_img.Draw(screen, px, py);
        player.manageCollisions(nx, ny, screen);

        // * DEBUG: Enabled if pressing <spacebar>.
        debug.displayDebug(screen);
    }
}
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
    void Game::Init() {}
    void Game::Shutdown() {}

    Player player;
    Debug debug;

    // MAIN GAME LOGIC
    void Game::Tick(float deltaTime)
    {
        // * Drawing the map and clearing the screen every tick.
        screen->Clear(0);
        map.drawMap(screen);

        // * Player logic.
        int nx = px, ny = py; // Update the player's new position every tick.
        player.movePlayer(nx, ny, 1);
        player_img.Draw(screen, px, py);
        player.manageCollisions(nx, ny, screen);

        // * DEBUG: Enabled if pressing <spacebar>.
        debug.displayDebug(screen);
    }
}
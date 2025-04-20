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
        //player.setMap(&tilemap);
        tilemap.setPlayer(&player);
        debug.setMap(&tilemap);
        debug.setPlayer(&player);
        debug.setCamera(&camera);
        debug.setCollectible(&collectibles);
    }

    void Game::Shutdown() {}

    // + MAIN GAME LOGIC 
    void Game::Tick(float deltaTime)
    {
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
            camera.setCamPos(player.camFollowPlayer());
            player.movePlayer(new_pos);
            bool is_colliding = player.manageCollisions(new_pos, screen, &collectibles);

            manageCollectibleCollision(new_pos, &collectibles);
            if (is_colliding) camera.Shake();
            camera.camShake(deltaTime);  

            // * Draw the objects on screen
            tilemap.drawMap(screen, camera);
            camera.drawWithCam(&player_img, screen, static_cast<int>(new_pos.x), static_cast<int>(new_pos.y-4));
            drawCollectibleMap(&camera, screen, &this->collectibles);

            // * DEBUG: Enabled if pressing <spacebar>
            debug.displayDebug(screen, deltaTime);
        }
        else
        {
            menu.drawMenu(screen); // As long as we don't start the game, stay in the menu screen
        }
    }
}

/*
Dream:

- War france invaded, I'm at my apartment and get ready to leave or smt smt
- Battle with groups of 3 like hunger games levels, with you and my friend. 1 of them is on water around a swirling thing like pirate of the carabeans
We win even tho everyone else was super good just bcse we lucky and others' hubris or smt
- Mario Kart World, Mario has a new skin that's with colors that are not very saturated or anything, more bland and someone complains a lot bcse usually
Nintendo makes colors super flashy and all. Also it releases tmr
- Had to write down my notes on fucking VSC bcse Obsidian not working, Discord you see it and Obsidian on PC too and notepad too somehow???

*/
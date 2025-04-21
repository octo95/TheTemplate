#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "camera.h"
#include "collectible.h"
#include "debug.h"
#include "game.h"
#include "menu.h"
#include "player.h"
#include "tile.h"
#include "ai_follow.h"
#include "tilemap.h"

#include <unordered_map>

// +-----------------------+
// |        TODO           |
// +-----------------------+

/*
* - drawRotated redo to fix black pixels and redo from the ground up
* - work on physics bounces
* - do the evil AI
* - load a font to do a counter (otherwise if too hard to do, will do UI with sprites
* - CheckTop collisions
*/

namespace Tmpl8
{
    // + Initializer / Shutdown
    void Game::Init()
    {
        //player.setPlayerPos({ 400, 10 });
        level.loadLevel(1);
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
            // * Initialize game logic
            vec2 player_pos;

            player.getPlayerPos(player_pos);

            camera.setCamPos(player.camFollowPlayer());
            ai_follow.followPlayer(deltaTime);
            player.movePlayer(player_pos);
            collisions.playerCollisionsAI();
            player.setJumpState(collisions.getJumpState(player_pos));
            bool is_colliding = collisions.manageCollisions(player_pos, screen, &collectible);
            manageWallCollision(player_pos, &wall);
            manageCollectibleCollision(player_pos, &collectible);
            if (is_colliding) camera.Shake();
            camera.camShake(deltaTime);  

            // * Draw the objects on screen
            tilemap.drawMap(screen, camera);
            camera.drawWithCamAndAngle(&player_img, screen, static_cast<int>(player_pos.x), static_cast<int>(player_pos.y - 4), deltaTime);
            camera.drawWithCamAndAngle(&img_ai_follow, screen, static_cast<int>(ai_follow.position.x), static_cast<int>(ai_follow.position.y - 4), deltaTime);
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
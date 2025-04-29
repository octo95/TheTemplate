#include "game.h"

namespace Tmpl8
{
    // + MAIN GAME LOGIC 


    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert deltaTime to seconds

        // * Clear the screen black every tick
        screen->Clear(0);

        // * Starting the game logic
        if (menu.start_game)
        {
            if (menu.resume_game)
            {
                // * Initialize game logic
                
                // Player logic
                player.getPlayerPos(player_pos);
                player.movePlayer(player_pos, &collisions);
                player.setJumpState(collisions.getJumpState(player_pos));
        
                // Collisions logic
                collisions.manageCollisions(player_pos, screen, &collectible);
                manageWallCollision(player_pos, &gamesound);
                manageCollectibleCollision(player_pos, &gamesound);
                manageCollectibleRespawn(deltaTime);
        
                // AI logic
                ai_copy.setProperties();
                ai_copy.playerBuffer.add(player_pos, player.acceleration);
                ai_follow.followPlayer(deltaTime);
                ai_patrol.Patrol(deltaTime, &collisions);
        
                // Camera logic
                camera.setCamPos(player.camFollowPlayer());
                camera.shakeCamera(deltaTime);

                // Bell logic
                bell.isBellTouchingPlayer(&player);

            }
            else
            {
                // Pause the time if the game is paused
                deltaTime = 0.0f;
            }
        
            // * Draw the objects on screen
            tilemap.drawMap(screen, camera);            
            drawWallMap(&camera, screen, &this->wall);  
            drawCollectibleMap(&camera, screen);       
            camera.drawPlayer(&img_player, screen, player_pos, deltaTime, player.acceleration);
            camera.drawAICopy(&img_ai_copy, screen, ai_copy.position, deltaTime, ai_copy.acceleration);
			img_ai_follow.DrawRotated(screen, ai_follow.position + camera.getCamPos(), ai_follow.angle);
			if(!ai_patrol.isDead) img_ai_patrol.DrawRotated(screen, ai_patrol.position + camera.getCamPos(), ai_patrol.angle);
            collisions.drawSplash(screen, player_pos, deltaTime); 
            bell.drawBell(screen, &camera, tilemap.getCurrentLevel());
            menu.manageMenus(screen);
        
            // * DEBUG: Enabled if pressing <SPACEBAR>
            debug.displayDebug(screen, deltaTime);
        }
        else
        {
            menu.openMainMenu(screen); // As long as we don't start the game, stay in the menu screen
        }
    }

    // + INITIALIZER / SHUTDOWN
    void Game::Init() 
    {
        tilemap.readImageToCharMap();
        gamesound.playMusic(gamesound.mus_menu);
    }
    void Game::Shutdown() {}
}
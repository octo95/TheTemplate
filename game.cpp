#include "game.h"
#include "text.h"

namespace Tmpl8
{
    // + MAIN GAME LOGIC 


    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert deltaTime to seconds
        localTime = deltaTime;

        vec2 new_pos;
        //frameTime += deltaTime;
        //if (frameTime < 1 / 60.0f) return;
        //frameTime = 0.0f;

        // * Clear the screen black every tick
        screen->Clear(0);

        // * Starting the game logic
        if (menu.start_game)
        {
            if (menu.resume_game)
            {
                // * Initialize game logic
                
                // Player logic
                new_pos = player.movePlayer(&collisions, localTime);
                player.setJumpState(collisions.getJumpState(new_pos));
                collisions.manageCollisions(new_pos);
        
                // Collisions logic
                manageWallCollision(&player, &gamesound);
                manageCollectibleCollision(&player, &gamesound, &menu);
                manageCollectibleRespawn(localTime);
                
                // AI logic
                //workAI(ai_map, ...);
                ai_copy.setProperties();
                ai_copy.playerBuffer.add(new_pos, player.angular_acceleration);
                ai_follow.followPlayer(localTime);
                ai_patrol.Patrol(localTime, &collisions);
        
                // Camera logic
                camera.setCamPos(player.camFollowPlayer(&tilemap));
                camera.shakeCamera(localTime);

                // Bell logic
                bell.isBellTouchingPlayer(&player, &gamesound);

            }
            else
            {
                // Pause the time if the game is paused
                localTime = 0.0f;
            }


        
            // * Draw the objects on screen
            camera.drawWithCam(tilemap.current_map_draw, screen, vec2(0, 0));
            drawWallMap(&camera, screen, &this->wall);  
            drawCollectibleMap(&camera, screen, localTime);       
            camera.drawPlayer(&img_player, screen, player.position, localTime, player.angular_acceleration);
            camera.drawAICopy(&img_ai_copy, screen, ai_copy.position, localTime, ai_copy.acceleration);
			img_ai_follow.DrawRotated(screen, ai_follow.position + camera.getCamPos(), ai_follow.angle);
			if(!ai_patrol.isDead) img_ai_patrol.DrawRotated(screen, ai_patrol.position + camera.getCamPos(), ai_patrol.angle);
            bell.drawBell(screen, &camera, tilemap.getCurrentLevel());
            menu.manageMenus(screen, deltaTime);
            menu.scoreInGame(screen, localTime);
            menu.dashCountInGame(screen, localTime);
            menu.timerInGame(screen, deltaTime);
            collisions.drawSplash(screen, new_pos, localTime);
            health.drawHealthBar(screen, &menu, &gamesound);
            menu.openScoreMenu(screen, deltaTime);

            // * DEBUG: Enabled if pressing <SPACEBAR>
            debug.displayDebug(screen, localTime);  
        }
        else
        {
            menu.openMainMenu(screen, localTime); // As long as we don't start the game, stay in the menu screen
        }
    }

    // + INITIALIZER / SHUTDOWN
    void Game::Init() 
    {
        tilemap.readImageToMap(&img_map1_data_read);
        gamesound.playMusic(gamesound.mus_menu);
    }
    void Game::Shutdown() 
    {
    }
}
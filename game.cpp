#include "game.h"

namespace Tmpl8
{
    // +-----------------+
    // | INITIALIZE GAME |
    // +-----------------+

    void Game::Init()
    {
        // Initialize some elements before starting the game logic.
        tilemap.readImageToMap(&img_map1_data_read);
        gamesound.playMusic(gamesound.mus_menu);
    }

    // +-----------------+
    // |    GAME LOGIC   |
    // +-----------------+

    void Game::GameLogic()
    {
        // Player logic
        new_pos = player.movePlayer(&collisions, localTime);
        player.setJumpState(collisions.getJumpState(new_pos));
        collisions.manageCollisions(new_pos);
        player.restrictPlayerInMap(&tilemap);

        // Collisions logic
        manageWallCollision(&player, &gamesound);
        manageCollectibleCollision(&player, &gamesound, &menu, &health, &tilemap);
        manageCollectibleRespawn(localTime, &player);

        // AI logic
        workAI(&ai_map, localTime, collisions, tilemap);

        // Camera logic
        camera.setCamPos(player.camFollowPlayer(&tilemap));
        camera.shakeCamera(localTime);

        // Bell logic
        bell.isBellTouchingPlayer(&player, &gamesound);
    }

    // +-----------------+
    // |    DRAW GAME    |
    // +-----------------+

    // The game is drawn layer by layer, the first being called are the most in the background 
    // and the last ones are the most in the foreground, the order is the following:
    /* --------------------------------------------------------------------------------------
    * -  1. Background
    * -  2. Clouds
    * -  3. Map
    * -  4. Collectibles
    * -  5. Player
    * -  6. AIs
    * -  7. Bells
    * -  8. Menus
    * -  9. UI
    * - 10. Debug
    */

    void Game::GameDraw(float deltaTime)
    {
        // Clear the screen black every tick
        screen->Clear(0);

        // Background
        camera.drawWithCam(tilemap.current_map_draw_bg, screen, vec2(-50.0f, -50.0f));
        drawCloudMap(&camera, screen, &this->cloud, &tilemap, localTime);
        if (!tilemap.secret_collected)  camera.drawWithCam(tilemap.current_map_draw, screen, vec2(0, 0));
        if (tilemap.secret_collected)   camera.drawWithCam(&img_map5_draw_alt, screen, vec2(0, 0));
        drawWallMap(&camera, screen, &this->wall);
        drawCollectibleMap(&camera, screen, localTime);

        // Objects
        camera.drawPlayer(&img_player, screen, player.position, localTime, player.angular_acceleration);
        collisions.drawSplash(screen, new_pos, localTime);
        drawAI(&ai_map, screen, localTime, camera);
        bell.drawBell(screen, &camera, tilemap.getCurrentLevel(), deltaTime);

        // Menus
        menu.manageMenus(screen, deltaTime);

        // UI
        menu.scoreInGame(screen, localTime);
        menu.dashCountInGame(screen, localTime);
        menu.timerInGame(screen, deltaTime);
        menu.openResultsMenu(screen, deltaTime);
        health.drawHealthBar(screen, &menu, &gamesound, localTime);

        // * DEBUG: Enabled if pressing <SPACEBAR>
        debug.displayDebug(screen, localTime);
    }

    // +-----------------+
    // |    GAME TICK    |
    // +-----------------+

    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f;   // Convert deltaTime to seconds
        localTime = deltaTime;  // Seperate deltaTime logic for pause

        // * Cap the framerate (Unused)
        //frameTime += deltaTime;
        //if (frameTime < 1 / 60.0f) return;
        //frameTime = 0.0f;

        // Starting the game logic
        if (menu.start_game)
        {
            if (menu.resume_game)
            {
                // Enable the game logic if the game is not paused
                GameLogic();
            }
            else
            {
                // Pause the time if the game is paused
                localTime = 0.0f;
            }

            // Draw the objects on screen even when the game is paused
            GameDraw(deltaTime);
        }
        else
        {
            // As long as we don't start the game, stay in the menu screen
            menu.openMainMenu(screen, localTime); 
        }
    }

    // +-----------------+
    // |    CLOSE GAME   |
    // +-----------------+

    void Game::Shutdown() 
    {
        // Press <ESC> to quit the game.
        printf("* Closing game... *\n");
    }
}
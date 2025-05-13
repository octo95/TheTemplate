// +----------------------------------------------------------------------------+
// | _____ ____  _   _ ___ _____ ____     ____ ___  _     _     ___ ____  _____ |
// ||  ___|  _ \| | | |_ _|_   _/ ___|   / ___/ _ \| |   | |   |_ _|  _ \| ____||
// || |_  | |_) | | | || |  | | \___ \  | |  | | | | |   | |    | || | | |  _|  |
// ||  _| |  _ <| |_| || |  | |  ___) | | |__| |_| | |___| |___ | || |_| | |___ |
// ||_|   |_| \_\\___/|___| |_| |____/   \____\___/|_____|_____|___|____/|_____||
// |                                                                            |
// +----------------------------------------------------------------------------+

// A game for the BUas programming intake for the academic year of 2025 / 2026.

// * CREDITS:
// -----------
// Game by Niels DUNOU.
// Art assets made for the game by gegega.
// Music and sound design made for the game by Synth Mints.
// Using background assets from: https://free-game-assets.itch.io/free-summer-pixel-art-backgrounds.
// Using the template Tmpl8, BUAS version https://www.buas.nl/games (IGAD/BUAS(NHTV)/UU - Jacco Bikker - 2006-2020)
// Using the following additional libraries:
// - Audio library made by Jeremiah: https://github.com/jpvanoosten/Audio
// - stb_easy_fonts:https://github.com/nothings/stb/blob/master/stb_easy_font.h
// Contains references to medias owned by their respective copyright holders.

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
        collisions.manageCollisions(new_pos);

        player.setJumpState(collisions.getJumpState(new_pos));
        player.manageJump(localTime);
        player.applyGravity(localTime);
        player.manageDash(localTime);
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

        // * Cap the framerate
        frameTime += deltaTime;
        if (frameTime < 1 / 144.0f) return;
        frameTime = 0.0f;

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
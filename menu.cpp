#define WIN32_MEAN_AND_LEAN
#include "windows.h"
#include "menu.h"

namespace Tmpl8
{
    Menu::Menu(Level& levelRef, Player& playerRef, TileMap& tilemapRef, GameSound& gamesoundRef, Text& textRef, Health& healthRef) :
        level(levelRef),
        player(playerRef),
        tilemap(tilemapRef),
        gamesound(gamesoundRef),
        text(textRef),
        health(healthRef)
    {}

    //// + MAIN MENU
    //Sprite img_menu_main_bg(new Surface("assets/images/menus/main_menu/img_menu_main_bg.png"), 1);
    //Sprite img_menu_main_start(new Surface("assets/images/menus/main_menu/img_menu_main_start.png"), 1);
    //Sprite img_menu_main_lvl1(new Surface("assets/images/menus/main_menu/img_menu_main_lvl1.png"), 1);
    //Sprite img_menu_main_lvl2(new Surface("assets/images/menus/main_menu/img_menu_main_lvl2.png"), 1);
    //Sprite img_menu_main_lvl3(new Surface("assets/images/menus/main_menu/img_menu_main_lvl3.png"), 1);
    //Sprite img_menu_main_lvl4(new Surface("assets/images/menus/main_menu/img_menu_main_lvl4.png"), 1);
    //Sprite img_menu_main_lvl5(new Surface("assets/images/menus/main_menu/img_menu_main_lvl5.png"), 1);
    //Sprite img_menu_main_difficulty_easy(new Surface("assets/images/menus/main_menu/img_menu_main_difficulty_easy.png"), 1);
    //Sprite img_menu_main_difficulty_medium(new Surface("assets/images/menus/main_menu/img_menu_main_difficulty_medium.png"), 1);
    //Sprite img_menu_main_difficulty_hard(new Surface("assets/images/menus/main_menu/img_menu_main_difficulty_hard.png"), 1);
    //Sprite img_menu_main_pro_tip(new Surface("assets/images/menus/main_menu/img_menu_main_pro_tip.png"), 1);

    //    // - Info panel
    //Sprite img_menu_main_info_bg(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_bg.png"), 1);
    //Sprite img_menu_main_info_info(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_info.png"), 1);
    //Sprite img_menu_main_info_info_alt(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_info_alt.png"), 1);
    //Sprite img_menu_main_info_quit(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_quit.png"), 1);
    //Sprite img_menu_main_info_quit_alt(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_quit_alt.png"), 1);

    //    // - Hover
    //Sprite img_menu_main_start_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_start_alt.png"), 1);
    //Sprite img_menu_main_lvl1_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl1_alt.png"), 1);
    //Sprite img_menu_main_lvl2_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl2_alt.png"), 1);
    //Sprite img_menu_main_lvl3_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl3_alt.png"), 1);
    //Sprite img_menu_main_lvl4_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl4_alt.png"), 1);
    //Sprite img_menu_main_lvl5_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl5_alt.png"), 1);
    //Sprite img_menu_main_difficulty_easy_hover(new Surface("assets/images/menus/main_menu/hover/img_menu_main_difficulty_easy_hover.png"), 1);
    //Sprite img_menu_main_difficulty_medium_hover(new Surface("assets/images/menus/main_menu/hover/img_menu_main_difficulty_medium_hover.png"), 1);
    //Sprite img_menu_main_difficulty_hard_hover(new Surface("assets/images/menus/main_menu/hover/img_menu_main_difficulty_hard_hover.png"), 1);

    // + NEXT MENU
    Sprite img_menu_next_bg(new Surface("assets/images/menus/next_menu/img_menu_next_bg.png"), 1);
    Sprite img_menu_next_next(new Surface("assets/images/menus/next_menu/img_menu_next_next.png"), 1);
    Sprite img_menu_next_menu(new Surface("assets/images/menus/next_menu/img_menu_next_menu.png"), 1);

        // - Hover
    Sprite img_menu_next_next_alt(new Surface("assets/images/menus/next_menu/img_menu_next_next_alt.png"), 1);
    Sprite img_menu_next_menu_alt(new Surface("assets/images/menus/next_menu/img_menu_next_menu_alt.png"), 1);

    // + PAUSE MENU
    Sprite img_menu_pause_bg(new Surface("assets/images/menus/pause_menu/img_menu_pause_bg.png"), 1);
    Sprite img_menu_pause_resume(new Surface("assets/images/menus/pause_menu/img_menu_pause_resume.png"), 1);
    Sprite img_menu_pause_quit(new Surface("assets/images/menus/pause_menu/img_menu_pause_quit.png"), 1);

        // - Hover
    Sprite img_menu_pause_resume_alt(new Surface("assets/images/menus/pause_menu/img_menu_pause_resume_alt.png"), 1);
    Sprite img_menu_pause_quit_alt(new Surface("assets/images/menus/pause_menu/img_menu_pause_quit_alt.png"), 1);

    // + END MENU
    Sprite img_menu_end_bg(new Surface("assets/images/menus/end_menu/img_menu_end_bg.png"), 1);
    Sprite img_menu_end_menu(new Surface("assets/images/menus/end_menu/img_menu_end_menu.png"), 1);
    Sprite img_menu_end_replay(new Surface("assets/images/menus/end_menu/img_menu_end_menu_replay.png"), 1);

        // - Hover
    Sprite img_menu_end_menu_alt(new Surface("assets/images/menus/end_menu/img_menu_end_menu_alt.png"), 1);
    Sprite img_menu_end_replay_alt(new Surface("assets/images/menus/end_menu/img_menu_end_menu_replay_alt.png"), 1);

    // + OVER MENU
    Sprite img_menu_over_bg(new Surface("assets/images/menus/over_menu/img_menu_over_bg.png"), 1);

    // + AUDIO MANAGER
    Sprite img_audio_on(new Surface("assets/images/UI/img_audio_on.png"), 1);
    Sprite img_audio_off(new Surface("assets/images/UI/img_audio_off.png"), 1);

        // - Hover
    Sprite img_audio_on_hover(new Surface("assets/images/UI/img_audio_on_hover.png"), 1);
    Sprite img_audio_off_hover(new Surface("assets/images/UI/img_audio_off_hover.png"), 1);

    // + GLOBAL
    //Sprite img_selected(new Surface("assets/images/UI/img_selected.png"), 1);
    Sprite img_quit(new Surface("assets/images/UI/img_quit.png"), 1);

        // - Hover
    Sprite img_quit_hover(new Surface("assets/images/UI/img_quit_hover.png"), 1);

    bool Menu::isHoveringSurface(int x, int y, int width, int height)
    {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }

    void Menu::handleButton(
        Surface* screen,
        int x, int y, int width, int height,
        Sprite* normalSprite,
        Sprite* hoverSprite,
        bool& wasHovering,
        std::function<void()> onClick)
    {
        bool isHovering = isHoveringSurface(x, y, width, height);

        if (isHovering)
        {
            if (!wasHovering)
                gamesound.playSound(gamesound.snd_hover);

            hoverSprite->Draw(screen, x, y);

            if (isMousePressed && !wasMousePressedLastFrame)
            {
                gamesound.playSound(gamesound.snd_select);
                if (onClick) onClick();
            }
            isMousePressed = wasMousePressedLastFrame;
        }
        else
        {
            normalSprite->Draw(screen, x, y);
        }

        wasHovering = isHovering;
    }

    //void Menu::drawMainBGPan(Surface* screen, float deltaTime)
    //{
    //    float panning_speed = 150.0f; 
    //    float bg_width = img_menu_main_bg.GetWidth();

    //    main_bg_x += panning_speed * deltaTime;

    //    if (main_bg_x >= bg_width) main_bg_x -= bg_width;

    //    img_menu_main_bg.Draw(screen, -main_bg_x, 0);           
    //    img_menu_main_bg.Draw(screen, -main_bg_x + bg_width, 0);
    //}

    //void Menu::openMainMenu(Surface* screen, float deltaTime)
    //{
    //    if (!mainMenuOpen) return;

    //    drawMainBGPan(screen, deltaTime);
    //    img_menu_main_pro_tip.Draw(screen, 7, SCREEN_HEIGHT - img_menu_main_pro_tip.GetHeight() - 7);

    //    audioOpen = true;
    //    quitOpen = true;
    //    audioManagerOpen(screen);
    //    quitManagerOpen(screen);

    //    // Level buttons
    //    Sprite* lvl_hover_list[5] = { &img_menu_main_lvl1_alt, &img_menu_main_lvl2_alt, &img_menu_main_lvl3_alt, &img_menu_main_lvl4_alt, &img_menu_main_lvl5_alt };
    //    Sprite* lvl_list[5] = { &img_menu_main_lvl1, &img_menu_main_lvl2, &img_menu_main_lvl3, &img_menu_main_lvl4, &img_menu_main_lvl5 };
    //    int lvl_list_X[5] = { MAIN_LVL1_X, MAIN_LVL2_X, MAIN_LVL3_X, MAIN_LVL4_X, MAIN_LVL5_X };

    //    // Difficulty buttons
    //    Sprite* difficulty_hover_list[3] = { &img_menu_main_difficulty_easy_hover, &img_menu_main_difficulty_medium_hover, &img_menu_main_difficulty_hard_hover };
    //    Sprite* difficulty_list[3] = { &img_menu_main_difficulty_easy, &img_menu_main_difficulty_medium, &img_menu_main_difficulty_hard };
    //    int difficulty_X[3] = { MAIN_EASY_X, MAIN_MEDIUM_X, MAIN_HARD_X };

    //    // Variables to track button hover state
    //    static bool wasHoveringLevel[5] = { false };
    //    static bool wasHoveringDifficulty[3] = { false };
    //    static bool wasHoveringStart = false;
    //    static bool wasHoveringInfo = false;

    //    // Level buttons loop
    //    for (int i = 0; i < 5; i++)
    //    {
    //        handleButton(
    //            screen,
    //            lvl_list_X[i], MAIN_LVLS_Y,
    //            MAIN_LVL_WIDTH, MAIN_LVL_HEIGHT,
    //            lvl_list[i], lvl_hover_list[i],
    //            wasHoveringLevel[i],
    //            [&]() {
    //                manageLevelSelect(i);
    //                score = 0.0f;
    //                timer_current = 0.0f;
    //            });
    //    }

    //    // Difficulty buttons loop
    //    for (int i = 0; i < 3; i++)
    //    {
    //        handleButton(
    //            screen,
    //            difficulty_X[i], MAIN_DIFFICULTIES_Y,
    //            MAIN_DIFFICULTY_WIDTH, MAIN_DIFFICULTY_HEIGHT,
    //            difficulty_list[i], difficulty_hover_list[i],
    //            wasHoveringDifficulty[i],
    //            [&]() {
    //                manageDifficultySelect(i);
    //            });

    //        // Draw the selected difficulty marker
    //        if (difficulty == i + 1)
    //        {
    //            static float totalTime = 0.0f;
    //            float floating_time = 2.0f;
    //            float amplitude = 5.0f;
    //            vec2 draw_pos = vec2(
    //                difficulty_X[i] + MAIN_DIFFICULTY_WIDTH / 2 - img_selected.GetWidth() / 2,
    //                MAIN_DIFFICULTIES_Y + MAIN_DIFFICULTY_HEIGHT + 10.0f
    //            );
    //            totalTime += deltaTime;
    //            draw_pos.y += sin((totalTime / floating_time) * 2.0f * PI) * amplitude - 4.0f;
    //            img_selected.Draw(screen, draw_pos);
    //        }
    //    }

    //    // Start button hover logic
    //    handleButton(
    //        screen,
    //        MAIN_START_X, MAIN_START_Y,
    //        MAIN_START_WIDTH, MAIN_START_HEIGHT,
    //        &img_menu_main_start, &img_menu_main_start_alt,
    //        wasHoveringStart,
    //        [&]() {
    //            manageLevelSelect(0);
    //            score = 0;
    //            timer_current = 0.0f;
    //        });

    //    // Info button hover logic
    //    static bool wasMousePressedLastFrame = false;
    //    handleButton(
    //        screen,
    //        MAIN_INFO_X, MAIN_INFO_Y,
    //        MAIN_INFO_WIDTH, MAIN_INFO_HEIGHT,
    //        &img_menu_main_info_info, &img_menu_main_info_info_alt,
    //        wasHoveringInfo,
    //        [&]() {
    //            if (isMousePressed && !wasMousePressedLastFrame)
    //            {
    //                gamesound.playSound(gamesound.snd_select);
    //                infoMenuOpen = true;
    //            }
    //        });

    //    // Open the info menu
    //    openInfoMenu(screen, deltaTime);

    //    // Store mouse pressed state for next frame
    //    wasMousePressedLastFrame = isMousePressed;
    //}

    void Menu::manageLevelSelect(int index)
    {
        if (isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            gamesound.playMusic(gamesound.mus_level);
            health.initHealth(this);
            audioOpen = false;
            quitOpen = false;
            level.level_finished = false;
            start_game = true;
            resume_game = true;
            manualPaused = false;
            mainMenuOpen = false;
            infoMenuOpen = false;
            endMenuOpen = false;
            level.loadLevel(index + 1);
        }
    }

    void Menu::manageDifficultySelect(int index)
    {
        health.hp_initialized = false;
        if (isMousePressed && difficulty != index + 1)
        {
            gamesound.playSound(gamesound.snd_select);  
            difficulty = index + 1;
        }
    }

    void Menu::openNextMenu(Surface* screen)
    {
        scoreMenuOpen = true;
        nextMenuOpen = level.level_finished;
        if (!nextMenuOpen) return;

        img_menu_next_bg.Draw(screen, SCREEN_WIDTH / 2 - NEXT_BG_WIDTH / 2, SCREEN_HEIGHT / 2 - NEXT_BG_HEIGHT / 2);

        static bool wasHoveringNext = false;
        static bool wasHoveringMenu = false;

        // Handle "Next Level" button
        handleButton(
            screen,
            NEXT_LVL_X, NEXT_LVL_Y,
            NEXT_NEXT_WIDTH, NEXT_NEXT_HEIGHT,
            &img_menu_next_next,
            &img_menu_next_next_alt,
            wasHoveringNext,
            [&]() {
                if (!alreadyClickedNextLevel)
                {
                    gamesound.playSound(gamesound.snd_select);
                    resume_game = true;
                    level.loadLevel(tilemap.incrementMapIndex());
                    level.level_finished = false;
                    alreadyClickedNextLevel = true;
                    nextMenuOpen = false;
                    scoreMenuOpen = false;
                }
            });

        // Handle "Menu" button
        handleButton(
            screen,
            NEXT_MENU_X, NEXT_MENU_Y,
            NEXT_NEXT_WIDTH, NEXT_NEXT_HEIGHT,
            &img_menu_next_menu,
            &img_menu_next_menu_alt,
            wasHoveringMenu,
            [&]() {
                gamesound.playSound(gamesound.snd_select);
                gamesound.playMusic(gamesound.mus_menu);
                start_game = false;
                nextMenuOpen = false;
                mainMenuOpen = true;
                scoreMenuOpen = false;
            });
    }

    void Menu::openPauseMenu(Surface* screen)
    {
        if (!pauseMenuOpen) return;

        audioOpen = true;
        quitOpen = true;
        audioManagerOpen(screen);
        quitManagerOpen(screen);

        img_menu_pause_bg.Draw(screen, SCREEN_WIDTH / 2 - PAUSE_BG_WIDTH / 2, SCREEN_HEIGHT / 2 - PAUSE_BG_HEIGHT / 2);

        static bool wasHoveringResume = false;
        static bool wasHoveringQuit = false;

        // Pause Button
        handleButton(
            screen,
            PAUSE_RESUME_X, PAUSE_RESUME_Y,
            PAUSE_RESUME_WIDTH, PAUSE_RESUME_HEIGHT,
            &img_menu_pause_resume,
            &img_menu_pause_resume_alt,
            wasHoveringResume,
            [&]() {
                manualPaused = false;
                resume_game = true;
                pauseMenuOpen = false;
                audioOpen = false;
                quitOpen = false;
            });

        // Quit Button
        handleButton(
            screen,
            PAUSE_QUIT_X, PAUSE_QUIT_Y,
            PAUSE_QUIT_WIDTH, PAUSE_QUIT_HEIGHT,
            &img_menu_pause_quit,
            &img_menu_pause_quit_alt,
            wasHoveringQuit,
            [&]() {
                gamesound.playMusic(gamesound.mus_menu);
                start_game = false;
                resume_game = false;
                mainMenuOpen = true;
                infoMenuOpen = false;
                pauseMenuOpen = false;
                audioOpen = false;
                quitOpen = false;
            });
    }

    void Menu::openEndMenu(Surface* screen)
    {
        endMenuOpen = level.game_finished;
        scoreMenuOpen = true;

        if (endMenuOpen)
            img_menu_end_bg.Draw(screen, SCREEN_WIDTH / 2 - PAUSE_BG_WIDTH / 2, SCREEN_HEIGHT / 2 - PAUSE_BG_HEIGHT / 2);
        else if (overMenuOpen)
            img_menu_over_bg.Draw(screen, SCREEN_WIDTH / 2 - PAUSE_BG_WIDTH / 2, SCREEN_HEIGHT / 2 - PAUSE_BG_HEIGHT / 2);
        else
            return;

        static bool wasHoveringMenu = false;
        static bool wasHoveringReplay = false;

        // Menu button
        handleButton(
            screen,
            END_MENU_X, END_MENU_Y,
            END_MENU_WIDTH, END_MENU_HEIGHT,
            &img_menu_end_menu,
            &img_menu_end_menu_alt,
            wasHoveringMenu,
            [&]() {
                gamesound.playMusic(gamesound.mus_menu);
                start_game = false;
                resume_game = false;
                pauseMenuOpen = false;
                endMenuOpen = false;
                overMenuOpen = false;
                mainMenuOpen = true;
                infoMenuOpen = false;
                level.game_finished = false;
                scoreMenuOpen = false;
                score = 0.0f;
                timer_current = 0.0f;
            });

        // Replay button
        handleButton(
            screen,
            END_REPLAY_X, END_REPLAY_Y, 
            END_REPLAY_WIDTH, END_REPLAY_HEIGHT,
            &img_menu_end_replay,
            &img_menu_end_replay_alt,
            wasHoveringReplay,
            [&]() {
                gamesound.playMusic(gamesound.mus_level);
                start_game = true;
                resume_game = true;
                pauseMenuOpen = false;
                endMenuOpen = false;
                overMenuOpen = false;
                mainMenuOpen = false;
                level.game_finished = false;
                health.initHealth(this);
                level.loadLevel(1);
                scoreMenuOpen = false;
                score = 0.0f;
                timer_current = 0.0f;
            });
    }

    void Menu::manageMenus(Surface* screen, float deltaTime)
    {
        // Toggle <P> to open/close the pause menu
        static bool pPressedLastFrame = false;
        bool isPDown = GetAsyncKeyState('P') & 0x8000; // Is <P> pressed and released
        bool press = isPDown && !pPressedLastFrame;
        if (press)
        {
            pauseMenuOpen = !pauseMenuOpen;
            manualPaused = !manualPaused;
        }

        pPressedLastFrame = isPDown;

        if (level.level_finished)
        {
            openNextMenu(screen);
            resume_game = false;
        }
        else
        {
            if (!resume_game) openPauseMenu(screen);
            resume_game = !manualPaused;
        }

        static bool end_sound_played = false;
        if (level.game_finished)
        {
            if (!end_sound_played)
            {
                gamesound.stopMusic();
                if(score <= 0) gamesound.playSound(gamesound.snd_level_finished); // If the player has 0 score, play the SFX instantly instead of waiting for the countdown
                end_sound_played = true;
            }
            openEndMenu(screen);
            resume_game = false;
        }
        else
        {
            end_sound_played = false; 
        }

    }

    void Menu::addScore(int score_increment)
    {
        score += score_increment * difficulty;
    }

    void Menu::scoreInGame(Surface* screen, float deltaTime)
    {
        if (pauseMenuOpen || nextMenuOpen || endMenuOpen || overMenuOpen) return;

        char buffer[50];
        bool score_updated = score != previousScore;
        float color_update_time = 0.3f;
        Pixel color = 0xFFFFFF;         // White by default
        vec2 size = vec2(1.0f, 1.0f);   // Scale to 100% by default

        sprintf(buffer, "Score: %04d", score);

        std::string txt = buffer;
        int text_width = stb_easy_font_width((char*)txt.c_str());
        float offset_to_corner = 10.0f;
        static float lastScoreUpdateTime = -1.0f;
        if (score_updated) 
            lastScoreUpdateTime = 0.0f; 
        if (lastScoreUpdateTime >= 0.0f && lastScoreUpdateTime < color_update_time && score!=0) 
        {
            size = vec2(1.05f, 1.05f);  // Scale to 105%
            color = 0xFFFF00;           // Yellow
            text_width = static_cast<int>(static_cast<float>(text_width) * size.x);       // Adjust width (unused)
        }
        if (lastScoreUpdateTime >= color_update_time) 
        {
            size = vec2(1.0f, 1.0f);
            color = 0xFFFFFF;  
        }
        if (lastScoreUpdateTime >= 0.0f) 
            lastScoreUpdateTime += deltaTime;

        previousScore = score;

        vec2 draw_pos = vec2(
            offset_to_corner,
            offset_to_corner
        );

        // Draw the text on the screen
        text.printOnScreen((char*)txt.c_str(), draw_pos + 2.0f, screen, size, 0x934712);  // Drop shadow (dark orange)
        text.printOnScreen((char*)txt.c_str(), draw_pos, screen, size, color);            // Actual text (color)
    }

    void Menu::dashCountInGame(Surface* screen, float deltaTime)
    {
        if (pauseMenuOpen || nextMenuOpen || endMenuOpen || overMenuOpen) return;

        char buffer[50];
        Pixel color = 0xFFFFFF;         
        vec2 size = vec2(1.0f, 1.0f);   

        sprintf(buffer, "Dashes: %d", player.dash_count);

        std::string txt = buffer;
        int text_width = stb_easy_font_width((char*)txt.c_str());
        float offset_to_corner = 10.0f;
   
        vec2 draw_pos = vec2(
            offset_to_corner,
            offset_to_corner + 40.0f
        );

        // Draw the text on the screen
        text.printOnScreen((char*)txt.c_str(), draw_pos + 2.0f, screen, size, 0x934712);  // Drop shadow (dark orange)
        text.printOnScreen((char*)txt.c_str(), draw_pos, screen, size, color);            // Actual text (color)
    }

    void Menu::openScoreMenu(Surface* screen, float deltaTime)
    {
        if (score <= 0) score = 0; // The score can't go below 0

        if (!scoreMenuOpen)
        {
            score_timer = 0.0f;
            score_value_current = 0;
            score_is_counting = true;
            finish_sfx_played = false;
            return;
        }

        static const float counting_speed = 0.5f; // In secs

        Pixel color = 0xFFFFFF;
        vec2 size = vec2(4.0f, 4.0f);

        score_timer += deltaTime;
        for (int i = 0; i < score; i++)
        {
            score_value_current = score * score_timer / counting_speed;

            color = 0xFFFF00;
            size = vec2(5.2f, 5.2f);

            if (score_value_current >= score)
            {
                score_value_current = score;
                score_is_counting = false;
                if (endMenuOpen) color = 0x00FF00;
                else color = 0xFFFFFF;
                size = vec2(5.0f, 5.0f);

                if(!finish_sfx_played && endMenuOpen) // Play a victory SFX once the count finishes
                {
                    gamesound.playSound(gamesound.snd_level_finished);
                    finish_sfx_played = true;
                }
            }
        }
        char buffer[50];
        sprintf(buffer, "Score: %04d", score_value_current);

        std::string txt = buffer;
        int text_width = stb_easy_font_width((char*)txt.c_str());
        int text_height = stb_easy_font_height((char*)txt.c_str());

        vec2 draw_pos = vec2(
            (SCREEN_WIDTH - text_width * size.x) / 2.0f,
            (SCREEN_HEIGHT - text_height * size.y) / 2.0f
        );

        text.printOnScreen((char*)txt.c_str(), draw_pos, screen, size, color);
    }

    void Menu::quitManagerOpen(Surface* screen)
    {
        if (!quitOpen) return;

        static bool wasHoveringQuit = false;

        handleButton(
            screen,
            QUIT_X, QUIT_Y,
            QUIT_WIDTH, QUIT_HEIGHT,
            &img_quit,
            &img_quit_hover,
            wasHoveringQuit,
            []() {
                exit(0);
            }
        );
    }

    void Menu::audioManagerOpen(Surface* screen)
    {
        if (!audioOpen) return;

        static bool wasHoveringAudio = false;
        bool isHoveringAudio = isHoveringSurface(AUDIO_X, AUDIO_Y, AUDIO_WIDTH, AUDIO_HEIGHT);

        handleButton(
            screen,
            AUDIO_X, AUDIO_Y,
            AUDIO_WIDTH, AUDIO_HEIGHT,
            audioOn ? &img_audio_on : &img_audio_off, 
            audioOn ? &img_audio_on_hover : &img_audio_off_hover,
            wasHoveringAudio,
            [&]() {
                gamesound.playSound(gamesound.snd_select);
                audioOn = !audioOn;

                if (audioOn)
                {
                    gamesound.globalVolume = 0.1f;
                    gamesound.playSound(gamesound.snd_select);
                    if (start_game)
                    {
                        gamesound.playMusic(gamesound.mus_level);
                    }
                    else
                    {
                        gamesound.playMusic(gamesound.mus_menu);
                    }
                }
                else
                {
                    gamesound.stopMusic();
                    gamesound.globalVolume = 0.0f;
                }
            });

        wasHoveringAudio = isHoveringAudio;
    }

    void Menu::timerInGame(Surface* screen, float deltaTime)
    {
        if ( pauseMenuOpen || nextMenuOpen || endMenuOpen || overMenuOpen) return;

        timer_current += deltaTime;

        int total_seconds = static_cast<int>(timer_current);
        int minutes = total_seconds / 60;
        int seconds = total_seconds % 60;

        char buffer[50];
        sprintf(buffer, "Time: %02d:%02d", minutes, seconds);

        std::string txt = buffer;
        int text_width = stb_easy_font_width((char*)txt.c_str());
        int text_height = stb_easy_font_height((char*)txt.c_str());

        vec2 size = vec2(1.0f,1.0f);
        vec2 draw_pos = vec2(
            10.0f,
            30.0f 
        );

        text.printOnScreen((char*)txt.c_str(), draw_pos + 2.0f, screen, size, 0x934712);
        text.printOnScreen((char*)txt.c_str(), draw_pos, screen, size, 0xFFFFFF);
    }

    void Menu::setMousePosition(int x, int y)
    {
        mouseX = x;
        mouseY = y;
    }
}
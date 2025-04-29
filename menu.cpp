#define WIN32_MEAN_AND_LEAN
#include "windows.h"
#include "menu.h"

namespace Tmpl8
{
    Menu::Menu(Level& levelRef, Player& playerRef, TileMap& tilemapRef, GameSound& gamesoundRef) :
        level(levelRef),
        player(playerRef),
        tilemap(tilemapRef),
        gamesound(gamesoundRef)
    {}

    // + MAIN MENU
    Sprite img_menu_main_bg(new Surface("assets/images/menus/main_menu/img_menu_main_bg.png"), 1);
    Sprite img_menu_main_start(new Surface("assets/images/menus/main_menu/img_menu_main_start.png"), 1);
    Sprite img_menu_main_lvl1(new Surface("assets/images/menus/main_menu/img_menu_main_lvl1.png"), 1);
    Sprite img_menu_main_lvl2(new Surface("assets/images/menus/main_menu/img_menu_main_lvl2.png"), 1);
    Sprite img_menu_main_lvl3(new Surface("assets/images/menus/main_menu/img_menu_main_lvl3.png"), 1);
    Sprite img_menu_main_lvl4(new Surface("assets/images/menus/main_menu/img_menu_main_lvl4.png"), 1);
    Sprite img_menu_main_lvl5(new Surface("assets/images/menus/main_menu/img_menu_main_lvl5.png"), 1);
    Sprite img_menu_main_difficulty_easy(new Surface("assets/images/menus/main_menu/img_menu_main_difficulty_easy.png"), 1);
    Sprite img_menu_main_difficulty_medium(new Surface("assets/images/menus/main_menu/img_menu_main_difficulty_medium.png"), 1);
    Sprite img_menu_main_difficulty_hard(new Surface("assets/images/menus/main_menu/img_menu_main_difficulty_hard.png"), 1);

        // - Hover
    Sprite img_menu_main_start_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_start_alt.png"), 1);
    Sprite img_menu_main_lvl1_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl1_alt.png"), 1);
    Sprite img_menu_main_lvl2_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl2_alt.png"), 1);
    Sprite img_menu_main_lvl3_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl3_alt.png"), 1);
    Sprite img_menu_main_lvl4_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl4_alt.png"), 1);
    Sprite img_menu_main_lvl5_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl5_alt.png"), 1);
    Sprite img_menu_main_difficulty_easy_hover(new Surface("assets/images/menus/main_menu/hover/img_menu_main_difficulty_easy_hover.png"), 1);
    Sprite img_menu_main_difficulty_medium_hover(new Surface("assets/images/menus/main_menu/hover/img_menu_main_difficulty_medium_hover.png"), 1);
    Sprite img_menu_main_difficulty_hard_hover(new Surface("assets/images/menus/main_menu/hover/img_menu_main_difficulty_hard_hover.png"), 1);

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

    // + AUDIO MANAGER
    Sprite img_audio_on(new Surface("assets/images/UI/img_audio_on.png"), 1);
    Sprite img_audio_off(new Surface("assets/images/UI/img_audio_off.png"), 1);

        // - Hover
    Sprite img_audio_on_hover(new Surface("assets/images/UI/img_audio_on_hover.png"), 1);
    Sprite img_audio_off_hover(new Surface("assets/images/UI/img_audio_off_hover.png"), 1);

    // + GLOBAL
    Sprite img_selected(new Surface("assets/images/UI/img_selected.png"), 1);
    Sprite img_quit(new Surface("assets/images/UI/img_quit.png"), 1);

        // - Hover
    Sprite img_quit_hover(new Surface("assets/images/UI/img_quit_hover.png"), 1);

    bool Menu::isHoveringSurface(const vec2& pos, const vec2& size)
    {
        return mouseX >= pos.x && mouseX <= pos.x + size.x && mouseY >= pos.y && mouseY <= pos.y + size.y;
    }

    void Menu::openMainMenu(Surface* screen)
    {
        if (!mainMenuOpen) return;

        img_menu_main_bg.Draw(screen, 0, 0);

        audioOpen = true;
        quitOpen = true;
        audioManagerOpen(screen);
        quitManagerOpen(screen);

        Sprite* lvl_hover_list[5] = { &img_menu_main_lvl1_alt, &img_menu_main_lvl2_alt, &img_menu_main_lvl3_alt, &img_menu_main_lvl4_alt, &img_menu_main_lvl5_alt };
        Sprite* lvl_list[5] = { &img_menu_main_lvl1, &img_menu_main_lvl2, &img_menu_main_lvl3, &img_menu_main_lvl4, &img_menu_main_lvl5 };
        vec2 lvl_list_pos[5] = { MAIN_LVL1_POS, MAIN_LVL2_POS, MAIN_LVL3_POS, MAIN_LVL4_POS, MAIN_LVL5_POS };

        Sprite* difficulty_hover_list[3] = { &img_menu_main_difficulty_easy_hover, &img_menu_main_difficulty_medium_hover, &img_menu_main_difficulty_hard_hover };
        Sprite* difficulty_list[3] = { &img_menu_main_difficulty_easy, &img_menu_main_difficulty_medium, &img_menu_main_difficulty_hard };
        vec2 difficulty_pos[3] = { MAIN_EASY_POS, MAIN_MEDIUM_POS, MAIN_HARD_POS };

        static bool wasHoveringLevel[5] = { false };
        static bool wasHoveringDifficulty[5] = { false };
        static bool wasHoveringStart = false;

        for (int i = 0; i < 5; i++)
        { 
            // Hover levels buttons logic
            bool isHoveringLevel = isHoveringSurface(lvl_list_pos[i], MAIN_LVL_SIZE);

            if (isHoveringLevel)
            {
                if (!wasHoveringLevel[i]) gamesound.playSound(gamesound.snd_hover);
                lvl_hover_list[i]->Draw(screen, lvl_list_pos[i]);
                manageLevelSelect(i);
            }
            else
            {
                lvl_list[i]->Draw(screen, lvl_list_pos[i]);
            }

            wasHoveringLevel[i] = isHoveringLevel;
        }

        for (int i = 0; i < 3; i++)
        {
            // Hover difficulties buttons logic
            bool isHoveringDifficulty = isHoveringSurface(difficulty_pos[i], MAIN_DIFFICULTY_SIZE);

            if (isHoveringDifficulty)
            {
                if (!wasHoveringDifficulty[i]) gamesound.playSound(gamesound.snd_hover);
                difficulty_hover_list[i]->Draw(screen, difficulty_pos[i]);
                manageDifficultySelect(i);
            }
            else
            {
                difficulty_list[i]->Draw(screen, difficulty_pos[i]);
            }

            wasHoveringDifficulty[i] = isHoveringDifficulty;

            // Draw the selected difficulty marker
            if (difficulty == i + 1)
            {
                img_selected.Draw(screen, difficulty_pos[i].x + MAIN_DIFFICULTY_SIZE.x / 2 - img_selected.GetWidth() / 2, difficulty_pos[i].y + MAIN_DIFFICULTY_SIZE.y );
            }
        }

    
        // Hover start button logic
        bool isHoveringStart = isHoveringSurface(MAIN_START_POS, MAIN_START_SIZE);

        if (isHoveringStart)
        {
            if (!wasHoveringStart) gamesound.playSound(gamesound.snd_hover);
            img_menu_main_start_alt.Draw(screen, MAIN_START_POS);
            manageLevelSelect(0);
        }
        else
        {
            img_menu_main_start.Draw(screen, MAIN_START_POS);
        }

        wasHoveringStart = isHoveringStart;
    }


    void Menu::manageLevelSelect(int index)
    {
        if (isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            gamesound.playMusic(gamesound.mus_level);
            audioOpen = false;
            quitOpen = false;
            level.level_finished = false;
            start_game = true;
            resume_game = true;
            manualPaused = false;
            mainMenuOpen = false;
            level.loadLevel(index + 1);
        }
    }

    void Menu::manageDifficultySelect(int index)
    {
        if (isMousePressed && difficulty != index + 1)
        {
            gamesound.playSound(gamesound.snd_select);  
            difficulty = index + 1;
        }
    }


    void Menu::openNextMenu(Surface* screen)
    {
        nextMenuOpen = level.level_finished;
        if (!nextMenuOpen) return;

        img_menu_next_bg.Draw(screen, SCREEN_WIDTH / 2 - NEXT_BG_SIZE.x / 2, SCREEN_HEIGHT / 2 - NEXT_BG_SIZE.y / 2);

        static bool wasHoveringNext = false;
        static bool wasHoveringMenu = false;

        bool isHoveringMenu = isHoveringSurface(NEXT_MENU_POS, NEXT_NEXT_SIZE);
        bool isHoveringNext = isHoveringSurface(NEXT_LVL_POS, NEXT_NEXT_SIZE);

        if (isHoveringMenu)
        {
            if (!wasHoveringMenu) gamesound.playSound(gamesound.snd_hover);
            img_menu_next_menu_alt.Draw(screen, NEXT_MENU_POS);
        }
        else
        {
            img_menu_next_menu.Draw(screen, NEXT_MENU_POS);
        }

        if (isHoveringNext)
        {
            if (!wasHoveringNext) gamesound.playSound(gamesound.snd_hover);
            img_menu_next_next_alt.Draw(screen, NEXT_LVL_POS);
        }
        else
        {
            img_menu_next_next.Draw(screen, NEXT_LVL_POS);
        }

        wasHoveringMenu = isHoveringMenu;
        wasHoveringNext = isHoveringNext;

        bool pressingNext = (isHoveringNext && isMousePressed) || (GetAsyncKeyState(VK_RETURN) & 0x8000);
        bool pressingMenu = (isHoveringMenu && isMousePressed);

        if (pressingNext && !alreadyClickedNextLevel)
        {
            gamesound.playSound(gamesound.snd_select);
            resume_game = true;
            level.loadLevel(tilemap.incrementMapIndex());
            level.level_finished = false;
            alreadyClickedNextLevel = true;
            nextMenuOpen = false;
        }
        else if (!pressingNext)
        {
            alreadyClickedNextLevel = false;
        }

        if (pressingMenu)
        {
            gamesound.playSound(gamesound.snd_select);
            gamesound.playMusic(gamesound.mus_menu);
            start_game = false;
            nextMenuOpen = false;
            mainMenuOpen = true;
        }
    }


    void Menu::openPauseMenu(Surface* screen)
    {
        if (!pauseMenuOpen) return;

        audioOpen = true;
        quitOpen = true;
        audioManagerOpen(screen);
        quitManagerOpen(screen);

        img_menu_pause_bg.Draw(screen, SCREEN_WIDTH / 2 - PAUSE_BG_SIZE.x / 2, SCREEN_HEIGHT / 2 - PAUSE_BG_SIZE.y / 2);

        static bool wasHoveringResume = false;
        static bool wasHoveringQuit = false;

        bool isHoveringResume = isHoveringSurface(PAUSE_RESUME_POS, PAUSE_RESUME_SIZE);
        bool isHoveringQuit = isHoveringSurface(PAUSE_QUIT_POS, PAUSE_QUIT_SIZE);

        if (isHoveringResume)
        {
            if (!wasHoveringResume) gamesound.playSound(gamesound.snd_hover);
            img_menu_pause_resume_alt.Draw(screen, PAUSE_RESUME_POS);
        }
        else
        {
            img_menu_pause_resume.Draw(screen, PAUSE_RESUME_POS);
        }

        if (isHoveringQuit)
        {
            if (!wasHoveringQuit) gamesound.playSound(gamesound.snd_hover);
            img_menu_pause_quit_alt.Draw(screen, PAUSE_QUIT_POS);
        }
        else
        {
            img_menu_pause_quit.Draw(screen, PAUSE_QUIT_POS);
        }

        wasHoveringResume = isHoveringResume;
        wasHoveringQuit = isHoveringQuit;

        if (isHoveringQuit && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            gamesound.playMusic(gamesound.mus_menu);
            start_game = false;
            resume_game = false;
            mainMenuOpen = true;
            pauseMenuOpen = false;
            audioOpen = false;
            quitOpen = false;
        }
        else if (isHoveringResume && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            manualPaused = false;
            resume_game = true;
            pauseMenuOpen = false;
            audioOpen = false;
            quitOpen = false;
        }
    }


    void Menu::openEndMenu(Surface* screen)
    {
        endMenuOpen = level.game_finished;
        if (!endMenuOpen) return;

        img_menu_end_bg.Draw(screen, SCREEN_WIDTH / 2 - PAUSE_BG_SIZE.x / 2, SCREEN_HEIGHT / 2 - PAUSE_BG_SIZE.y / 2);

        static bool wasHoveringMenu = false;
        static bool wasHoveringReplay = false;

        bool isHoveringMenu = isHoveringSurface(END_MENU_POS, END_MENU_SIZE);
        bool isHoveringReplay = isHoveringSurface(END_REPLAY_POS, END_REPLAY_SIZE);

        if (isHoveringMenu)
        {
            if (!wasHoveringMenu) gamesound.playSound(gamesound.snd_hover);
            img_menu_end_menu_alt.Draw(screen, END_MENU_POS);
        }
        else
        {
            img_menu_end_menu.Draw(screen, END_MENU_POS);
        }

        if(isHoveringReplay)
        {
            if (!wasHoveringReplay) gamesound.playSound(gamesound.snd_hover);
            img_menu_end_replay_alt.Draw(screen, END_REPLAY_POS);
        }
        else
        {
            img_menu_end_replay.Draw(screen, END_REPLAY_POS);
        }

        wasHoveringMenu = isHoveringMenu;
        wasHoveringReplay = isHoveringReplay;

        if (isHoveringMenu && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            gamesound.playMusic(gamesound.mus_menu);
            start_game = false;
            resume_game = false;
            pauseMenuOpen = false;
            endMenuOpen = false;
            mainMenuOpen = true;
            level.game_finished = false;
        }

        if (isHoveringReplay && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            gamesound.playMusic(gamesound.mus_level);
            start_game = true;
            resume_game = true;
            pauseMenuOpen = false;
            endMenuOpen = false;
            mainMenuOpen = false;
            level.game_finished = false;
            level.loadLevel(1);
        }
    }


    void Menu::manageMenus(Surface* screen)
    {
        // Toggle <P> to open/close the pause menu
        static bool pPressedLastFrame = false;
        bool isPDown = GetAsyncKeyState('P') & 0x8000; // Is <P> pressed and released
        bool press = isPDown && !pPressedLastFrame;
        if (press)
        {
            pauseMenuOpen = true;
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

        static bool end_sound_played = false; // To play the end sound only once
        if (level.game_finished)
        {
            if (!end_sound_played)
            {
                gamesound.stopMusic();
                gamesound.playSound(gamesound.snd_level_finished);
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

    void Menu::quitManagerOpen(Surface* screen)
    {
        if (!quitOpen) return;

        static bool wasHoveringQuit = false;
        bool isHoveringQuit = isHoveringSurface(QUIT_POS, QUIT_SIZE);

        if (isHoveringQuit)
        {
            if (!wasHoveringQuit)
                gamesound.playSound(gamesound.snd_hover);
            img_quit_hover.Draw(screen, QUIT_POS);
        }
        else
        {
            img_quit.Draw(screen, QUIT_POS);
        }

        wasHoveringQuit = isHoveringQuit;

        if (isHoveringQuit && isMousePressed)
        {
            exit(0);
        }
    }

    void Menu::audioManagerOpen(Surface* screen)
    {
        if (!audioOpen) return;

        static bool wasHoveringAudio = false;
        static bool audioClickedLastFrame = false;

        bool isHoveringAudio = isHoveringSurface(AUDIO_POS, AUDIO_SIZE);

        if (isHoveringAudio)
        {
            if (!wasHoveringAudio)
                gamesound.playSound(gamesound.snd_hover);

            if (audioOn)
                img_audio_on_hover.Draw(screen, AUDIO_POS);
            else
                img_audio_off_hover.Draw(screen, AUDIO_POS);
        }
        else
        {
            if (audioOn)
                img_audio_on.Draw(screen, AUDIO_POS);
            else
                img_audio_off.Draw(screen, AUDIO_POS);
        }

        wasHoveringAudio = isHoveringAudio;

        if (isHoveringAudio && isMousePressed && !audioClickedLastFrame)
        {
            gamesound.playSound(gamesound.snd_select);
            audioOn = !audioOn;
            if (audioOn)
            {
                gamesound.globalVolume = 0.1f;
                gamesound.playSound(gamesound.snd_select);
                if (start_game)
                    gamesound.playMusic(gamesound.mus_level);
                else
                    gamesound.playMusic(gamesound.mus_menu);
            }
            else
            {
                gamesound.stopMusic();
                gamesound.globalVolume = 0.0f;
            }

        }

        audioClickedLastFrame = isMousePressed;
    }

    void Menu::setMousePosition(int x, int y)
    {
        mouseX = x;
        mouseY = y;
    }
}
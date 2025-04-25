#include "menu.h"
#include "game.h"  // To call MouseMove if needed
#include "windows.h"
#include "tilemap.h"
#include <stdio.h>
#include <iostream>
#include <thread>

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

        // - Hover
    Sprite img_menu_main_start_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_start_alt.png"), 1);
    Sprite img_menu_main_lvl1_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl1_alt.png"), 1);
    Sprite img_menu_main_lvl2_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl2_alt.png"), 1);
    Sprite img_menu_main_lvl3_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl3_alt.png"), 1);
    Sprite img_menu_main_lvl4_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl4_alt.png"), 1);
    Sprite img_menu_main_lvl5_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl5_alt.png"), 1);

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

        // - Hover
    Sprite img_menu_end_menu_alt(new Surface("assets/images/menus/end_menu/img_menu_end_menu_alt.png"), 1);

    bool Menu::isHoveringSurface(int x, int y, int width, int height)
    {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }

    void Menu::openMainMenu(Surface* screen)
    {
        if (!mainMenuOpen) return;

        img_menu_main_bg.Draw(screen, 0, 0);

        Sprite* lvl_hover_list[5] = { &img_menu_main_lvl1_alt, &img_menu_main_lvl2_alt, &img_menu_main_lvl3_alt, &img_menu_main_lvl4_alt, &img_menu_main_lvl5_alt };
        Sprite* lvl_list[5] = { &img_menu_main_lvl1, &img_menu_main_lvl2, &img_menu_main_lvl3, &img_menu_main_lvl4, &img_menu_main_lvl5 };
        int lvl_list_X[5] = { MAIN_LVL1_X, MAIN_LVL2_X, MAIN_LVL3_X, MAIN_LVL4_X, MAIN_LVL5_X };
        int lvl_list_Y[5] = { MAIN_LVL1_Y, MAIN_LVL2_Y, MAIN_LVL3_Y, MAIN_LVL4_Y, MAIN_LVL5_Y };

        static bool wasHoveringLevel[5] = { false };
        static bool wasHoveringStart = false;

        for (int i = 0; i < 5; i++)
        { 
            // Hover levels buttons logic
            bool isHoveringLevel = isHoveringSurface(lvl_list_X[i], lvl_list_Y[i], MAIN_LVL_WIDTH, MAIN_LVL_HEIGHT);

            if (isHoveringLevel)
            {
                if (!wasHoveringLevel[i])
                    gamesound.playSound(gamesound.snd_hover);

                lvl_hover_list[i]->Draw(screen, lvl_list_X[i], lvl_list_Y[i]);
                manageLevelSelect(i);
            }
            else
            {
                lvl_list[i]->Draw(screen, lvl_list_X[i], lvl_list_Y[i]);
            }

            wasHoveringLevel[i] = isHoveringLevel;
        }

        // Hover start button logic
        bool isHoveringStart = isHoveringSurface(MAIN_START_X, MAIN_START_Y, MAIN_START_WIDTH, MAIN_START_HEIGHT);

        if (isHoveringStart)
        {
            if (!wasHoveringStart)
                gamesound.playSound(gamesound.snd_hover);

            img_menu_main_start_alt.Draw(screen, MAIN_START_X, MAIN_START_Y);
            manageLevelSelect(1);
        }
        else
        {
            img_menu_main_start.Draw(screen, MAIN_START_X, MAIN_START_Y);
        }

        wasHoveringStart = isHoveringStart;
    }


    void Menu::manageLevelSelect(int index)
    {
        if (isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            gamesound.playMusic(gamesound.mus_level);
            level.level_finished = false;
            start_game = true;
            resume_game = true;
            manualPaused = false;
            mainMenuOpen = false;
            level.loadLevel(index + 1);
        }
    }

    void Menu::openNextMenu(Surface* screen)
    {
        nextMenuOpen = level.level_finished;
        if (!nextMenuOpen) return;

        img_menu_next_bg.Draw(screen, SCREEN_WIDTH / 2 - NEXT_BG_WIDTH / 2, SCREEN_HEIGHT / 2 - NEXT_BG_HEIGHT / 2);

        static bool wasHoveringNext = false;
        static bool wasHoveringMenu = false;

        bool isHoveringMenu = isHoveringSurface(NEXT_MENU_X, NEXT_MENU_Y, NEXT_NEXT_WIDTH, NEXT_NEXT_HEIGHT);
        bool isHoveringNext = isHoveringSurface(NEXT_LVL_X, NEXT_LVL_Y, NEXT_NEXT_WIDTH, NEXT_NEXT_HEIGHT);

        if (isHoveringMenu)
        {
            if (!wasHoveringMenu)
                gamesound.playSound(gamesound.snd_hover);
            img_menu_next_menu_alt.Draw(screen, NEXT_MENU_X, NEXT_MENU_Y);
        }
        else
        {
            img_menu_next_menu.Draw(screen, NEXT_MENU_X, NEXT_MENU_Y);
        }

        if (isHoveringNext)
        {
            if (!wasHoveringNext)
                gamesound.playSound(gamesound.snd_hover);
            img_menu_next_next_alt.Draw(screen, NEXT_LVL_X, NEXT_LVL_Y);
        }
        else
        {
            img_menu_next_next.Draw(screen, NEXT_LVL_X, NEXT_LVL_Y);
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

        img_menu_pause_bg.Draw(screen, SCREEN_WIDTH / 2 - PAUSE_BG_WIDTH / 2, SCREEN_HEIGHT / 2 - PAUSE_BG_HEIGHT / 2);

        static bool wasHoveringResume = false;
        static bool wasHoveringQuit = false;

        bool isHoveringResume = isHoveringSurface(PAUSE_RESUME_X, PAUSE_RESUME_Y, PAUSE_RESUME_WIDTH, PAUSE_RESUME_HEIGHT);
        bool isHoveringQuit = isHoveringSurface(PAUSE_QUIT_X, PAUSE_QUIT_Y, PAUSE_QUIT_WIDTH, PAUSE_QUIT_HEIGHT);

        if (isHoveringResume)
        {
            if (!wasHoveringResume)
                gamesound.playSound(gamesound.snd_hover);
            img_menu_pause_resume_alt.Draw(screen, PAUSE_RESUME_X, PAUSE_RESUME_Y);
        }
        else
        {
            img_menu_pause_resume.Draw(screen, PAUSE_RESUME_X, PAUSE_RESUME_Y);
        }

        if (isHoveringQuit)
        {
            if (!wasHoveringQuit)
                gamesound.playSound(gamesound.snd_hover);
            img_menu_pause_quit_alt.Draw(screen, PAUSE_QUIT_X, PAUSE_QUIT_Y);
        }
        else
        {
            img_menu_pause_quit.Draw(screen, PAUSE_QUIT_X, PAUSE_QUIT_Y);
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
        }
        else if (isHoveringResume && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            manualPaused = false;
            resume_game = true;
            pauseMenuOpen = false;
        }
    }


    void Menu::openEndMenu(Surface* screen)
    {
        endMenuOpen = level.game_finished;
        if (!endMenuOpen) return;

        img_menu_end_bg.Draw(screen, SCREEN_WIDTH / 2 - PAUSE_BG_WIDTH / 2, SCREEN_HEIGHT / 2 - PAUSE_BG_HEIGHT / 2);

        static bool wasHoveringMenu = false;
        bool isHoveringMenu = isHoveringSurface(END_MENU_X, END_MENU_Y, END_MENU_WIDTH, END_MENU_HEIGHT);

        if (isHoveringMenu)
        {
            if (!wasHoveringMenu)
                gamesound.playSound(gamesound.snd_hover);
            img_menu_end_menu_alt.Draw(screen, END_MENU_X, END_MENU_Y);
        }
        else
        {
            img_menu_end_menu.Draw(screen, END_MENU_X, END_MENU_Y);
        }

        wasHoveringMenu = isHoveringMenu;

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

    void Menu::setMousePosition(int x, int y)
    {
        mouseX = x;
        mouseY = y;
    }
}
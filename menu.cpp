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

    Sprite img_menu_bg(new Surface("assets/menu.png"), 1);
    Sprite img_start_button(new Surface("assets/start_button.png"), 1);
    Sprite img_lvl1_button(new Surface("assets/button_lvl1.png"), 1);
    Sprite img_lvl2_button(new Surface("assets/button_lvl2.png"), 1);
    Sprite img_lvl3_button(new Surface("assets/button_lvl3.png"), 1);
    Sprite img_lvl4_button(new Surface("assets/button_lvl4.png"), 1);
    Sprite img_lvl5_button(new Surface("assets/button_lvl5.png"), 1);
    Sprite img_menu_next_level(new Surface("assets/menu_next_level.png"), 1);
    Sprite img_button_next_level(new Surface("assets/button_next_level.png"), 1);
    Sprite img_button_next_level_menu(new Surface("assets/button_next_level_menu.png"), 1);
    Sprite img_pause_menu(new Surface("assets/menu_pause.png"), 1);
    Sprite img_button_resume(new Surface("assets/button_resume.png"), 1);
    Sprite img_button_quit(new Surface("assets/button_quit.png"), 1);

    bool Menu::isHoveringSurface(int x, int y, int width, int height)
    {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }

    void Menu::openMainMenu(Surface* screen)
    {
        if (!mainMenuOpen) return;

        img_menu_bg.Draw(screen, 0, 0);

        img_start_button.Draw(screen, MAIN_ENTER_X, MAIN_ENTER_Y);
        img_lvl1_button.Draw(screen, MAIN_LVL1_X, MAIN_LVL1_Y);
        img_lvl2_button.Draw(screen, MAIN_LVL2_X, MAIN_LVL2_Y);
        img_lvl3_button.Draw(screen, MAIN_LVL3_X, MAIN_LVL3_Y);
        img_lvl4_button.Draw(screen, MAIN_LVL4_X, MAIN_LVL4_Y);
        img_lvl5_button.Draw(screen, MAIN_LVL5_X, MAIN_LVL5_Y);

        bool isHoveringLVL1 = isHoveringSurface(MAIN_LVL1_X, MAIN_LVL1_Y, MAIN_LVL_WIDTH, MAIN_LVL_HEIGHT);
        bool isHoveringLVL2 = isHoveringSurface(MAIN_LVL2_X, MAIN_LVL2_Y, MAIN_LVL_WIDTH, MAIN_LVL_HEIGHT);
        bool isHoveringLVL3 = isHoveringSurface(MAIN_LVL3_X, MAIN_LVL3_Y, MAIN_LVL_WIDTH, MAIN_LVL_HEIGHT);
        bool isHoveringLVL4 = isHoveringSurface(MAIN_LVL4_X, MAIN_LVL4_Y, MAIN_LVL_WIDTH, MAIN_LVL_HEIGHT);
        bool isHoveringLVL5 = isHoveringSurface(MAIN_LVL5_X, MAIN_LVL5_Y, MAIN_LVL_WIDTH, MAIN_LVL_HEIGHT);
        bool isHoveringEnter = isHoveringSurface(MAIN_ENTER_X, MAIN_ENTER_Y, MAIN_START_WIDTH, MAIN_START_HEIGHT);

        if ((isHoveringLVL1 || isHoveringEnter) && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            level.level_finished = false;
            start_game = true;
            resume_game = true;
            manualPaused = false;
            mainMenuOpen = false;
            level.loadLevel(1);
        }
        else if (isHoveringLVL2 && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            level.level_finished = false;
            start_game = true;
            resume_game = true;
            manualPaused = false;
            mainMenuOpen = false;
            level.loadLevel(2);
        }
        else if (isHoveringLVL3 && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            level.level_finished = false;
            start_game = true;
            resume_game = true;
            manualPaused = false;
            mainMenuOpen = false;
            level.loadLevel(3);
        }
        else if (isHoveringLVL4 && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            printf("Level 4 is not ready yet.");
        }
        else if (isHoveringLVL5 && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            printf("Level 5 is not ready yet.");
        }
    }

    void Menu::openNextMenu(Surface* screen)
    {
        nextMenuOpen = level.level_finished;
        if (!nextMenuOpen) return;

        img_menu_next_level.Draw(screen, SCREEN_WIDTH / 2 - NEXT_BG_WIDTH / 2, SCREEN_HEIGHT / 2 - NEXT_BG_HEIGHT / 2);
        img_button_next_level_menu.Draw(screen, NEXT_MENU_X, NEXT_MENU_Y);
        img_button_next_level.Draw(screen, NEXT_LVL_X, NEXT_LVL_Y);
 
        bool isHoveringNXTMENU = isHoveringSurface(NEXT_MENU_X, NEXT_MENU_Y, NEXT_NEXT_WIDTH, NEXT_NEXT_HEIGHT);
        bool isHoveringNXTLVL = isHoveringSurface(NEXT_LVL_X, NEXT_LVL_Y, NEXT_NEXT_WIDTH, NEXT_NEXT_HEIGHT);

        bool pressingNext = (isHoveringNXTLVL && isMousePressed) || (GetAsyncKeyState(VK_RETURN) & 0x8000);
        bool pressingMenu = (isHoveringNXTMENU && isMousePressed);

        // If [NEXT]
        if (pressingNext && !alreadyClickedNextLevel)
        {    
            gamesound.playSound(gamesound.snd_select);
            resume_game = true;
            level.loadLevel(tilemap.incrementMapIndex());
            level.level_finished = false;
            alreadyClickedNextLevel = true; 
            nextMenuOpen = false;
        }

        // If NONE
        else if (!pressingNext)
        {
            alreadyClickedNextLevel = false; 
        }

        // If [MENU]
        if (pressingMenu)
        {
            gamesound.playSound(gamesound.snd_select);
            start_game = false;
            nextMenuOpen = false;
            mainMenuOpen = true;
        }
    }

    void Menu::openPauseMenu(Surface* screen)
    {
        if (!pauseMenuOpen) return;

        img_pause_menu.Draw(screen, SCREEN_WIDTH / 2 - PAUSE_BG_WIDTH / 2, SCREEN_HEIGHT / 2 - PAUSE_BG_HEIGHT / 2);
        img_button_quit.Draw(screen, PAUSE_QUIT_X, PAUSE_QUIT_Y);
        img_button_resume.Draw(screen, PAUSE_RESUME_X, PAUSE_RESUME_Y);

        bool isHoveringQuit = isHoveringSurface(PAUSE_QUIT_X, PAUSE_QUIT_Y, PAUSE_QUIT_WIDTH, PAUSE_QUIT_HEIGHT);
        bool isHoveringResume = isHoveringSurface(PAUSE_RESUME_X, PAUSE_RESUME_Y, PAUSE_QUIT_WIDTH, PAUSE_QUIT_HEIGHT);

        // If [QUIT]
        if (isHoveringQuit && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            start_game = false;
            resume_game = false;
            mainMenuOpen = true;
            pauseMenuOpen = false;
        }

        // If [RESUME]
        else if (isHoveringResume && isMousePressed)
        {
            gamesound.playSound(gamesound.snd_select);
            manualPaused = false;
            resume_game = true;
            pauseMenuOpen = false;
        }
    }

    void Menu::manageNextMenu(Surface* screen)
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
    }

    void Menu::setMousePosition(int x, int y)
    {
        mouseX = x;
        mouseY = y;
    }
}
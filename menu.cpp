#include "menu.h"
#include "game.h"  // To call MouseMove if needed
#include "windows.h"
#include "tilemap.h"
#include <stdio.h>
#include <iostream>
#include <thread>

namespace Tmpl8
{
    Menu::Menu(Level& levelRef, Player& playerRef, TileMap& tilemapRef) :
        level(levelRef),
        player(playerRef),
        tilemap(tilemapRef)
    {}

    Sprite img_menu_bg(new Surface("assets/menu.png"), 1);
    Sprite img_start_button(new Surface("assets/start_button.png"), 1);
    Sprite img_lvl1_button(new Surface("assets/button_lvl1.png"), 1);
    Sprite img_lvl2_button(new Surface("assets/button_lvl2.png"), 1);
    Sprite img_lvl3_button(new Surface("assets/button_lvl3.png"), 1);
    Sprite img_menu_next_level(new Surface("assets/menu_next_level.png"), 1);
    Sprite img_button_next_level(new Surface("assets/button_next_level.png"), 1);
    Sprite img_button_next_level_menu(new Surface("assets/button_next_level_menu.png"), 1);

    void Menu::drawMenu(Surface* screen)
    {
        // Draw background and buttons
        img_menu_bg.Draw(screen, 0, 0);
        detectLevelHover();

        int startX = SCREEN_WIDTH / 2 - START_BUTTON_WIDTH / 2;
        int startY = SCREEN_HEIGHT / 2 - START_BUTTON_HEIGHT / 2 + 80;
        img_start_button.Draw(screen, startX, startY);

        int lvlButtonWidth = img_lvl1_button.GetWidth();
        int totalWidth = 3 * lvlButtonWidth + 2 * SPACING;
        int groupStartX = SCREEN_WIDTH / 2 - totalWidth / 2;
        int lvlY = startY + START_BUTTON_HEIGHT + SPACING;

        img_lvl1_button.Draw(screen, groupStartX, lvlY);
        img_lvl2_button.Draw(screen, groupStartX + lvlButtonWidth + SPACING, lvlY);
        img_lvl3_button.Draw(screen, groupStartX + 2 * (lvlButtonWidth + SPACING), lvlY);
    }

    bool Menu::isHoveringSurface(int x, int y, int width, int height)
    {
        return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
    }

    void Menu::detectLevelHover()
    {
        bool isHoveringLVL1 = isHoveringSurface(LVL1X, LVLY, LVL_BUTTON_WIDTH, LVL_BUTTON_HEIGHT);
        bool isHoveringLVL2 = isHoveringSurface(LVL2X, LVLY, LVL_BUTTON_WIDTH, LVL_BUTTON_HEIGHT);
        bool isHoveringLVL3 = isHoveringSurface(LVL3X, LVLY, LVL_BUTTON_WIDTH, LVL_BUTTON_HEIGHT);
        bool isHoveringEnter = isHoveringSurface(ENTER_BUTTON_X, ENTER_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT);

        if ((isHoveringLVL1 || isHoveringEnter) && isMousePressed)
        {
            start_game = true;
            level.loadLevel(1);
        }
        else if (isHoveringLVL2 && isMousePressed)
        {
            start_game = true;
            level.loadLevel(2);
        }
        else if (isHoveringLVL3 && isMousePressed)
        {
            start_game = true;
            level.loadLevel(3);
        }
    }

    void Menu::drawNextMenu(Surface* screen)
    {
        detectNextLevelHover();
        img_menu_next_level.Draw(screen, SCREEN_WIDTH / 2 - MENU_NXT_LVL_WIDTH / 2, SCREEN_HEIGHT / 2 - MENU_NXT_LVL_HEIGHT / 2);
        img_button_next_level_menu.Draw(screen, NXTMENUX, NXTMENUY);
        img_button_next_level.Draw(screen, NXTLVLX, NXTLVLY);
    }


    void Menu::detectNextLevelHover()
    {
        bool isHoveringNXTMENU = isHoveringSurface(NXTMENUX, NXTMENUY, BUTTON_NXT_LVL_WIDTH, BUTTON_NXT_LVL_HEIGHT);
        bool isHoveringNXTLVL = isHoveringSurface(NXTLVLX, NXTLVLY, BUTTON_NXT_LVL_WIDTH, BUTTON_NXT_LVL_HEIGHT);

        bool pressingNext = (isHoveringNXTLVL && isMousePressed) || (GetAsyncKeyState(VK_RETURN) & 0x8000);
        bool pressingMenu = (isHoveringNXTMENU && isMousePressed);

        if (pressingNext && !alreadyClickedNextLevel)
        {
            resume_game = true;
            level.loadLevel(tilemap.incrementMapIndex());
            level.level_finished = false;
            alreadyClickedNextLevel = true; 
        }
        else if (!pressingNext)
        {
            alreadyClickedNextLevel = false; 
        }

        if (pressingMenu)
        {
            start_game = false;
        }
    }


    void Menu::manageNextMenu(Surface* screen, bool level_finished)
    {
        static bool pPressedLastFrame = false;
        static bool manualPaused = false;

        bool isPDown = GetAsyncKeyState('P') & 0x8000;
        bool press = isPDown && !pPressedLastFrame;

        if (press)
        {
            manualPaused = !manualPaused;
        }

        pPressedLastFrame = isPDown;

        if (level_finished)
        {
            drawNextMenu(screen);
            detectNextLevelHover();
            resume_game = false;
        }
        else
        {
            resume_game = !manualPaused;
        }
    }

    void Menu::setMousePosition(int x, int y)
    {
        mouseX = x;
        mouseY = y;
    }

    bool Menu::manageGameStart()
    {
        static bool enterPressedLastFrame = false;
        static int game_state = 0;
        bool isEnterDown = GetAsyncKeyState(VK_RETURN) & 0x8000;

        if (isEnterDown && !enterPressedLastFrame)
        {
            level.loadLevel(1);
            game_state++;
            start_game = (game_state % 2) == 1; 
        }
        enterPressedLastFrame = isEnterDown;
        return start_game;
    }

    bool Menu::manageGamePause()
    {
        return resume_game ;
    }

    void Menu::skipAFrame(bool& isTDown)
    {
        if (GetAsyncKeyState('T') & 0x8000) isTDown = !isTDown;

        if (isTDown)
        {
            resume_game = true;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            resume_game = false;
        }
    }
}
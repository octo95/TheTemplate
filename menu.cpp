#include "menu.h"
#include "game.h"  // To call MouseMove if needed
#include "windows.h"
#include "tilemap.h"
#include <stdio.h>
#include <iostream>
#include <thread>

namespace Tmpl8
{
    Menu::Menu(Level& levelRef, Player& playerRef) :
        level(levelRef),
        player(playerRef)
    {}

    Sprite img_menu_bg(new Surface("assets/menu.png"), 1);
    Sprite img_start_button(new Surface("assets/start_button.png"), 1);
    Sprite img_lvl1_button(new Surface("assets/button_lvl1.png"), 1);
    Sprite img_lvl2_button(new Surface("assets/button_lvl2.png"), 1);
    Sprite img_lvl3_button(new Surface("assets/button_lvl3.png"), 1);

    const int START_BUTTON_WIDTH = img_start_button.GetWidth();
    const int START_BUTTON_HEIGHT = img_start_button.GetHeight();
    const int LVL_BUTTON_WIDTH = img_lvl1_button.GetWidth();
    const int LVL_BUTTON_HEIGHT = img_lvl1_button.GetHeight();

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

    void Menu::detectLevelHover()
    {
        int lvl1X = SCREEN_WIDTH / 2 - (MAP_AMOUNT * LVL_BUTTON_WIDTH + (MAP_AMOUNT-1) * SPACING) / 2;
        int lvl2X = lvl1X + LVL_BUTTON_WIDTH + SPACING;
        int lvl3X = lvl2X + LVL_BUTTON_WIDTH + SPACING;
        int lvlY = SCREEN_HEIGHT / 2 - START_BUTTON_HEIGHT / 2 + 80 + START_BUTTON_HEIGHT + SPACING;
        int enterButtonX = SCREEN_WIDTH / 2 - START_BUTTON_WIDTH / 2;
        int enterButtonY = SCREEN_WIDTH / 2 - START_BUTTON_HEIGHT / 2 - 80;

        bool isHoveringLVL1 =   mouseX >= lvl1X && mouseX <= lvl1X + LVL_BUTTON_WIDTH && 
                                mouseY >= lvlY && mouseY <= lvlY + LVL_BUTTON_HEIGHT;

        bool isHoveringLVL2 =   mouseX >= lvl2X && mouseX <= lvl2X + LVL_BUTTON_WIDTH && 
                                mouseY >= lvlY && mouseY <= lvlY + LVL_BUTTON_HEIGHT;

        bool isHoveringLVL3 =   mouseX >= lvl3X && mouseX <= lvl3X + LVL_BUTTON_WIDTH && 
                                mouseY >= lvlY && mouseY <= lvlY + LVL_BUTTON_HEIGHT;

        bool isHoveringEnter =  mouseX >= enterButtonX && mouseX <= enterButtonX + START_BUTTON_WIDTH &&
                                mouseY >= enterButtonY && mouseY <= enterButtonY + START_BUTTON_HEIGHT;
        
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
            game_state++;
            start_game = (game_state % 2) == 1; 
            level.loadLevel(1);
        }
        enterPressedLastFrame = isEnterDown;
        return start_game;
    }

    bool Menu::manageGamePause()
    {
        static bool pPressedLastFrame = false;
        static bool resume_game = true; 
        bool isPDown = GetAsyncKeyState('P') & 0x8000;

        if (isPDown && !pPressedLastFrame) resume_game = !resume_game; 
       
        pPressedLastFrame = isPDown;
        return resume_game;
    }

    void Menu::skipAFrame(bool& isTDown)
    {

        //static bool tPressedLastFrame = false;
        if (GetAsyncKeyState('T') & 0x8000) isTDown = !isTDown;

        if (isTDown)
        {
            resume_game = true;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            resume_game = false;
        }


        //tPressedLastFrame = isTDown;
    }


}

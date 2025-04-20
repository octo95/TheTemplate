#include "menu.h"
#include "game.h"  // To call MouseMove if needed
#include "windows.h"
#include "tilemap.h"
#include <stdio.h>
#include <iostream>

namespace Tmpl8
{
    Menu::Menu(TileMap& tilemapRef, Player& playerRef) :
        tilemap(tilemapRef),
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
        screen->Clear(0);
        img_menu_bg.Draw(screen, 0, 0);
        detectLevelHover();

        int startX = SCREEN_WIDTH / 2 - START_BUTTON_WIDTH / 2;
        int startY = SCREEN_HEIGHT / 2 - START_BUTTON_HEIGHT / 2 + 80;
        img_start_button.Draw(screen, startX, startY);

        int spacing = 20;
        int lvlButtonWidth = img_lvl1_button.GetWidth();
        int totalWidth = 3 * lvlButtonWidth + 2 * spacing;
        int groupStartX = SCREEN_WIDTH / 2 - totalWidth / 2;
        int lvlY = startY + START_BUTTON_HEIGHT + spacing;

        img_lvl1_button.Draw(screen, groupStartX, lvlY);
        img_lvl2_button.Draw(screen, groupStartX + lvlButtonWidth + spacing, lvlY);
        img_lvl3_button.Draw(screen, groupStartX + 2 * (lvlButtonWidth + spacing), lvlY);
    }

    void Menu::detectLevelHover()
    {
        int lvl1X = SCREEN_WIDTH / 2 - (3 * LVL_BUTTON_WIDTH + 2 * 20) / 2;
        int lvl2X = lvl1X + LVL_BUTTON_WIDTH + 20;
        int lvl3X = lvl2X + LVL_BUTTON_WIDTH + 20;
        int lvlY = SCREEN_HEIGHT / 2 - START_BUTTON_HEIGHT / 2 + 80 + START_BUTTON_HEIGHT + 20;

        bool isHoveringLVL1 = mouseX >= lvl1X && mouseX <= lvl1X + LVL_BUTTON_WIDTH && mouseY >= lvlY && mouseY <= lvlY + LVL_BUTTON_HEIGHT;
        bool isHoveringLVL2 = mouseX >= lvl2X && mouseX <= lvl2X + LVL_BUTTON_WIDTH && mouseY >= lvlY && mouseY <= lvlY + LVL_BUTTON_HEIGHT;
        bool isHoveringLVL3 = mouseX >= lvl3X && mouseX <= lvl3X + LVL_BUTTON_WIDTH && mouseY >= lvlY && mouseY <= lvlY + LVL_BUTTON_HEIGHT;
        
        if (isHoveringLVL1 && isMousePressed)
        {
            start_game = true;
            tilemap.loadLevel(1);
        }
        else if (isHoveringLVL2 && isMousePressed)
        {
            start_game = true;
            tilemap.loadLevel(2);
        }
        else if (isHoveringLVL3 && isMousePressed)
        {
            start_game = true;
            tilemap.loadLevel(3);
        }
    }

    void Menu::setMousePosition(int x, int y)
    {
        mouseX = x;
        mouseY = y;
    }

    bool Menu::startGame()
    {
        if (GetAsyncKeyState(VK_RETURN))
        {
            start_game = true;
        }
        return start_game;
    }
}

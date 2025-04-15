#define WIN32_LEAN_AND_MEAN
#include "menu.h"
#include "surface.h"
#include "windows.h"
#include "tilemap.h"
#include <stdio.h>

namespace Tmpl8
{
	Sprite img_menu_bg(new Surface("assets/menu.png"), 1);
	Sprite img_start_button(new Surface("assets/start_button.png"), 1);
	Sprite img_lvl1_button(new Surface("assets/button_lvl1.png"), 1);
	Sprite img_lvl2_button(new Surface("assets/button_lvl2.png"), 1);
	Sprite img_lvl3_button(new Surface("assets/button_lvl3.png"), 1);

	const int START_BUTTON_WIDTH = img_start_button.GetWidth();
	const int START_BUTTON_HEIGHT = img_start_button.GetHeight();

	void Menu::drawMenu(Surface* screen)
	{
		screen->Clear(0);
		img_menu_bg.Draw(screen, 0, 0);

		// Draw the Start button
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

	void Menu::loadLevelMenu()
	{
		TileMap map;
		int level = 0;
		switch (level)
		{
			case 1:
				map.setMapIndex(1);
			case 2:
				map.setMapIndex(2);
			case 3:
				map.setMapIndex(3);
		}
	}
}

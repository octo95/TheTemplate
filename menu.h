#pragma once
#include "surface.h"
#include "level.h"
#include "player.h"
#include "tilemap.h"

namespace Tmpl8
{
	const int SPACING = 20;

	extern Sprite img_menu_bg;
	extern Sprite img_start_button;
	extern Sprite img_menu_bg;
	extern Sprite img_start_button;
	extern Sprite img_lvl1_button;
	extern Sprite img_lvl2_button;
	extern Sprite img_lvl3_button;
	extern Sprite img_menu_next_level;
	extern Sprite img_button_next_level;
	extern Sprite img_button_next_level_menu;

	class Menu
	{
	public:
		Menu(Level& levelRef, Player& playerRef, TileMap& tilemapRef);
		void drawMenu(Surface* screen);
		void drawNextMenu(Surface* screen);
		void manageNextMenu(Surface* screen, bool level_finished);
		void setMousePosition(int x, int y); 
		void detectLevelHover();
		void detectNextLevelHover();
		void setMouseState(bool isPressed) { isMousePressed = isPressed; }
		bool manageGameStart();
		bool manageGamePause();
		void skipAFrame(bool& isTDown);
		bool Menu::isHoveringSurface(int x, int y, int width, int height);

	private:
		Level& level;
		Player& player;
		TileMap& tilemap;

		int mouseX, mouseY; 
		bool start_game = false;
		bool resume_game = true;
		bool isMousePressed = false;
		bool alreadyClickedNextLevel = false;

		// Offsets
		const int BUTTON_OFFSET_Y = 80;
		const int BUTTON_OFFSET_X = 50;

		// Buttons dimensions
		const int START_BUTTON_WIDTH = img_start_button.GetWidth();
		const int START_BUTTON_HEIGHT = img_start_button.GetHeight();
		const int LVL_BUTTON_WIDTH = img_lvl1_button.GetWidth();
		const int LVL_BUTTON_HEIGHT = img_lvl1_button.GetHeight();
		const int MENU_NXT_LVL_WIDTH = img_menu_next_level.GetWidth();
		const int MENU_NXT_LVL_HEIGHT = img_menu_next_level.GetHeight();
		const int BUTTON_NXT_LVL_WIDTH = img_button_next_level.GetWidth();
		const int BUTTON_NXT_LVL_HEIGHT = img_button_next_level.GetHeight();
		const int BUTTON_NXT_LVL_MENU_WIDTH = img_button_next_level_menu.GetWidth();
		const int BUTTON_NXT_LVL_MENU_HEIGHT = img_button_next_level_menu.GetHeight();

		// Buttons positions
		const int NXTMENUX = SCREEN_WIDTH / 2 - BUTTON_NXT_LVL_MENU_WIDTH / 2 - BUTTON_OFFSET_X;
		const int NXTMENUY = SCREEN_HEIGHT / 2 - BUTTON_NXT_LVL_MENU_HEIGHT / 2 + BUTTON_OFFSET_X;
		const int NXTLVLX = SCREEN_WIDTH / 2 - BUTTON_NXT_LVL_WIDTH / 2 + BUTTON_OFFSET_X;
		const int NXTLVLY = SCREEN_HEIGHT / 2 - BUTTON_NXT_LVL_HEIGHT / 2 + BUTTON_OFFSET_X;
		const int LVL1X = SCREEN_WIDTH / 2 - (MAP_AMOUNT * LVL_BUTTON_WIDTH + (MAP_AMOUNT - 1) * SPACING) / 2;
		const int LVL2X = LVL1X + LVL_BUTTON_WIDTH + SPACING;
		const int LVL3X = LVL2X + LVL_BUTTON_WIDTH + SPACING;
		const int LVLY = SCREEN_HEIGHT / 2 - START_BUTTON_HEIGHT / 2 + BUTTON_OFFSET_Y + START_BUTTON_HEIGHT + SPACING;
		const int ENTER_BUTTON_X = SCREEN_WIDTH / 2 - START_BUTTON_WIDTH / 2;
		const int ENTER_BUTTON_Y = SCREEN_WIDTH / 2 - START_BUTTON_HEIGHT / 2 - BUTTON_OFFSET_Y;
	};
}
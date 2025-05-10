#pragma once
#include "menu.h"

namespace Tmpl8
{
	extern Sprite img_menu_main_bg;
	extern Sprite img_menu_main_start;
	extern Sprite img_menu_main_bg;
	extern Sprite img_menu_main_start;
	extern Sprite img_menu_main_lvl1;
	extern Sprite img_menu_main_lvl2;
	extern Sprite img_menu_main_lvl3;
	extern Sprite img_menu_main_difficulty_easy;
	extern Sprite img_menu_main_difficulty_medium;
	extern Sprite img_menu_main_difficulty_hard;
	extern Sprite img_menu_main_info_info;
	extern Sprite img_menu_main_info_bg;
	extern Sprite img_menu_main_info_quit;
	extern Sprite img_selected;

    class MenuMain : public Menu
    {

    public:
		MenuMain::MenuMain(Level& levelRef, Player& playerRef, TileMap& tilemapRef, GameSound& gamesoundRef, Text& textRef, Health& healthRef)
			: Menu(levelRef, playerRef, tilemapRef, gamesoundRef, textRef, healthRef)
		{
		}

		void drawMainBGPan(Surface* screen, float deltaTime);
        void openMainMenu(Surface* screen, float deltaTime);
		void openInfoMenu(Surface* screen, float deltaTime);
    private:
		float main_bg_x = 0.0f;

        // Main menu
        const int MAIN_START_WIDTH = img_menu_main_start.GetWidth();
        const int MAIN_START_HEIGHT = img_menu_main_start.GetHeight();
        const int MAIN_LVL_WIDTH = img_menu_main_lvl1.GetWidth();
        const int MAIN_LVL_HEIGHT = img_menu_main_lvl1.GetHeight();
        const int MAIN_DIFFICULTY_WIDTH = img_menu_main_difficulty_easy.GetWidth();
        const int MAIN_DIFFICULTY_HEIGHT = img_menu_main_difficulty_easy.GetHeight();

        const int MAIN_INFO_WIDTH = img_menu_main_info_info.GetWidth();
        const int MAIN_INFO_HEIGHT = img_menu_main_info_info.GetHeight();
        const int MAIN_INFO_BG_WIDTH = img_menu_main_info_bg.GetWidth();
        const int MAIN_INFO_BG_HEIGHT = img_menu_main_info_bg.GetHeight();
        const int MAIN_INFO_QUIT_WIDTH = img_menu_main_info_quit.GetWidth();
        const int MAIN_INFO_QUIT_HEIGHT = img_menu_main_info_quit.GetHeight();

		// Main menu

				// - LVLs
		const int MAIN_LVL1_X = SCREEN_HALF_WIDTH - (5 * MAIN_LVL_WIDTH + 4 * 20) / 2;
		const int MAIN_LVLS_Y = SCREEN_HALF_HEIGHT - MAIN_START_HEIGHT / 3 - SCREEN_HEIGHT / 3;

		const int MAIN_LVL2_X = MAIN_LVL1_X + MAIN_LVL_WIDTH + 20;
		const int MAIN_LVL3_X = MAIN_LVL2_X + MAIN_LVL_WIDTH + 20;
		const int MAIN_LVL4_X = MAIN_LVL3_X + MAIN_LVL_WIDTH + 20;
		const int MAIN_LVL5_X = MAIN_LVL4_X + MAIN_LVL_WIDTH + 20;

		// - Difficulties
		const int MAIN_EASY_X = SCREEN_HALF_WIDTH - (3 * MAIN_DIFFICULTY_WIDTH + 2 * 50) / 2;
		const int MAIN_DIFFICULTIES_Y = SCREEN_HALF_HEIGHT - MAIN_DIFFICULTY_HEIGHT / 2;

		const int MAIN_MEDIUM_X = MAIN_EASY_X + MAIN_DIFFICULTY_WIDTH + 50;
		const int MAIN_HARD_X = MAIN_MEDIUM_X + MAIN_DIFFICULTY_WIDTH + 50;

		// - Start
		const int MAIN_START_X = SCREEN_HALF_WIDTH - MAIN_START_WIDTH / 2;
		const int MAIN_START_Y = SCREEN_HALF_HEIGHT - MAIN_START_HEIGHT / 2 + SCREEN_HEIGHT / 3;

		// - Info
		const int MAIN_INFO_X = SCREEN_WIDTH - MAIN_INFO_WIDTH - 7;
		const int MAIN_INFO_Y = SCREEN_HEIGHT - MAIN_INFO_HEIGHT - 7;
		const int MAIN_INFO_QUIT_X = (SCREEN_WIDTH - MAIN_INFO_BG_WIDTH) / 2 + MAIN_INFO_BG_WIDTH - MAIN_INFO_QUIT_WIDTH - 5;
		const int MAIN_INFO_QUIT_Y = (SCREEN_HEIGHT - MAIN_INFO_BG_HEIGHT) / 2 + 5;
    };
}
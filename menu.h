#pragma once
#include "surface.h"
#include "level.h"
#include "player.h"
#include "tilemap.h"
#include "gamesound.h"

namespace Tmpl8
{
	extern Sprite img_menu_main_bg;
	extern Sprite img_menu_main_start;
	extern Sprite img_menu_main_bg;
	extern Sprite img_menu_main_start;
	extern Sprite img_menu_main_lvl1;
	extern Sprite img_menu_main_lvl2;
	extern Sprite img_menu_main_lvl3;
	extern Sprite img_menu_next_bg;
	extern Sprite img_menu_next_next;
	extern Sprite img_menu_next_menu;
	extern Sprite img_menu_pause_bg;
	extern Sprite img_menu_pause_resume;
	extern Sprite img_menu_pause_quit;
	extern Sprite img_menu_end_bg;
	extern Sprite img_menu_end_menu;
	extern Sprite img_menu_end_menu;
	extern Sprite img_menu_end_replay;


	class Menu
	{
	public:
		Menu(Level& levelRef, Player& playerRef, TileMap& tilemapRef, GameSound& gamesoundRef);
		void openMainMenu(Surface* screen);
		void openNextMenu(Surface* screen);
		void openPauseMenu(Surface* screen);
		void openEndMenu(Surface* screen);
		void manageMenus(Surface* screen);
		void setMousePosition(int x, int y); 
		void setMouseState(bool isPressed) { isMousePressed = isPressed; }
		bool isHoveringSurface(int x, int y, int width, int height);
		void manageLevelSelect(int index);

		bool start_game = false;
		bool resume_game = true;

	private:
		Level& level;
		Player& player;
		TileMap& tilemap;
		GameSound& gamesound;

		int mouseX, mouseY; 

		bool isMousePressed = false;
		bool manualPaused = false;
		bool alreadyClickedNextLevel = false;

		// Menu flags
		bool mainMenuOpen = true;
		bool pauseMenuOpen = false;
		bool nextMenuOpen = false;
		bool endMenuOpen = false;

		// Other consts
		const int SCREEN_HALF_WIDTH = SCREEN_WIDTH / 2;
		const int SCREEN_HALF_HEIGHT = SCREEN_HEIGHT / 2;

		// +-------------------+
		// | BUTTON DIMENSIONS |
		// +-------------------+

		// Main menu
		const int MAIN_START_WIDTH = img_menu_main_start.GetWidth();
		const int MAIN_START_HEIGHT = img_menu_main_start.GetHeight();
		const int MAIN_LVL_WIDTH = img_menu_main_lvl1.GetWidth();
		const int MAIN_LVL_HEIGHT = img_menu_main_lvl1.GetHeight();

		// Next level menu
		const int NEXT_BG_WIDTH = img_menu_next_bg.GetWidth();
		const int NEXT_BG_HEIGHT = img_menu_next_bg.GetHeight();
		const int NEXT_NEXT_WIDTH = img_menu_next_next.GetWidth();
		const int NEXT_NEXT_HEIGHT = img_menu_next_next.GetHeight();
		const int NEXT_MENU_WIDTH = img_menu_next_menu.GetWidth();
		const int NEXT_MENU_HEIGHT = img_menu_next_menu.GetHeight();

		// Pause menu
		const int PAUSE_BG_WIDTH = img_menu_pause_bg.GetWidth();
		const int PAUSE_BG_HEIGHT = img_menu_pause_bg.GetHeight();
		const int PAUSE_RESUME_WIDTH = img_menu_pause_resume.GetWidth();
		const int PAUSE_RESUME_HEIGHT = img_menu_pause_resume.GetHeight();
		const int PAUSE_QUIT_WIDTH = img_menu_pause_quit.GetWidth();
		const int PAUSE_QUIT_HEIGHT = img_menu_pause_quit.GetHeight();

		// End menu
		const int END_BG_WIDTH = img_menu_end_bg.GetWidth();
		const int END_BG_HEIGHT = img_menu_end_bg.GetHeight();
		const int END_MENU_WIDTH = img_menu_end_menu.GetWidth();
		const int END_MENU_HEIGHT = img_menu_end_menu.GetHeight();
		const int END_REPLAY_WIDTH = img_menu_end_replay.GetWidth();
		const int END_REPLAY_HEIGHT = img_menu_end_replay.GetHeight();

		// +------------------+
		// | BUTTON POSITIONS |
		// +------------------+

		// Main menu
		const int MAIN_LVL1_X = SCREEN_HALF_WIDTH - (5 * MAIN_LVL_WIDTH + 4 * 20) / 2;
		const int MAIN_LVL1_Y = SCREEN_HALF_HEIGHT - MAIN_START_HEIGHT / 3 - SCREEN_HEIGHT / 3;

		const int MAIN_LVL2_X = MAIN_LVL1_X + MAIN_LVL_WIDTH + 20;
		const int MAIN_LVL2_Y = MAIN_LVL1_Y;

		const int MAIN_LVL3_X = MAIN_LVL2_X + MAIN_LVL_WIDTH + 20;
		const int MAIN_LVL3_Y = MAIN_LVL1_Y;

		const int MAIN_LVL4_X = MAIN_LVL3_X + MAIN_LVL_WIDTH + 20;
		const int MAIN_LVL4_Y = MAIN_LVL1_Y;

		const int MAIN_LVL5_X = MAIN_LVL4_X + MAIN_LVL_WIDTH + 20;
		const int MAIN_LVL5_Y = MAIN_LVL1_Y;

		const int MAIN_START_X = SCREEN_HALF_WIDTH - MAIN_START_WIDTH / 2;
		const int MAIN_START_Y = SCREEN_HALF_HEIGHT - MAIN_START_HEIGHT / 2 + SCREEN_HEIGHT / 3;

		// Next level menu
		const int NEXT_MENU_X = SCREEN_HALF_WIDTH - NEXT_MENU_WIDTH / 2 - NEXT_BG_WIDTH / 4;
		const int NEXT_MENU_Y = SCREEN_HALF_HEIGHT - NEXT_MENU_HEIGHT / 2 + NEXT_BG_HEIGHT / 4;
		const int NEXT_LVL_X = SCREEN_HALF_WIDTH - NEXT_NEXT_WIDTH / 2 + NEXT_BG_WIDTH / 4;
		const int NEXT_LVL_Y = NEXT_MENU_Y;

		// Pause menu
		const int PAUSE_QUIT_X = SCREEN_HALF_WIDTH - PAUSE_QUIT_WIDTH / 2 - PAUSE_BG_WIDTH / 4;
		const int PAUSE_QUIT_Y = SCREEN_HALF_HEIGHT - PAUSE_RESUME_HEIGHT / 2 + PAUSE_BG_WIDTH / 5;
		const int PAUSE_RESUME_X = SCREEN_HALF_WIDTH - PAUSE_RESUME_WIDTH / 2 + PAUSE_BG_WIDTH / 4;
		const int PAUSE_RESUME_Y = PAUSE_QUIT_Y;

		// End menu
		const int END_MENU_X = SCREEN_HALF_WIDTH - END_MENU_WIDTH / 2 - END_BG_WIDTH / 4;
		const int END_MENU_Y = SCREEN_HALF_HEIGHT - END_MENU_HEIGHT / 2 + END_BG_HEIGHT / 4;
		const int END_REPLAY_X = SCREEN_HALF_WIDTH - END_REPLAY_WIDTH / 2 + END_BG_WIDTH / 4;
		const int END_REPLAY_Y = END_MENU_Y;
	};
}
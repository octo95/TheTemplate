#pragma once
#include "gamesound.h"
#include "level.h"
#include "player.h"
#include "surface.h"
#include "tilemap.h"

namespace Tmpl8
{
	// External variables
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
	extern Sprite img_audio_on;
	extern Sprite img_audio_off;
	extern Sprite img_menu_main_difficulty_easy;
	extern Sprite img_menu_main_difficulty_medium;
	extern Sprite img_menu_main_difficulty_hard;
	extern Sprite img_quit;

	class Menu
	{
		public:

			// Constructor
			Menu(
				Level& levelRef, 
				Player& playerRef, 
				TileMap& tilemapRef, 
				GameSound& gamesoundRef
			);

			// Variables
			bool start_game = false;
			bool resume_game = true;

			// Open menus
			void openMainMenu(Surface* screen);
			void openNextMenu(Surface* screen);
			void openPauseMenu(Surface* screen);
			void openEndMenu(Surface* screen);

			// Menu managers
			void manageMenus(Surface* screen);
			void manageLevelSelect(int index);
			void manageDifficultySelect(int index);
			void audioManagerOpen(Surface* screen);
			void quitManagerOpen(Surface* screen);

			// Mouse functions
			void setMousePosition(int x, int y); 
			void setMouseState(bool isPressed) { isMousePressed = isPressed; }
			bool isHoveringSurface(const vec2& pos, const vec2& size);


		private:
			Level& level;
			Player& player;
			TileMap& tilemap;
			GameSound& gamesound;

			// Variables
			int mouseX, mouseY; 
			int difficulty = 2; // 1: easy, 2: medium (default), 3: hard
			bool isMousePressed = false;
			bool manualPaused = false;
			bool alreadyClickedNextLevel = false;
			bool audioOn = true;

			// Menu flags
			bool mainMenuOpen = true;
			bool audioOpen = true;
			bool quitOpen = true;
			bool pauseMenuOpen = false;
			bool nextMenuOpen = false;
			bool endMenuOpen = false;

			// Other consts
			const int SCREEN_HALF_WIDTH = SCREEN_WIDTH / 2;
			const int SCREEN_HALF_HEIGHT = SCREEN_HEIGHT / 2;

			// +-------------------+
			// | BUTTON DIMENSIONS |
			// +-------------------+

			// Main menu sizes
			vec2 MAIN_START_SIZE = {
				img_menu_main_start.GetFloatWidth(),
				img_menu_main_start.GetFloatHeight()
			};
			vec2 MAIN_LVL_SIZE = {
				img_menu_main_lvl1.GetFloatWidth(),
				img_menu_main_lvl1.GetFloatHeight()
			};
			vec2 MAIN_DIFFICULTY_SIZE = {
				img_menu_main_difficulty_easy.GetFloatWidth(),
				img_menu_main_difficulty_easy.GetFloatHeight()
			};

			// Next level menu sizes
			vec2 NEXT_BG_SIZE = {
				img_menu_next_bg.GetFloatWidth(),
				img_menu_next_bg.GetFloatHeight()
			};
			vec2 NEXT_NEXT_SIZE = {
				img_menu_next_next.GetFloatWidth(),
				img_menu_next_next.GetFloatHeight()
			};
			vec2 NEXT_MENU_SIZE = {
				img_menu_next_menu.GetFloatWidth(),
				img_menu_next_menu.GetFloatHeight()
			};

			// Pause menu sizes
			vec2 PAUSE_BG_SIZE = {
				img_menu_pause_bg.GetFloatWidth(),
				img_menu_pause_bg.GetFloatHeight()
			};
			vec2 PAUSE_RESUME_SIZE = {
				img_menu_pause_resume.GetFloatWidth(),
				img_menu_pause_resume.GetFloatHeight()
			};
			vec2 PAUSE_QUIT_SIZE = {
				img_menu_pause_quit.GetFloatWidth(),
				img_menu_pause_quit.GetFloatHeight()
			};

			// End menu sizes
			vec2 END_BG_SIZE = {
				img_menu_end_bg.GetFloatWidth(),
				img_menu_end_bg.GetFloatHeight()
			};
			vec2 END_MENU_SIZE = {
				img_menu_end_menu.GetFloatWidth(),
				img_menu_end_menu.GetFloatHeight()
			};
			vec2 END_REPLAY_SIZE = {
				img_menu_end_replay.GetFloatWidth(),
				img_menu_end_replay.GetFloatHeight()
			};

			// Audio manager size
			vec2 AUDIO_SIZE = {
				img_audio_on.GetFloatWidth(),
				img_audio_on.GetFloatHeight()
			};

			// Quit manager size
			vec2 QUIT_SIZE = {
				img_quit.GetFloatWidth(),
				img_quit.GetFloatHeight()
			};

			// +------------------+
			// | BUTTON POSITIONS |
			// +------------------+

			// Main menu positions
			vec2 MAIN_LVL1_POS = {
				SCREEN_HALF_WIDTH - (5 * MAIN_LVL_SIZE.x + 4 * 20) / 2,
				SCREEN_HALF_HEIGHT - MAIN_START_SIZE.y / 3 - SCREEN_HEIGHT / 3
			};
			vec2 MAIN_LVL2_POS = {
				MAIN_LVL1_POS.x + MAIN_LVL_SIZE.x + 20,
				MAIN_LVL1_POS.y
			};
			vec2 MAIN_LVL3_POS = {
				MAIN_LVL2_POS.x + MAIN_LVL_SIZE.x + 20,
				MAIN_LVL2_POS.y
			};
			vec2 MAIN_LVL4_POS = {
				MAIN_LVL3_POS.x + MAIN_LVL_SIZE.x + 20,
				MAIN_LVL3_POS.y
			};
			vec2 MAIN_LVL5_POS = {
				MAIN_LVL4_POS.x + MAIN_LVL_SIZE.x + 20,
				MAIN_LVL4_POS.y
			};

			// Difficulty positions
			vec2 MAIN_EASY_POS = {
				SCREEN_HALF_WIDTH - (3 * MAIN_DIFFICULTY_SIZE.x + 2 * 50) / 2,
				SCREEN_HALF_HEIGHT - MAIN_DIFFICULTY_SIZE.y / 2
			};
			vec2 MAIN_MEDIUM_POS = {
				MAIN_EASY_POS.x + MAIN_DIFFICULTY_SIZE.x + 50,
				MAIN_EASY_POS.y
			};
			vec2 MAIN_HARD_POS = {
				MAIN_MEDIUM_POS.x + MAIN_DIFFICULTY_SIZE.x + 50,
				MAIN_MEDIUM_POS.y
			};

			// Start button position
			vec2 MAIN_START_POS = {
				SCREEN_HALF_WIDTH - MAIN_START_SIZE.x / 2,
				SCREEN_HALF_HEIGHT - MAIN_START_SIZE.y / 2 + SCREEN_HEIGHT / 3
			};

			// Next level menu positions
			vec2 NEXT_MENU_POS = {
				SCREEN_HALF_WIDTH - NEXT_MENU_SIZE.x / 2 - NEXT_BG_SIZE.x / 4,
				SCREEN_HALF_HEIGHT - NEXT_MENU_SIZE.y / 2 + NEXT_BG_SIZE.y / 4
			};
			vec2 NEXT_LVL_POS = {
				SCREEN_HALF_WIDTH - NEXT_NEXT_SIZE.x / 2 + NEXT_BG_SIZE.x / 4,
				NEXT_MENU_POS.y
			};

			// Pause menu positions
			vec2 PAUSE_QUIT_POS = {
				SCREEN_HALF_WIDTH - PAUSE_QUIT_SIZE.x / 2 - PAUSE_BG_SIZE.x / 4,
				SCREEN_HALF_HEIGHT - PAUSE_RESUME_SIZE.y / 2 + PAUSE_BG_SIZE.x / 5
			};
			vec2 PAUSE_RESUME_POS = {
				SCREEN_HALF_WIDTH - PAUSE_RESUME_SIZE.x / 2 + PAUSE_BG_SIZE.x / 4,
				PAUSE_QUIT_POS.y
			};

			// End menu positions
			vec2 END_MENU_POS = {
				SCREEN_HALF_WIDTH - END_MENU_SIZE.x / 2 - END_BG_SIZE.x / 4,
				SCREEN_HALF_HEIGHT - END_MENU_SIZE.y / 2 + END_BG_SIZE.y / 4
			};
			vec2 END_REPLAY_POS = {
				SCREEN_HALF_WIDTH - END_REPLAY_SIZE.x / 2 + END_BG_SIZE.x / 4,
				END_MENU_POS.y
			};

			// Audio position
			vec2 AUDIO_POS = {
				AUDIO_SIZE.x / 10,
				AUDIO_SIZE.y / 10
			};

			// Quit position
			vec2 QUIT_POS = {
				SCREEN_WIDTH - QUIT_SIZE.x - QUIT_SIZE.x / 10,
				QUIT_SIZE.y / 10
			};


	};
}

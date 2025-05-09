#pragma once
#include "gamesound.h"
#include "level.h"
#include "player.h"
#include "surface.h"
#include "tilemap.h"
#include "text.h"
#include "health.h"

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

	class Health;

	class Menu
	{
		public:

			// Constructor
			Menu(
				Level& levelRef, 
				Player& playerRef, 
				TileMap& tilemapRef, 
				GameSound& gamesoundRef,
				Text& textRef,
				Health& healthRef
			);

			// Variables
			int score = 0;
			int previousScore = 0;
			bool start_game = false;
			bool resume_game = true;
			float finish_sfx_played = false;

			// Score timer variables
			float score_timer = 0.0f;
			int score_value_current = 0;
			bool score_is_counting = true;

			// Open menus
			void drawMainBGPan(Surface* screen, float deltaTime);
			void openMainMenu(Surface* screen, float deltaTime);
			void openNextMenu(Surface* screen);
			void openPauseMenu(Surface* screen);
			void openEndMenu(Surface* screen);
			void openScoreMenu(Surface* screen, float deltaTime);

			// Menu managers
			void manageMenus(Surface* screen, float deltaTime);
			void manageLevelSelect(int index);
			void manageDifficultySelect(int index);
			void audioManagerOpen(Surface* screen);
			void quitManagerOpen(Surface* screen);

			// In game menus
			void addScore(int score_increment);
			void scoreInGame(Surface* screen, float deltaTime);
			void dashCountInGame(Surface* screen, float deltaTime);
			void timerInGame(Surface* screen, float deltaTime);

			// Mouse functions
			void setMousePosition(int x, int y); 
			void setMouseState(bool isPressed) { isMousePressed = isPressed; }
			bool isHoveringSurface(int x, int y, int width, int height);

			// Menu flags
			bool endMenuOpen = false;
			bool mainMenuOpen = true;
			bool audioOpen = true;
			bool quitOpen = true;
			bool pauseMenuOpen = false;
			bool nextMenuOpen = false;
			bool scoreMenuOpen = false;
			bool overMenuOpen = false;

			int difficulty = 2; // 1: easy, 2: medium (default), 3: hard
		private:
			Level& level;
			Player& player;
			TileMap& tilemap;
			GameSound& gamesound;
			Text& text;
			Health& health;

			// Variables
			int mouseX, mouseY; 
			bool isMousePressed = false;
			bool manualPaused = false;
			bool alreadyClickedNextLevel = false;
			bool audioOn = true;
			float main_bg_x = 0.0f;
			float timer_current = 0.0f;

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
			const int MAIN_DIFFICULTY_WIDTH = img_menu_main_difficulty_easy.GetWidth();
			const int MAIN_DIFFICULTY_HEIGHT = img_menu_main_difficulty_easy.GetHeight();
			//const int MAIN_INFO_WIDTH = img_menu_main_info_info.GetWidth();
			//const int MAIN_INFO_HEIGHT = img_menu_main_info_info.GetHeight();

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

			// Audio manager
			const int AUDIO_WIDTH = img_audio_on.GetWidth();
			const int AUDIO_HEIGHT = img_audio_on.GetHeight();

			// Quit manager
			const int QUIT_WIDTH = img_quit.GetWidth();
			const int QUIT_HEIGHT = img_quit.GetHeight();

			// +------------------+
			// | BUTTON POSITIONS |
			// +------------------+

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
			const int END_MENU_Y = SCREEN_HALF_HEIGHT - END_MENU_HEIGHT / 2 + END_BG_HEIGHT / 3;
			const int END_REPLAY_X = SCREEN_HALF_WIDTH - END_REPLAY_WIDTH / 2 + END_BG_WIDTH / 4;
			const int END_REPLAY_Y = END_MENU_Y;

			// Audio
			const int AUDIO_X = AUDIO_WIDTH / 10;
			const int AUDIO_Y = AUDIO_HEIGHT / 10;

			// Quit
			const int QUIT_X = SCREEN_WIDTH - QUIT_WIDTH - QUIT_WIDTH / 10;
			const int QUIT_Y = QUIT_HEIGHT / 10;
	};
}

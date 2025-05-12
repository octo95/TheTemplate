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
	extern Sprite img_menu_main_info_info;
	extern Sprite img_menu_main_info_bg;
	extern Sprite img_menu_main_info_quit;
	extern Sprite img_menu_over_bg;

	class Health;
	class MenuMain;

	class Menu
	{
		public:

			// Constructor
			Menu(
				GameSound& gamesound,
				Health& health,
				Level& level,
				Player& player,
				Text& text,
				TileMap& tilemap
			);


			// Open menus
			void drawMainBGPan(Surface* screen, float deltaTime);
			void openMainMenu(Surface* screen, float deltaTime);
			void openNextMenu(Surface* screen);
			void openPauseMenu(Surface* screen);
			void openEndMenu(Surface* screen, float deltaTime);
			void openResultsMenu(Surface* screen, float deltaTime);
			void openInfoMenu(Surface* screen, float deltaTime);

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
			void setMousePosition(vec2 pos) { mouse_pos = pos; }
			void setMouseState(bool isPressed) { isMousePressed = isPressed; }
			bool isHoveringSurface(vec2 pos, vec2 size);
			void handleButton(
				Surface* screen, 
				vec2 pos, vec2 size, 
				Sprite* 
				normalSprite, 
				Sprite* hoverSprite, 
				bool& wasHovering, 
				std::function<void()> onClick);

			// Menu State Flags
			bool mainMenuOpen = true;
			bool infoMenuOpen = false;
			bool endMenuOpen = false;
			bool pauseMenuOpen = false;
			bool nextMenuOpen = false;
			bool resultsMenuOpen = false;
			bool overMenuOpen = false;

			// Submenu Toggles
			bool audioOpen = true;
			bool quitOpen = true;

			// Mouse Input
			bool isMousePressed = false;
			bool wasMousePressedLastFrame = false;
			vec2 mouse_pos = vec2(0.0f, 0.0f);

			// Gameplay State
			bool start_game = false;
			bool resume_game = true;
			bool manualPaused = false;
			float timer_current = 0.0f;
			int difficulty = 2; // 1: easy, 2: medium (default), 3: hard

			// Audio Settings
			bool audioOn = true;
			bool finish_sfx_played = false;

			// Scoring System
			int score = 0;
			int previousScore = 0;
			float score_timer = 0.0f;
			int score_value_current = 0;
			bool score_is_counting = true;

	private:

		// Objects
		Level& level;
		Player& player;
		TileMap& tilemap;
		GameSound& gamesound;
		Text& text;
		Health& health;

		// +-------------------+
		// | BUTTON DIMENSIONS |
		// +-------------------+

		const vec2 SCREEN_HALF_SIZE = vec2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

		// Main menu
		const vec2 MAIN_START_SIZE = img_menu_main_start.GetSize();
		const vec2 MAIN_LVL_SIZE = img_menu_main_lvl1.GetSize();
		const vec2 MAIN_DIFFICULTY_SIZE = img_menu_main_difficulty_easy.GetSize();

		// Info
		const vec2 MAIN_INFO_SIZE = img_menu_main_info_info.GetSize();
		const vec2 MAIN_INFO_BG_SIZE = img_menu_main_info_bg.GetSize();
		const vec2 MAIN_INFO_QUIT_SIZE = img_menu_main_info_quit.GetSize();

		// Next level menu
		const vec2 NEXT_BG_SIZE = img_menu_next_bg.GetSize();
		const vec2 NEXT_NEXT_SIZE = img_menu_next_next.GetSize();
		const vec2 NEXT_MENU_SIZE = img_menu_next_menu.GetSize();

		// Pause menu
		const vec2 PAUSE_BG_SIZE = img_menu_pause_bg.GetSize();
		const vec2 PAUSE_RESUME_SIZE = img_menu_pause_resume.GetSize();
		const vec2 PAUSE_QUIT_SIZE = img_menu_pause_quit.GetSize();

		// End menu
		const vec2 END_BG_SIZE = img_menu_end_bg.GetSize();
		const vec2 END_BG_OVER_SIZE = img_menu_over_bg.GetSize();
		const vec2 END_MENU_SIZE = img_menu_end_menu.GetSize();
		const vec2 END_REPLAY_SIZE = img_menu_end_replay.GetSize();

		// Audio manager
		const vec2 AUDIO_SIZE = img_audio_on.GetSize();

		// Quit manager
		const vec2 QUIT_SIZE = img_quit.GetSize();

		// +------------------+
		// | BUTTON POSITIONS |
		// +------------------+

		// Main menu

		// - LVLs
		const vec2 MAIN_LVL1_POS = vec2(
			SCREEN_HALF_SIZE.x - (5.0f * MAIN_LVL_SIZE.x + 4.0f * 20.0f) / 2.0f,
			SCREEN_HALF_SIZE.y - MAIN_START_SIZE.y / 3.0f - SCREEN_HEIGHT / 3.0f
		);

		const vec2 MAIN_LVL2_POS = vec2(
			MAIN_LVL1_POS.x + MAIN_LVL_SIZE.x + 20.0f,
			MAIN_LVL1_POS.y
		);

		const vec2 MAIN_LVL3_POS = vec2(
			MAIN_LVL2_POS.x + MAIN_LVL_SIZE.x + 20.0f,
			MAIN_LVL2_POS.y
		);

		const vec2 MAIN_LVL4_POS = vec2(
			MAIN_LVL3_POS.x + MAIN_LVL_SIZE.x + 20.0f,
			MAIN_LVL3_POS.y
		);

		const vec2 MAIN_LVL5_POS = vec2(
			MAIN_LVL4_POS.x + MAIN_LVL_SIZE.x + 20.0f,
			MAIN_LVL4_POS.y
		);

		// - Difficulties
		const vec2 MAIN_EASY_POS = vec2(
			SCREEN_HALF_SIZE.x - (3.0f * MAIN_DIFFICULTY_SIZE.x + 2.0f * 50.0f) / 2.0f,
			SCREEN_HALF_SIZE.y - MAIN_DIFFICULTY_SIZE.y / 2.0f
		);

		const vec2 MAIN_MEDIUM_POS = vec2(
			MAIN_EASY_POS.x + MAIN_DIFFICULTY_SIZE.x + 50.0f,
			MAIN_EASY_POS.y
		);

		const vec2 MAIN_HARD_POS = vec2(
			MAIN_MEDIUM_POS.x + MAIN_DIFFICULTY_SIZE.x + 50.0f,
			MAIN_MEDIUM_POS.y
		);

		// - Start
		const vec2 MAIN_START_POS = vec2(
			SCREEN_HALF_SIZE.x - MAIN_START_SIZE.x / 2.0f,
			SCREEN_HALF_SIZE.y - MAIN_START_SIZE.y / 2.0f + SCREEN_HEIGHT / 3.0f
		);

		// - Info
		const vec2 MAIN_INFO_BG_POS = vec2(
			SCREEN_HALF_SIZE.x - MAIN_INFO_BG_SIZE.x / 2.0f,
			SCREEN_HALF_SIZE.y - MAIN_INFO_BG_SIZE.y / 2.0f
		);

		const vec2 MAIN_INFO_POS = vec2(
			SCREEN_WIDTH - MAIN_INFO_SIZE.x - 7.0f,
			SCREEN_HEIGHT - MAIN_INFO_SIZE.y - 7.0f
		);

		const vec2 MAIN_INFO_QUIT_POS = vec2(
			(SCREEN_WIDTH - MAIN_INFO_BG_SIZE.x) / 2.0f + MAIN_INFO_BG_SIZE.x - MAIN_INFO_QUIT_SIZE.x - 5.0f,
			(SCREEN_HEIGHT - MAIN_INFO_BG_SIZE.y) / 2.0f + 5.0f
		);

		// Next level menu
		const vec2 NEXT_MENU_POS = vec2(
			SCREEN_HALF_SIZE.x - NEXT_MENU_SIZE.x / 2.0f - NEXT_BG_SIZE.x / 4.0f,
			SCREEN_HALF_SIZE.y - NEXT_MENU_SIZE.y / 2.0f + NEXT_BG_SIZE.y / 3.0f
		);

		const vec2 NEXT_NEXT_POS = vec2(
			SCREEN_HALF_SIZE.x - NEXT_NEXT_SIZE.x / 2.0f + NEXT_BG_SIZE.x / 4.0f,
			NEXT_MENU_POS.y
		);

		// Pause menu
		const vec2 PAUSE_QUIT_POS = vec2(
			SCREEN_HALF_SIZE.x - PAUSE_QUIT_SIZE.x / 2.0f - PAUSE_BG_SIZE.x / 4.0f,
			SCREEN_HALF_SIZE.y - PAUSE_QUIT_SIZE.y / 2.0f + PAUSE_BG_SIZE.y / 3.0f
		);

		const vec2 PAUSE_RESUME_POS = vec2(
			SCREEN_HALF_SIZE.x - PAUSE_RESUME_SIZE.x / 2.0f + PAUSE_BG_SIZE.x / 4.0f,
			PAUSE_QUIT_POS.y
		);

		// End menu
		const vec2 END_MENU_POS = vec2(
			SCREEN_HALF_SIZE.x - END_MENU_SIZE.x / 2.0f - END_BG_SIZE.x / 4.0f,
			SCREEN_HALF_SIZE.y - END_MENU_SIZE.y / 2.0f + END_BG_SIZE.y / 3.0f
		);

		const vec2 END_REPLAY_POS = vec2(
			SCREEN_HALF_SIZE.x - END_REPLAY_SIZE.x / 2.0f + END_BG_SIZE.x / 4.0f,
			END_MENU_POS.y
		);

		// Audio
		const vec2 AUDIO_POS = vec2(
			AUDIO_SIZE.x / 10.0f,
			AUDIO_SIZE.y / 10.0f
		);

		// Quit
		const vec2 QUIT_POS = vec2(
			SCREEN_WIDTH - QUIT_SIZE.x - QUIT_SIZE.x / 10.0f,
			QUIT_SIZE.y / 10.0f
		);

	};
}

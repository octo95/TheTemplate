#pragma once
#include "surface.h"
#include "level.h"
#include "player.h"

namespace Tmpl8
{
	const int SPACING = 20;

	extern Sprite img_menu_bg;
	extern Sprite img_start_button;

	class Menu
	{
	public:
		Menu(Level& levelRef, Player& playerRef);
		void drawMenu(Surface* screen);
		void setMousePosition(int x, int y); 
		void detectLevelHover();
		void setMouseState(bool isPressed) { isMousePressed = isPressed; }
		bool manageGameStart();
		bool manageGamePause();
		void skipAFrame(bool& isTDown);

	private:
		Level& level;
		Player& player;
		int mouseX, mouseY; 
		bool start_game = false;
		bool resume_game = true;
		bool isMousePressed = false;
	};
}
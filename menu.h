#pragma once
#include "surface.h"
#include "tilemap.h"
#include "player.h"

namespace Tmpl8
{
	extern Sprite img_menu_bg;
	extern Sprite img_start_button;

	class Menu
	{
	public:
		Menu(TileMap& tilemap, Player& playerRef);
		void drawMenu(Surface* screen);
		void setMousePosition(int x, int y); 
		void detectLevelHover();
		void setMouseState(bool isPressed) { isMousePressed = isPressed; }
		bool startGame();

	private:
		TileMap& tilemap;
		Player& player;
		int mouseX, mouseY; 
		bool start_game = false;
		bool isMousePressed = false;
	};
}
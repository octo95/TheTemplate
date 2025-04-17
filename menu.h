#pragma once
#include "surface.h"
#include "camera.h"
#include "tilemap.h"

namespace Tmpl8
{
	// 
	// variables
	extern Sprite img_menu_bg;
	extern Sprite img_start_button;

	// Constants

	class Menu
	{
	public:
		void drawMenu(Surface* screen);
		void loadLevelMenu();
	private:
		Camera camera;
		TileMap map;
	};
}
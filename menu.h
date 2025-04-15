#pragma once
#include "surface.h"

namespace Tmpl8
{
	// Extern variables
	extern Sprite img_menu_bg;
	extern Sprite img_start_button;

	// Constants

	class Menu
	{
	public:
		void drawMenu(Surface* screen);
		void loadLevelMenu();
	};
}
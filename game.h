#pragma once
#include "tilemap.h"
#include "player.h"
#include "debug.h"
#include "menu.h"
#include "collectible.h"
#include "surface.h"
#include "template.h"
#include "tile.h"

namespace Tmpl8 
{
	extern TileMap map;
	extern Camera camera;
	extern Player player;
	extern Debug debug;
	extern Menu menu;
	extern Collectible collectible;

	class Game
	{
		public:
			void SetTarget( Surface* surface ) { screen = surface; }
			void Init();
			void Shutdown();
			void Tick( float deltaTime );
			void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
			void MouseMove(int x, int y) { mousex = x, mousey = y; }
			void KeyUp( int key ) { /* implement if you want to handle keys */ }
			void KeyDown( int key ) { /* implement if you want to handle keys */ }
		private:
			Surface* screen;
			Camera camera;
			int mousex, mousey; // UNUSED
			bool start_game = false;
	};
}

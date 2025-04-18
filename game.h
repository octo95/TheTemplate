#pragma once
#include "tilemap.h"
#include "menu.h"
#include "collectible.h"
#include "debug.h"
#include "player.h"
#include "tilemap.h"

namespace Tmpl8 
{
	// External variables
	// extern TileMap map;
	
	class Surface;
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
		Menu menu;
		Collectible collectible;
		Player player;
		Debug debug;
		TileMap map;
		int mousex, mousey; // TODO
		bool start_game = false;
	};

}

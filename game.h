#pragma once
#include "tilemap.h"

namespace Tmpl8 
{
	// External variables
	extern TileMap map;
	extern bool start_game;
	
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
		void startGame( float deltaTime );
	private:
		Surface* screen;
		Camera camera;
		int mousex, mousey;
};

}; // namespace Tmpl8

#pragma once
#include "tilemap.h"
#include "menu.h"
#include "collectible.h"
#include "debug.h"
#include "player.h"

#include <unordered_map>

namespace Tmpl8 
{
	class Surface;
	class Game
	{
	public:
		Game() : 
			player(tilemap),
			debug(camera, tilemap, player, collectible)
		{}

		Camera& GetCamera() { return camera; }
		Debug& GetDebug() { return debug; }
		Menu& GetMenu() { return menu;  }
		Player& GetPlayer() { return player; }
		TileMap& GetTileMap() { return tilemap; }
		CollectibleMap& GetCollectible() { return collectible; }

		void SetTarget( Surface* surface ) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int x, int y) { mousex = x, mousey = y; }
		void KeyUp( int key ) { /* implement if you want to handle keys */ }
		void KeyDown( int key ) { /* implement if you want to handle keys */ }

		~Game(){}
	private:
		// Graphics
		Surface* screen;
		Camera camera;
		Debug debug;
		Menu menu;
		
		// Gameplay
		CollectibleMap collectible = CollectibleMap();
		Player player;
		TileMap tilemap;
		
		int mousex, mousey; // TODO
		bool start_game = false;
	};
}
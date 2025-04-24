#pragma once
#include "camera.h"
#include "tilemap.h"
#include "menu.h"
#include "collectible.h"
#include "debug.h"
#include "player.h"
#include "wall.h"
#include "ai_follow.h"
#include "collisions.h"
#include "level.h"
#include "gamesound.h"
#include "health.h"

#include <unordered_map>

namespace Tmpl8 
{
	class Surface;
	class Game

	{
	public:

		Game() :
			player(camera),
			ai_follow(player, camera),
			debug(camera, tilemap, player, collectible, wall, ai_follow, level, collisions, menu),
			menu(level, player, tilemap, gamesound),
			tilemap(player),
			collisions(player, tilemap, ai_follow, collectible, wall, level, camera, gamesound),
			level(tilemap, player, ai_follow, collectible, wall, gamesound),
			health(player)
		{}

		void SetTarget( Surface* surface ) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void MouseUp( int button ) { menu.setMouseState(false); }
		void MouseDown(int button) { menu.setMouseState(true); }
		void MouseMove(int x, int y) 
		{ 
			mousex = x;
			mousey = y;
			menu.setMousePosition(mousex, mousey);
		}
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
		WallMap wall = WallMap();
		Player player;
		AI_Follow ai_follow;
		TileMap tilemap;
		Collisions collisions;
		Level level;
		GameSound gamesound;
		Health health;

		int mousex, mousey;
		bool start_game = false;
		vec2 player_pos;
		bool isTDown = false;
	};
}
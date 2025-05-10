#pragma once
#include "ai.h"
#include "ai_copy.h"
#include "ai_follow.h"
#include "ai_patrol.h"
#include "bell.h"
#include "camera.h"
#include "collectible.h"
#include "collisions.h"
#include "debug.h"
#include "gamesound.h"
#include "health.h"
#include "level.h"
#include "menu.h"
#include "player.h"
#include "tilemap.h"
#include "wall.h"
#include "circular_buffer.h"
#include "text.h"
#include "cloud.h"
#include "menu_main.h"

namespace Tmpl8 
{
	class Surface;
	class Game
	{
	public:

		Game() :
			player(camera),
			debug(camera, tilemap, player, collectible, wall, level, collisions, menu, ai_map),
			menu(level, player, tilemap, gamesound, text, health),
			tilemap(player),
			collisions(player, tilemap, level, camera, gamesound, ai_map, menu, health),
			level(tilemap, player, collectible, wall, gamesound, ai_map, camera, cloud),
			health(player),
			bell(level),
			menu_main(level, player, tilemap, gamesound, text, health)
		{}

		void SetTarget( Surface* surface ) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void MouseUp(int button) { menu.setMouseState(false); }
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
		CloudMap cloud = CloudMap();
		//MenuMap menu = MenuMap();
		Player player;
		AIMap ai_map = AIMap{ std::vector<AI_Copy>(), std::vector<AI_Follow>(), std::vector<AI_Patrol>() };
		TileMap tilemap;
		Collisions collisions;
		Level level;
		GameSound gamesound;
		Health health;
		Bell bell;
		CircularBuffer circular_buffer;
		Text text;
		MenuMain menu_main;

		int mousex, mousey;
		bool start_game = false;
		bool isTDown = false;
		float localTime = 0.0f;
		float frameTime = 0.0f;
	};
}
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
			bell(level),
			collisions(player, tilemap, level, camera, gamesound, ai_map, menu, health),
			debug(camera, tilemap, player, collectible, wall, level, collisions, menu, ai_map),
			health(player),
			level(tilemap, player, collectible, wall, gamesound, ai_map, camera, cloud),
			menu(level, player, tilemap, gamesound, text, health),
			player(camera),
			tilemap(player)
		{}

		void SetTarget( Surface* surface ) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void MouseUp(int button) { menu.setMouseState(false); }
		void MouseDown(int button) { menu.setMouseState(true); }
		void MouseMove(int x, int y) { menu.setMousePosition(x, y); }
		void KeyUp( int key ) {}
		void KeyDown( int key ) {}

		~Game(){}
	private:
		AIMap ai_map = AIMap{ std::vector<AI_Copy>(), std::vector<AI_Follow>(), std::vector<AI_Patrol>() };
		Bell bell;
		Camera camera;
		CircularBuffer circular_buffer;
		CloudMap cloud = CloudMap();
		CollectibleMap collectible = CollectibleMap();
		Collisions collisions;
		Debug debug;
		GameSound gamesound;
		Health health;
		Level level;
		Menu menu;
		Player player;
		Surface* screen;
		Text text;
		TileMap tilemap;
		WallMap wall = WallMap();

		float localTime = 0.0f;
		float frameTime = 0.0f;
	};
}
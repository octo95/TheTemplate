// +----------------------------------------------------------------------------+
// | _____ ____  _   _ ___ _____ ____     ____ ___  _     _     ___ ____  _____ |
// ||  ___|  _ \| | | |_ _|_   _/ ___|   / ___/ _ \| |   | |   |_ _|  _ \| ____||
// || |_  | |_) | | | || |  | | \___ \  | |  | | | | |   | |    | || | | |  _|  |
// ||  _| |  _ <| |_| || |  | |  ___) | | |__| |_| | |___| |___ | || |_| | |___ |
// ||_|   |_| \_\\___/|___| |_| |____/   \____\___/|_____|_____|___|____/|_____||
// |                                                                            |
// +----------------------------------------------------------------------------+

// Find all the documentation in both .h and .cpp files!
// Credits in game.cpp

#pragma once
#include "include/ai.h"
#include "include/ai_copy.h"
#include "include/ai_follow.h"
#include "include/ai_patrol.h"
#include "include/bell.h"
#include "include/camera.h"
#include "include/cloud.h"
#include "include/circular_buffer.h"
#include "include/collectible.h"
#include "include/collisions.h"
#include "include/debug.h"
#include "include/gamesound.h"
#include "include/health.h"
#include "include/level.h"
#include "include/menu.h"
#include "include/player.h"
#include "include/text.h"
#include "include/tilemap.h"
#include "include/wall.h"

namespace Tmpl8 
{
	class Surface;
	class Game
	{
	public:
		// Main game constructor, pass all the objects to their respective constructors as they are all created in game.h
		Game() :
			bell(level),
			collisions(ai_map, camera, gamesound, health, level, menu, player, tilemap),
			debug(ai_map, camera, collectible, collisions, level, menu, player, tilemap, wall),
			health(player),
			level(ai_map, camera, cloud, collectible, gamesound, player, tilemap, wall),
			menu(gamesound, health, level, player, text, tilemap),
			player(camera),
			tilemap(player)
		{}

		// Template functions.
		void SetTarget( Surface* surface ) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void GameLogic();
		void GameDraw(float deltaTime);
		void MouseUp(int button) { menu.setMouseState(false); }
		void MouseDown(int button) { menu.setMouseState(true); }
		void MouseMove(vec2 pos) { menu.setMousePosition(pos); }
		void KeyUp( int key ) {}
		void KeyDown( int key ) {}

		~Game(){}
	private:

		// Create all the objects for the game
		Bell bell;
		Camera camera;
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

		// Map objects
		AIMap ai_map = AIMap{ std::vector<AI_Copy>(), std::vector<AI_Follow>(), std::vector<AI_Patrol>() };
		CloudMap cloud = CloudMap();
		CollectibleMap collectible = CollectibleMap();
		WallMap wall = WallMap();

		// Variables
		vec2 new_pos;			// To determine the new position of the player next tick.
		float localTime = 0.0f;	// We split the calls of the functions between localTime and deltaTime allowing us
								// to pause only the functions that we want to pause as some still need to be running even during a pause.
		float frameTime = 0.0f;	// To cap the game at a specific FPS.
	};
}
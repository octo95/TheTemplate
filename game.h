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

namespace Tmpl8 
{
	class Surface;
	class Game
	{
	public:

		Game() :
			player(camera),
			debug(camera, tilemap, player, collectible, wall, ai_follow, level, collisions, menu, ai_patrol, ai_copy),
			menu(level, player, tilemap, gamesound, text),
			tilemap(player),
			collisions(player, tilemap, ai_follow, level, camera, gamesound, ai_patrol, ai_copy, menu),
			level(tilemap, player, ai_follow, collectible, wall, gamesound, ai_patrol, ai_copy),
			health(player),
			ai_follow(player, vec2(-500, -500), camera),   
			ai_patrol(player, vec2(-500, -500), camera),   
			ai_copy(player, vec2(-500, -500)),
			bell(level)
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
		Player player;
		AI_Follow ai_follow;
		AI_Patrol ai_patrol;
		TileMap tilemap;
		Collisions collisions;
		Level level;
		GameSound gamesound;
		Health health;
		Bell bell;
		AI_Copy ai_copy;
		CircularBuffer circular_buffer;
		Text text;

		std::vector<std::pair<AIType, AI*>> ai_map;

		// Dans loadlevel, load ai_map

		// void workAI(std::vector<std::pair<AIType, AI*>>& ai_map)
		// for(auto &ai : ai_map) {
		//		switch (ai.first())
		//		case Follow {
		//			AI_Follow* ai_follow = (AI_Follow*) ai.second()
		//			// whatever the AI needs to call or whatever...
		//		}
		//		case Follow {
		//			AI_Patrol* ai_patrol = (AI_Patrol*) ai.second()
		//			// whatever the AI needs to call or whatever...
		//		}
		//		case Follow {
		//			AI_Copy* ai_copy= (AI_Copy*) ai.second()
		//			// whatever the AI needs to call or whatever...
		//		}
		// }

		int mousex, mousey;
		bool start_game = false;
		bool isTDown = false;
		float localTime = 0.0f;
		float frameTime = 0.0f;
	};
}
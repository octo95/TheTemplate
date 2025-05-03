#pragma once
#include "surface.h"
#include "tile.h"
#include <map>
#include <iostream>
#include <functional>
#include <unordered_map>
#include "vec2_hash.h"
#include "gamesound.h"
#include "tilemap.h"
#include "player.h"

namespace Tmpl8
{
	extern Sprite img_wall;
	extern int walls_count;

	struct Wall
	{
		Tmpl8::vec2 pos;

		// Default Constructor
		Wall() :
			pos(vec2{ 0,0 })
		{};

		// Constructor
		Wall(Tmpl8::vec2 _pos) :
			pos(_pos)
		{};

		// Overloading == operator. Wall are equal if the coordinates are the same.
		bool operator==(const Wall& rhs) const noexcept
		{
			return this->pos == rhs.pos;
		}

		// Destructor
		~Wall() {};
	};

	// Definition of the WallMap type
	typedef std::unordered_map<vec2, Wall> WallMap;

	// Local functions
	void loadAllWalls(int map);
	void drawWallMap(Camera* camera, Surface* screen, WallMap* collectibles);
	void manageWallCollision(Player* player, GameSound* gamesound);
}
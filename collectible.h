#pragma once
#include "surface.h"
#include "tile.h"
#include <map>
#include <iostream>
#include <functional>
#include <unordered_map>
#include "vec2_hash.h"
#include "gamesound.h"

namespace Tmpl8
{
	extern Sprite img_collectible;
	extern int collectibles_collected;

	struct Collectible
	{
	public:
		Tmpl8::vec2 pos;

		// Default Constructor
		Collectible() :
			pos(vec2{ 0,0 })
		{};

		// Constructor
		Collectible(Tmpl8::vec2 _pos) :
			pos(_pos)
		{};

		// Overloading == operator. Collectible are equal if the coordinates are the same.
		bool operator==(const Collectible& rhs) const noexcept
		{
			return this->pos == rhs.pos;
		}

		// Destructor
		~Collectible() {};
	};

	typedef std::unordered_map<vec2, Collectible> CollectibleMap;

	void loadAllCollectibles(int map);
	void drawCollectibleMap(Camera* camera, Surface* screen);
	void manageCollectibleCollision(vec2 player_pos, GameSound* gamesound);
	void manageCollectibleRespawn(float deltaTime);
}
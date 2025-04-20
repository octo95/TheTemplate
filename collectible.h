#pragma once
#include "surface.h"
#include "tile.h"
#include <map>
#include <iostream>
#include <functional>
#include <unordered_map>

template<>
class std::hash<Tmpl8::vec2>
{
public:
	size_t operator()(const Tmpl8::vec2& key) const
	{
		size_t h1 = std::hash<float>{}(key.x);
		size_t h2 = std::hash<float>{}(key.y);
		return h1 ^ (h2 << 1);
	}
};

namespace Tmpl8
{
	extern Sprite img_collectible;
	extern int collectibles_collected;

	struct Collectible
	{
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

	void loadAllCollectibles();
	void drawCollectibleMap(Camera* camera, Surface* screen, CollectibleMap* collectibles);
	void manageCollectibleCollision(vec2 player_pos, CollectibleMap* collectibles);
	void loadCollectiblesForMap(int map);
	void clearCollectibles();
}
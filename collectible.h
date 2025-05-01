#pragma once
#include "gamesound.h"
#include "surface.h"
#include "tile.h"
#include "tilemap.h"
#include "vec2_hash.h"
#include <unordered_map>

namespace Tmpl8
{
	// External variables
	extern Sprite img_collectible_jump;
	extern int collectibles_collected;
	extern bool collectible_timer_active;
	extern bool collected_new;

	struct Collectible
	{
	public:
		vec2 pos;
		//enum class CollectibleType
		//{
		//	Jump,
		//	Health,
		//	Bullet
		//};
		//
		//CollectibleType type;

		// Default Constructor
		Collectible() :
			pos(vec2{ 0,0 })
		{};

		// Constructor
		Collectible(vec2 _pos) :
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

	// Definition of the CollectibleMap type
	typedef std::unordered_map<vec2, Collectible> CollectibleMap;

	// Local functions
	void loadAllCollectibles(int map);
	void drawCollectibleMap(Camera* camera, Surface* screen, float deltaTime);
	void manageCollectibleCollision(vec2 player_pos, GameSound* gamesound);
	void manageCollectibleRespawn(float deltaTime);
}
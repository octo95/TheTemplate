#pragma once
#include "surface.h"
//#include "tilemap.h"
#include "vec2_hash.h"
#include <unordered_map>

namespace Tmpl8
{
	// External variables
	extern Sprite img_collectible_dash;
	extern bool collectible_timer_active;
	extern bool collected_new;

	class Menu;
	class Health;
	class Player;
	class GameSound;
	class TileMap;
	class Camera;
	
	class Collectible
	{
	public:
		vec2 pos;
		enum class CollectibleType
		{
			Dash,
			Health,
			HealthCollected
		};
		
		CollectibleType type;

		// Default Constructor
		Collectible() :
			pos(vec2{ -50.0f, -50.0f }),
			type(CollectibleType::Dash)
		{};

		// Constructor
		Collectible(vec2 posRef, CollectibleType typeRef) :
			pos(posRef),
			type(typeRef)
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
	void loadAllCollectibles(int map_index);
	void loadDashCollectibles(int map_index, CollectibleMap& cmap);
	void loadHealthCollectibles(int map_index, CollectibleMap& cmap);
	void drawCollectibleMap(Camera* camera, Surface* screen, float deltaTime);
	void manageCollectibleCollision(Player* player, GameSound* gamesound, Menu* menu, Health* health, TileMap* tilemap);
	void manageCollectibleRespawn(float deltaTime, Player* player);
}
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

		// A collectible can either give you a dash or an HP.
		enum class CollectibleType
		{
			Dash,
			Health
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

		// Destructor
		~Collectible() {};
	};

	// Definition of the CollectibleMap type
	typedef std::unordered_map<vec2, Collectible> CollectibleMap;

	// The logic is split between dash and health in order to seperate them. This allows us for example
	// to make it so that if the player doesn't have any dashes left it will make dash collectibles appear again but
	// not the heart ones.

	void loadAllCollectibles(int map_index);
	void loadDashCollectibles(int map_index, CollectibleMap& cmap);
	void loadHealthCollectibles(int map_index, CollectibleMap& cmap);
	void drawCollectibleMap(Camera* camera, Surface* screen, float deltaTime);
	void manageCollectibleCollision(Player* player, GameSound* gamesound, Menu* menu, Health* health, TileMap* tilemap);

	// If the player collected the last collectible and has 0 dashes left, spawn a collectible after 3 seconds
	// to prevent soft lock.
	void manageCollectibleRespawn(float deltaTime, Player* player);
}
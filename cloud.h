#pragma once
#include "surface.h"
#include "template.h"
#include "camera.h"
#include "tilemap.h"
#include <unordered_map>

namespace Tmpl8
{
	extern Sprite img_cloud;

	class Cloud
	{
	public:
		Tmpl8::vec2 pos;
		float speed;

		// Default Constructor
		Cloud() :
			pos(vec2{ 0,0 }),
			speed(0.0f)
		{
		};

		// Constructor
		Cloud(Tmpl8::vec2 _pos, float _speed) :
			pos(_pos),
			speed(_speed)
		{
		};

		// Overloading == operator. Wall are equal if the coordinates are the same.
		bool operator==(const Cloud& rhs) const noexcept
		{
			return this->pos == rhs.pos;
		}

		// Destructor
		~Cloud() {};
	};

	// Definition of the CloudMap type
	typedef std::vector<std::pair<vec2, float>> CloudMap;

	// Local functions
	void loadAllClouds(TileMap* map);
	void drawCloudMap(Camera* camera, Surface* screen, CloudMap* clouds, TileMap* tilemap, float deltaTime);
	std::pair<vec2, float> generateRandomMapSpawn(TileMap* map);
}

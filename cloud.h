#pragma once
#include "surface.h"
#include "template.h"
#include "camera.h"
#include "tilemap.h"
#include <unordered_map>

namespace Tmpl8
{
	extern Sprite img_cloud;
	extern Sprite img_cloud_silly;

	class Cloud
	{
	public:
		// Each cloud is drawn at a random position and speed. It has 1 in 10 chances of being silly with a smile on it.
		Tmpl8::vec2 pos;
		float speed;
		bool is_silly;

		// Default Constructor
		Cloud() :
			pos(vec2{ 0,0 }),
			speed(0.0f),
			is_silly(false)
		{
		};

		// Constructor
		Cloud(Tmpl8::vec2 _pos, float _speed, bool _is_silly) :
			pos(_pos),
			speed(_speed),
			is_silly(_is_silly)
		{
		};

		// Destructor
		~Cloud() {};
	};

	// Definition of the CloudMap type
	typedef std::vector<Cloud> CloudMap;

	// Local all the clouds in the map.
	void loadAllClouds(TileMap* tilemap);

	// Draw every cloud of the map.
	void drawCloudMap(Camera* camera, Surface* screen, CloudMap* clouds, TileMap* tilemap, float deltaTime);

	// Give each cloud random properties.
	Cloud generateRandomMapSpawn(TileMap* map);
}

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

	// Local functions
	void loadAllClouds(TileMap* map);
	void drawCloudMap(Camera* camera, Surface* screen, CloudMap* clouds, TileMap* tilemap, float deltaTime);
	Cloud generateRandomMapSpawn(TileMap* map);
}

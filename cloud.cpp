#include "cloud.h"
#include <cstdlib>
#include <ctime>
#include <random>


namespace Tmpl8
{
	Sprite img_cloud(new Surface("assets/images/map/img_cloud.png"), 1);

	CloudMap cmap;

	void loadAllClouds(TileMap* map)
	{
		// Clear wmap
		cmap = CloudMap();
	
		// Make the number of clouds dependant on the width of the map to be proportional.
		int cloud_amount = map->current_map_data_read->GetWidth() / 200;

		for (int i = 0; i < cloud_amount; i++)
		{
			srand(static_cast<unsigned>(time(0)) + i);
			cmap.emplace_back(generateRandomMapSpawn(map));
		}
	}

	void drawCloudMap(Camera* camera, Surface* screen, CloudMap* clouds, TileMap* tilemap, float deltaTime)
	{
		for (auto& c : cmap)
		{
			// Move cloud.
			c.first.x += deltaTime * c.second;

			// Wrap the cloud around once it reaches the right side of the map.
			if (c.first.x > tilemap->current_map_data_read->GetWidth()) c.first.x = -img_cloud.GetWidth();

			// Draw cloud at updated position
			camera->drawWithCam(&img_cloud, screen, c.first);
		}
	}

	std::pair<vec2, float> generateRandomMapSpawn(TileMap* map)
	{
		vec2 mapSize = vec2(
			map->current_map_data_read->GetWidth(),
			map->current_map_data_read->GetHeight()
		);

		vec2 cloudSize = vec2(
			img_cloud.GetWidth(),
			img_cloud.GetHeight()
		);

		float min_x = -cloudSize.x;
		float max_x = mapSize.x;
		float min_y = -cloudSize.y;
		float max_y = mapSize.y / 3.0f; // Clouds appear on the upper third half of the map
		float min_speed = 5.0f;
		float max_speed = 50.0f;

		// Using RNG based on https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_real_distribution<float> dist_x(min_x, max_x);
		std::uniform_real_distribution<float> dist_y(min_y, max_y);
		std::uniform_real_distribution<float> dist_speed(min_speed, max_speed);

		float random_x = dist_x(gen);
		float random_y = dist_y(gen);
		float speed = dist_speed(gen);

		vec2 spawn_pos = vec2(random_x, random_y);

		return { spawn_pos, speed };
	}
}
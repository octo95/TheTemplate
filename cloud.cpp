#include "cloud.h"
#include <cstdlib>
#include <ctime>
#include <random>


namespace Tmpl8
{
	Sprite img_cloud(new Surface("assets/images/map/img_cloud.png"), 1);
	Sprite img_cloud_silly(new Surface("assets/images/map/img_cloud_silly.png"), 1);

	CloudMap cmap;

	void loadAllClouds(TileMap* map)
	{
		// Clear wmap
		cmap = CloudMap();
	
		// Make the number of clouds dependant on the width of the map to be proportional.
		int cloud_amount = static_cast<int>(map->current_map_data_read->GetWidth() / 200.0f);

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
			c.pos.x += deltaTime * c.speed;

			if (c.pos.x > tilemap->current_map_data_read->GetWidth())
			{
				c.pos.x = -img_cloud.GetWidth();

			}

			if (c.is_silly)
			{
				camera->drawWithCam(&img_cloud_silly, screen, c.pos);
			}
			else
			{
				camera->drawWithCam(&img_cloud, screen, c.pos);
			}
		}

	}

	Cloud generateRandomMapSpawn(TileMap* map)
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
		float max_y = mapSize.y / 3.0f; // Upper third
		float min_speed = 5.0f;
		float max_speed = 50.0f;

		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_real_distribution<float> dist_x(min_x, max_x);
		std::uniform_real_distribution<float> dist_y(min_y, max_y);
		std::uniform_real_distribution<float> dist_speed(min_speed, max_speed);
		std::uniform_int_distribution<int> dist_silly(1, 10); // 1 in 10 chance of being silly

		vec2 spawn_pos = vec2(dist_x(gen), dist_y(gen));
		float speed = dist_speed(gen);
		bool is_silly = (dist_silly(gen) == 1);

		return { spawn_pos, speed, is_silly };
	}

}
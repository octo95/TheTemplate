#include "cloud.h"
#include <cstdlib>
#include <ctime>
#include <random>


namespace Tmpl8
{   
	// Importing the sprites
	Sprite img_cloud(new Surface("assets/images/map/img_cloud.png"), 1);
	Sprite img_cloud_silly(new Surface("assets/images/map/img_cloud_silly.png"), 1);

	// Create a map for the Clouds.
	CloudMap cmap;

	void loadAllClouds(TileMap* map)
	{
		// Clear the CloudMap before loading it.
		cmap = CloudMap();
	
		// Make the number of clouds dependant on the width of the map to be proportional.
		int cloud_amount = static_cast<int>(map->current_map_data_read->GetWidth() / 200.0f);

		// Insert all the clouds in the map.
		for (int i = 0; i < cloud_amount; i++)
		{
			srand(static_cast<unsigned>(time(0)) + i);
			cmap.emplace_back(generateRandomMapSpawn(map));
		}
	}

	void drawCloudMap(Camera* camera, Surface* screen, CloudMap* clouds, TileMap* tilemap, float deltaTime)
	{
		// For every cloud of the map...
		for (auto& c : cmap)
		{
			// Pan the clouds horizontally based on deltaTime and their designated speed.
			c.pos.x += deltaTime * c.speed;

			// If the cloud goes past the screen size, wrap it back to the left.
			if (c.pos.x > tilemap->current_map_data_read->GetWidth())
			{
				c.pos.x = -img_cloud.GetWidth();

			}

			// There is a small chance a cloud can appear with a smilling face which is its 3rd parameter
			// if the cloud is silly, draw the corresponding sprite, if not, draw the normal one.
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
		// Gather the size of the map and cloud.
		vec2 mapSize = map->current_map_data_read->GetSize();
		vec2 cloudSize = img_cloud.GetSize();

		float min_x = -cloudSize.x;		// Left of the screen and min coordinates to have the sprite off screen.
		float max_x = mapSize.x;		// Right of the screen and max coordinates to have the sprite off screen.
		float min_y = -cloudSize.y;		// Top of the screen and max coordiantes to have the sprite off screen.
		float max_y = mapSize.y / 3.0f; // The clouds can appear only on the upper third half of the map.

		float min_speed = 5.0f;			// The speed of the cloud is clamped randomly between 5 and 50.
		float max_speed = 50.0f;		

		// Random number generation to have clouds with different position and speed, based on uniform real distribution:
		// https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_real_distribution<float> dist_x(min_x, max_x);
		std::uniform_real_distribution<float> dist_y(min_y, max_y);
		std::uniform_real_distribution<float> dist_speed(min_speed, max_speed);
		std::uniform_int_distribution<int> dist_silly(1, 10); // 1 in 10 chance of being silly

		// Gather the results of random values to return them.
		vec2 spawn_pos = vec2(dist_x(gen), dist_y(gen));
		float speed = dist_speed(gen);
		bool is_silly = (dist_silly(gen) == 1);

		return { spawn_pos, speed, is_silly };
	}

}
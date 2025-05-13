#include "../include/collectible.h"
#include "../include/menu.h"

namespace Tmpl8
{
	Sprite img_collectible_dash(new Surface("assets/images/UI/img_collectible_dash.png"), 1);
	Sprite img_collectible_health(new Surface("assets/images/UI/img_collectible_health.png"), 1);

	int current_map = 1;
	bool collectible_timer_active = false;
	float collectible_respawn_time = 0.0f;
	bool collected_new = false;

	CollectibleMap cmap;

	void loadDashCollectibles(int map_index, CollectibleMap& cmap) {

		// Make a pointer to the arrays of coordinates and gather their size, depending on the map index to get the correct ones.
		const vec2* dash_ptr = nullptr;
		int dash_size = 0;

		// Getting the size of an array based on: https://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
		switch (map_index)
		{
		case 1:
			dash_ptr = MAP1_COLLEC_DASH;
			dash_size = sizeof(MAP1_COLLEC_DASH) / sizeof(MAP1_COLLEC_DASH[0]);
			break;
		case 2:
			dash_ptr = MAP2_COLLEC_DASH;
			dash_size = sizeof(MAP2_COLLEC_DASH) / sizeof(MAP2_COLLEC_DASH[0]);
			break;
		case 3:
			dash_ptr = MAP3_COLLEC_DASH;
			dash_size = sizeof(MAP3_COLLEC_DASH) / sizeof(MAP3_COLLEC_DASH[0]);
			break;
		case 4:
			dash_ptr = MAP4_COLLEC_DASH;
			dash_size = sizeof(MAP4_COLLEC_DASH) / sizeof(MAP4_COLLEC_DASH[0]);
			break;
		case 5:
			dash_ptr = MAP5_COLLEC_DASH;
			dash_size = sizeof(MAP5_COLLEC_DASH) / sizeof(MAP5_COLLEC_DASH[0]);
			break;
		}

		// Once done gathering the correct arrays with dash_ptr, insert them in the map for the amount that there 
		// is in the array thanks to their size we gathered with dash_size.
		for (int i = 0; i < dash_size; i++)
		{
			cmap.insert({ dash_ptr[i], Collectible(dash_ptr[i], Collectible::CollectibleType::Dash) });
		}
	}

	void loadHealthCollectibles(int map_index, CollectibleMap& cmap) {

		// Follows the same logic as loadDashCollectibles, we seperate them to not load them at the same time,
		// allowing us for seperated ways of working with them.
		const vec2* health_ptr = nullptr;
		int health_size = 0;
		
		switch (map_index)
		{
		case 1:
			health_ptr = MAP1_COLLEC_HEALTH;
			health_size = sizeof(MAP1_COLLEC_HEALTH) / sizeof(MAP1_COLLEC_HEALTH[0]);
			break;
		case 2:
			health_ptr = MAP2_COLLEC_HEALTH;
			health_size = sizeof(MAP2_COLLEC_HEALTH) / sizeof(MAP2_COLLEC_HEALTH[0]);
			break;
		case 3:
			health_ptr = MAP3_COLLEC_HEALTH;
			health_size = sizeof(MAP3_COLLEC_HEALTH) / sizeof(MAP3_COLLEC_HEALTH[0]);
			break;
		case 4:
			health_ptr = MAP4_COLLEC_HEALTH;
			health_size = sizeof(MAP4_COLLEC_HEALTH) / sizeof(MAP4_COLLEC_HEALTH[0]);
			break;
		case 5:
			health_ptr = MAP5_COLLEC_HEALTH;
			health_size = sizeof(MAP5_COLLEC_HEALTH) / sizeof(MAP5_COLLEC_HEALTH[0]);
			break;
		}

		for (int i = 0; i < health_size; i++)
			cmap.insert({ health_ptr[i], Collectible(health_ptr[i], Collectible::CollectibleType::Health) });
	}

	// Load all the collectibles (dashes and hearts)
	void loadAllCollectibles(int map_index) {
		current_map = map_index;					// Gather the map_index for other functions	
		cmap = CollectibleMap();					// Create the map
		loadDashCollectibles(map_index, cmap);		// Load dashes
		loadHealthCollectibles(map_index, cmap);	// Load hearts
	}

	void drawCollectibleMap(Camera* camera, Surface* screen, float deltaTime)
	{
		static float totalTime = 0.0f;
		float floating_time = 2.0f; 
		float amplitude = 5.0f;    

		totalTime += deltaTime;

		for (auto& c : cmap)
		{
			// The coordinates of the collectibles are given in tile coordinates, to adjust them back in screen
			// coordinates we multiply by TILE_SIZE and put them in the middle with a TILE_SIZE / 2 offset.
			vec2 draw_pos = vec2(
				c.first.x * TILE_SIZE + TILE_SIZE / 2.0f,
				c.first.y * TILE_SIZE + TILE_SIZE / 2.0f
			);

			// Offset to make the collectibles float, adding an offset of 4 to put it a bit higher to the ground.
			draw_pos.y += sin((totalTime / floating_time) * 2.0f * 3.1416f) * amplitude - 4.0f;

			// Assign the sprite drawn according to its collectible type.
			if (c.second.type == Collectible::CollectibleType::Dash)
			{
				camera->drawWithCam(&img_collectible_dash, screen, draw_pos);
			}
			else if (c.second.type == Collectible::CollectibleType::Health)
			{
				camera->drawWithCam(&img_collectible_health, screen, draw_pos);
			}
		}
	}

	void manageCollectibleCollision(Player* player, GameSound* gamesound, Menu* menu, Health* health, TileMap* tilemap)
	{
		// Create an iterator
		CollectibleMap::iterator c = cmap.begin();

		// Iterate through the elements of the map
		while (c != cmap.end())
		{
			float col_x = c->first.x * TILE_SIZE + TILE_SIZE / 2.0f;
			float col_y = c->first.y * TILE_SIZE + TILE_SIZE / 2.0f;
			float col_width = TILE_SIZE;
			float col_height = TILE_SIZE;

			// AABB collision check
			bool overlap =
										player->position.x < col_x + col_width &&
				player->position.x + player->hitbox_radius > col_x &&
										player->position.y < col_y + col_height &&
				player->position.y + player->hitbox_radius > col_y;

			// AABB collision check for secret entrance of level 5 with a tolerance in Y axis of 1 TILE_SIZE.
			float secret_col_x = 30.0f * TILE_SIZE;
			float secret_col_y = 23.0F * TILE_SIZE;
			float secret_height = TILE_SIZE * 3.0f;
			float secret_width = TILE_SIZE;

			bool overlap_secret =
										player->position.x < secret_col_x + secret_width &&
				player->position.x + player->hitbox_radius > secret_col_x &&
										player->position.y < secret_col_y + secret_height &&
				player->position.y + player->hitbox_radius > secret_col_y;

			if (overlap_secret && tilemap->getCurrentLevel() == 5) 
			{
				tilemap->secret_collected = true;
			}

			// If the player touches the collectible, erase it from the map and play its logic.
			if (overlap)
			{
				Collectible::CollectibleType type = c->second.type;

				c = cmap.erase(c);
				gamesound->playSound(gamesound->snd_collect);

				// * If the collectible is a dash, give the player an additional dash, 10 score, set collected_new 
				//   to true so that a new timer can start if the player runs out of dashes (to not get soft locked).

				// * If the collectible is a heart, give the player an additional HP and 50 score.
				switch (type)
				{
				case Collectible::CollectibleType::Dash:
					player->dash_count++;
					collected_new = true;
					menu->addScore(10);
					break;
				case Collectible::CollectibleType::Health:
					health->player_hp++;
					menu->addScore(50);
					break;
				}
			}
			// If no collision is detected, continue going through the map
			else 
			{
				++c;
			}
		}
	}

	void manageCollectibleRespawn(float deltaTime, Player* player)
	{
		// Start the timer if the player runs out of dashes and don't have any others 
		// to collect nearby to avoid getting soft locked.

		if (player->dash_count < 1 && collected_new)
		{
			collectible_respawn_time = 3.0f;
			collectible_timer_active = true;
			collected_new = false;
		}

		// Run through the timer
		if (collectible_timer_active)
		{
			collectible_respawn_time -= deltaTime;

			// End of timer, make the collectibles respawn
			if (collectible_respawn_time <= 0.0f)
			{
				collectible_timer_active = false;
				loadDashCollectibles(current_map, cmap);
			}
		}
	}


}
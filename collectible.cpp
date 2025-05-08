#include "collectible.h"
#include "menu.h"

namespace Tmpl8
{
	Sprite img_collectible_dash(new Surface("assets/images/UI/img_collectible_dash.png"), 1);
	Sprite img_collectible_health(new Surface("assets/images/UI/img_collectible_health.png"), 1);
	Sprite img_collectible_health_collected(new Surface("assets/images/UI/img_collectible_health_collected.png"), 1);

	int collectibles_collected = 0;
	int current_map = 1;
	bool collectible_timer_active = false;
	float collectible_respawn_time = 0.0f;
	bool collected_new = false;

	CollectibleMap cmap;

	void loadAllCollectibles(int map_index)
	{
		current_map = map_index;
		cmap = CollectibleMap();

		const vec2* jump_ptr = nullptr;
		const vec2* health_ptr = nullptr;
		int jump_size = 0;
		int health_size = 0;

		switch (map_index)
		{
		case 1:
			jump_ptr = MAP1_COLLEC_DASH;
			jump_size = sizeof(MAP1_COLLEC_DASH) / sizeof(MAP1_COLLEC_DASH[0]);
			health_ptr = MAP1_COLLEC_HEALTH;
			health_size = sizeof(MAP1_COLLEC_HEALTH) / sizeof(MAP1_COLLEC_HEALTH[0]);
			break;
		case 2:
			jump_ptr = MAP2_COLLEC_DASH;
			jump_size = sizeof(MAP2_COLLEC_DASH) / sizeof(MAP2_COLLEC_DASH[0]);
			health_ptr = MAP2_COLLEC_HEALTH;
			health_size = sizeof(MAP2_COLLEC_HEALTH) / sizeof(MAP2_COLLEC_HEALTH[0]);
			break;
		case 3:
			jump_ptr = MAP3_COLLEC_DASH;
			jump_size = sizeof(MAP3_COLLEC_DASH) / sizeof(MAP3_COLLEC_DASH[0]);
			health_ptr = MAP3_COLLEC_HEALTH;
			health_size = sizeof(MAP3_COLLEC_HEALTH) / sizeof(MAP3_COLLEC_HEALTH[0]);
			break;
		case 4:
			jump_ptr = MAP4_COLLEC_DASH;
			jump_size = sizeof(MAP4_COLLEC_DASH) / sizeof(MAP4_COLLEC_DASH[0]);
			health_ptr = MAP4_COLLEC_HEALTH;
			health_size = sizeof(MAP4_COLLEC_HEALTH) / sizeof(MAP4_COLLEC_HEALTH[0]);
			break;
		case 5:
			jump_ptr = MAP5_COLLEC_DASH;
			jump_size = sizeof(MAP5_COLLEC_DASH) / sizeof(MAP5_COLLEC_DASH[0]);
			health_ptr = MAP5_COLLEC_HEALTH;
			health_size = sizeof(MAP5_COLLEC_HEALTH) / sizeof(MAP5_COLLEC_HEALTH[0]);
			break;
		}

		// Insert Jump collectibles
		for (int i = 0; i < jump_size; i++)
			cmap.insert({ jump_ptr[i], Collectible(jump_ptr[i], Collectible::CollectibleType::Dash) });

		// Insert Health collectibles
		for (int i = 0; i < health_size; i++)
			cmap.insert({ health_ptr[i], Collectible(health_ptr[i], Collectible::CollectibleType::Health) });
	}


	void drawCollectibleMap(Camera* camera, Surface* screen, float deltaTime)
	{
		static float totalTime = 0.0f;
		float floating_time = 2.0f; 
		float amplitude = 5.0f;    

		totalTime += deltaTime;

		for (auto& c : cmap)
		{
			vec2 draw_pos = vec2(
				c.first.x * TILE_SIZE + TILE_SIZE / 2.0f,
				c.first.y * TILE_SIZE + TILE_SIZE / 2.0f
			);

			// Offset to make the collectibles float, adding an offset of 4 to put it a bit higher to the ground
			draw_pos.y += sin((totalTime / floating_time) * 2.0f * 3.1416f) * amplitude - 4.0f;

			camera->drawWithCam(&img_collectible_dash, screen, draw_pos);

			Collectible::CollectibleType type = c.second.type;

			if (type == Collectible::CollectibleType::Dash)
			{
				camera->drawWithCam(&img_collectible_dash, screen, draw_pos);
			}
			else if (type == Collectible::CollectibleType::Health)
			{
				camera->drawWithCam(&img_collectible_health, screen, draw_pos);
			}
			else if (type == Collectible::CollectibleType::HealthCollected)	// UNUSED
			{
				camera->drawWithCam(&img_collectible_health_collected, screen, draw_pos);
			}
		}
	}

	void manageCollectibleCollision(Player* player, GameSound* gamesound, Menu* menu, Health* health)
	{
		float player_x = player->position.x;
		float player_y = player->position.y;
		float player_hitbox = hitbox_radius;

		CollectibleMap::iterator c = cmap.begin();

		while (c != cmap.end())
		{
			float col_x = c->first.x * TILE_SIZE;
			float col_y = c->first.y * TILE_SIZE;
			float col_width = TILE_SIZE;
			float col_height = TILE_SIZE;

			// AABB collision check
			bool overlap =
								player_x < col_x + col_width &&
				player_x + player_hitbox > col_x &&
								player_y < col_y + col_height &&
				player_y + player_hitbox > col_y;

			// The player touches the collectible, erase it from the map and play its logic
			
			if (overlap)
			{
				Collectible::CollectibleType type = c->second.type;

				c = cmap.erase(c);
				gamesound->playSound(gamesound->snd_collect);

				switch (type)
				{
				case Collectible::CollectibleType::Dash:
					player->dash_count++;
					collectibles_collected = player->dash_count;
					collected_new = true;
					menu->addScore(10);
					break;
				case Collectible::CollectibleType::Health:
					health->player_hp++;
					menu->addScore(50);
					break;
				}
			}
			// Otherwise continue going through the map
			else 
			{
				++c;
			}
		}
	}

	void manageCollectibleRespawn(float deltaTime, Player* player)
	{
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
				loadAllCollectibles(current_map);
			}
		}
	}


}
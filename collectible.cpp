#include "collectible.h"
#include "menu.h"

namespace Tmpl8
{
	Sprite img_collectible_jump(new Surface("assets/images/map/img_collectible_jump.png"), 1);
	int collectibles_collected = 0;
	int current_map = 1;
	bool collectible_timer_active = false;
	float collectible_respawn_time = 0.0f;
	bool collected_new = false;

	CollectibleMap cmap;

	void loadAllCollectibles(int map_index)
	{
		// Clear cmap
		current_map = map_index;
		cmap = CollectibleMap();

		// Select correct map
		const vec2* ptr;
		int size = 0;

		switch (map_index) {
		case 1:
			ptr = MAP1_COLLECTIBLES;
			size = sizeof(MAP1_COLLECTIBLES) / sizeof(MAP1_COLLECTIBLES[0]);
			break;
		case 2:
			ptr = MAP2_COLLECTIBLES;
			size = sizeof(MAP2_COLLECTIBLES) / sizeof(MAP2_COLLECTIBLES[0]);
			break;
		case 3:
			ptr = MAP3_COLLECTIBLES;
			size = sizeof(MAP3_COLLECTIBLES) / sizeof(MAP3_COLLECTIBLES[0]);
			break;
		case 4:
			ptr = MAP4_COLLECTIBLES;
			size = sizeof(MAP4_COLLECTIBLES) / sizeof(MAP4_COLLECTIBLES[0]);
			break;
		case 5:
			ptr = MAP5_COLLECTIBLES;
			size = sizeof(MAP5_COLLECTIBLES) / sizeof(MAP5_COLLECTIBLES[0]);
			break;
		}

		// Insert collectible in newly initialized map
		for (int i = 0; i < size; i++) {
			cmap.insert({ ptr[i], Collectible(ptr[i])});
		}
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
			camera->drawWithCam(&img_collectible_jump, screen, draw_pos);
		}
	}

	void manageCollectibleCollision(Player* player, GameSound* gamesound, Menu* menu)
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

			if (overlap)
			{
				c = cmap.erase(c);
				gamesound->playSound(gamesound->snd_collect);
				player->dash_count++;
				collectibles_collected = player->dash_count;
				collected_new = true;
				menu->addScore(10);
				printf("dash: %d, collectibles: %d\n", player->dash_count, collectibles_collected);
			}
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
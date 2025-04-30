#include "collectible.h"

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

	void drawCollectibleMap(Camera* camera,Surface* screen)
	{
		for (auto& c : cmap)
		{
			vec2 draw_pos = vec2(
				c.first.x * TILE_SIZE + TILE_SIZE / 2.0f, 
				c.first.y * TILE_SIZE + TILE_SIZE / 2.0f
			);
			camera->drawWithCam(&img_collectible_jump, screen, draw_pos);
		}
	}

	void manageCollectibleCollision(vec2 player_pos, GameSound* gamesound)
	{
		int x = (int)player_pos.x / TILE_SIZE;
		int y = (int)player_pos.y / TILE_SIZE;
		CollectibleMap::iterator c = cmap.begin();
		for (; c != cmap.end();)
		{
			int cx = (int)(c->first.x);
			int cy = (int)(c->first.y);
			if (cx == x && cy == y) {
				c = cmap.erase(c);
				gamesound->playSound(gamesound->snd_collect);
				collectibles_collected++;
				collected_new = true;
			}
			else 
			{
				++c;
			}
		}
	}
	void manageCollectibleRespawn(float deltaTime)
	{
		if (collectibles_collected < 1 && collected_new)
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
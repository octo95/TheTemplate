#include "collectible.h"
#include "tilemap.h"
#include "tile.h"
#include <unordered_map>
#include <iostream>
#include <functional>


// Implement std::hash for Tmpl8::vec2


namespace Tmpl8
{
	Sprite img_collectible(new Surface("assets/collectible.png"), 1);

	CollectibleMap initializeCollectibleMap(int map)
	{
		CollectibleMap collectibles;
		
		size_t map1_size = sizeof(MAP1_COLLECTIBLES) / sizeof(MAP1_COLLECTIBLES[0]);
		size_t map2_size = sizeof(MAP2_COLLECTIBLES) / sizeof(MAP2_COLLECTIBLES[0]);
		size_t map3_size = sizeof(MAP3_COLLECTIBLES) / sizeof(MAP3_COLLECTIBLES[0]);

		switch (map) {
		case 1:
			for (int i = 0; i < map1_size; i++) {
				collectibles.insert({ MAP1_COLLECTIBLES[i], Collectible(MAP1_COLLECTIBLES[i]) });
			}
			break;
		case 2:
			for (int i = 0; i < map2_size; i++) {
				collectibles.insert({ MAP2_COLLECTIBLES[i], Collectible(MAP2_COLLECTIBLES[i]) });
			}
			break;
		case 3:
			for (int i = 0; i < map3_size; i++) {
				collectibles.insert({ MAP3_COLLECTIBLES[i], Collectible(MAP3_COLLECTIBLES[i]) });
			}
			break;
		}

		return collectibles;
	}

	void drawCollectibleMap(Camera* camera,Surface* screen, CollectibleMap* collectibles)
	{
		for (auto& c : *collectibles)
		{
			float x = c.first.x * TILE_SIZE + TILE_SIZE / 2.0f;
			float y = c.first.y * TILE_SIZE + TILE_SIZE / 2.0f;
			camera->drawWithCam(&img_collectible, screen, x, y);
		}
	}

	void manageCollectibleCollision(vec2 player_pos, CollectibleMap* collectibles) {
		int x = player_pos.x / TILE_SIZE;
		int y = player_pos.y / TILE_SIZE;

		CollectibleMap::iterator c = collectibles->begin();
		for (; c != collectibles->end();)
		{
			int cx = static_cast<int>(c->first.x);
			int cy = static_cast<int>(c->first.y);
			if (cx == x && cy == y) {
				c = collectibles->erase(c);
				// GLOBAL_COUNTER_STRIKE_COUNTER += 1; (extern)
			}
			else {
				++c;
			}
		}
	}
}
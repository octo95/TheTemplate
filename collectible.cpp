#include "collectible.h"
#include "tilemap.h"
#include "tile.h"
#include <unordered_map>
#include <iostream>
#include <functional>
#include "gamesound.h"

namespace Tmpl8
{
	Sprite img_collectible(new Surface("assets/images/map/img_collectible.png"), 1);
	int collectibles_collected = 0;

	CollectibleMap cmap_current;
	CollectibleMap cmap_1;
	CollectibleMap cmap_2;
	CollectibleMap cmap_3;

	void loadAllCollectibles()
	{
		size_t map1_size = sizeof(MAP1_COLLECTIBLES) / sizeof(MAP1_COLLECTIBLES[0]);
		size_t map2_size = sizeof(MAP2_COLLECTIBLES) / sizeof(MAP2_COLLECTIBLES[0]);
		size_t map3_size = sizeof(MAP3_COLLECTIBLES) / sizeof(MAP3_COLLECTIBLES[0]);

		for (int i = 0; i < map1_size; i++) {
			cmap_1.insert({ MAP1_COLLECTIBLES[i], Collectible(MAP1_COLLECTIBLES[i]) });
		}

		for (int i = 0; i < map2_size; i++) {
			cmap_2.insert({ MAP2_COLLECTIBLES[i], Collectible(MAP2_COLLECTIBLES[i]) });
		}

		for (int i = 0; i < map3_size; i++) {
			cmap_3.insert({ MAP3_COLLECTIBLES[i], Collectible(MAP3_COLLECTIBLES[i]) });
		}
	}

	void loadCollectiblesForMap(int map)
	{
		clearCollectibles();

		if (map == 1)
			cmap_current = cmap_1;
		else if (map == 2)
			cmap_current = cmap_2;
		else if (map == 3)
			cmap_current = cmap_3;
	}

	void clearCollectibles()
	{
		cmap_current.clear();
		collectibles_collected = 0;
	}

	void drawCollectibleMap(Camera* camera,Surface* screen, CollectibleMap* collectibles)
	{
		for (auto& c : cmap_current)
		{
			float x = c.first.x * TILE_SIZE + TILE_SIZE / 2.0f;
			float y = c.first.y * TILE_SIZE + TILE_SIZE / 2.0f;
			camera->drawWithCam(&img_collectible, screen, x, y);
		}
	}

	// Need to REDO
	void manageCollectibleCollision(vec2 player_pos, CollectibleMap* collectibles, GameSound* gamesound) {
		int x = player_pos.x / TILE_SIZE;
		int y = player_pos.y / TILE_SIZE;
	
		CollectibleMap::iterator c = cmap_current.begin();
		for (; c != cmap_current.end();)
		{
			int cx = static_cast<int>(c->first.x);
			int cy = static_cast<int>(c->first.y);
			if (cx == x && cy == y) {
				c = cmap_current.erase(c);
				gamesound->playSound(gamesound->snd_collect);
				collectibles_collected++;
			}
			else {
				++c;
			}
		}
	}
}
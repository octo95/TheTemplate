#include "collectible.h"
#include "tilemap.h"
#include "tile.h"
#include <unordered_map>
#include <iostream>
#include <functional>
#include "gamesound.h"

#define CASE_MAP(i, map) case i: \
ptr = map; \
size = sizeof(map) / sizeof(map[0]); \
break;

namespace Tmpl8
{
	Sprite img_collectible(new Surface("assets/images/map/img_collectible.png"), 1);
	int collectibles_collected = 0;

	CollectibleMap cmap;

	void loadAllCollectibles(int map)
	{
		// Clear cmap
		cmap = CollectibleMap();

		// Select correct map
		const vec2* ptr;
		int size = 0;

		switch (map) {
		CASE_MAP(1, MAP1_COLLECTIBLES)
		CASE_MAP(2, MAP2_COLLECTIBLES)
		CASE_MAP(3, MAP3_COLLECTIBLES)
		CASE_MAP(4, MAP4_COLLECTIBLES)
		CASE_MAP(5, MAP5_COLLECTIBLES)

		//case 1:
		//	ptr = MAP1_COLLECTIBLES;
		//	size = sizeof(MAP1_COLLECTIBLES) / sizeof(MAP1_COLLECTIBLES[0]);
		//	break;
		//case 2:
		//	ptr = MAP2_COLLECTIBLES;
		//	size = sizeof(MAP2_COLLECTIBLES) / sizeof(MAP2_COLLECTIBLES[0]);
		//	break;
		//case 3:
		//	ptr = MAP3_COLLECTIBLES;
		//	size = sizeof(MAP3_COLLECTIBLES) / sizeof(MAP3_COLLECTIBLES[0]);
		//	break;
		//case 4:
		//	ptr = MAP4_COLLECTIBLES;
		//	size = sizeof(MAP4_COLLECTIBLES) / sizeof(MAP4_COLLECTIBLES[0]);
		//	break;
		//case 5:
		//	ptr = MAP5_COLLECTIBLES;
		//	size = sizeof(MAP5_COLLECTIBLES) / sizeof(MAP5_COLLECTIBLES[0]);
		//	break;
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
			float x = c.first.x * TILE_SIZE + TILE_SIZE / 2.0f;
			float y = c.first.y * TILE_SIZE + TILE_SIZE / 2.0f;
			camera->drawWithCam(&img_collectible, screen, x, y);
		}
	}

	// Need to REDO
	void manageCollectibleCollision(vec2 player_pos, GameSound* gamesound) {
		int x = (int)player_pos.x / TILE_SIZE;
		int y = (int)player_pos.y / TILE_SIZE + 1;
		CollectibleMap::iterator c = cmap.begin();
		for (; c != cmap.end();)
		{
			int cx = static_cast<int>(c->first.x);
			int cy = static_cast<int>(c->first.y);
			if (cx == x && cy == y) {
				c = cmap.erase(c);
				gamesound->playSound(gamesound->snd_collect);
				collectibles_collected++;
			}
			else {
				++c;
			}
		}
	}
}
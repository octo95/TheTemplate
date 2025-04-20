#include "wall.h"
#include "tilemap.h"
#include "tile.h"
#include <unordered_map>
#include <iostream>
#include <functional>

namespace Tmpl8
{
	Sprite img_wall(new Surface("assets/wall.png"), 1);
	int walls_collected = 0;

	WallMap wmap_current;
	WallMap wmap_1;
	WallMap wmap_2;
	WallMap wmap_3;

	void loadAllWalls()
	{
		size_t map1_size = sizeof(MAP1_WALLS) / sizeof(MAP1_WALLS[0]);
		size_t map2_size = sizeof(MAP2_WALLS) / sizeof(MAP2_WALLS[0]);
		size_t map3_size = sizeof(MAP3_WALLS) / sizeof(MAP3_WALLS[0]);

		for (int i = 0; i < map1_size; i++) {
			wmap_1.insert({ MAP1_WALLS[i], Wall(MAP1_WALLS[i]) });
		}

		for (int i = 0; i < map2_size; i++) {
			wmap_2.insert({ MAP2_WALLS[i], Wall(MAP2_WALLS[i]) });
		}

		for (int i = 0; i < map3_size; i++) {
			wmap_3.insert({ MAP3_WALLS[i], Wall(MAP3_WALLS[i]) });
		}
	}

	void loadWallsForMap(int map)
	{
		clearWalls();

		if (map == 1)
			wmap_current = wmap_1;
		else if (map == 2)
			wmap_current = wmap_2;
		else if (map == 3)
			wmap_current = wmap_3;
	}

	void clearWalls()
	{
		wmap_current.clear();
		walls_collected = 0;
	}

	void drawWallMap(Camera* camera, Surface* screen, WallMap* walls)
	{
		for (auto& c : wmap_current)
		{
			float x = c.first.x * TILE_SIZE + TILE_SIZE / 2.0f;
			float y = c.first.y * TILE_SIZE;
			camera->drawWithCam(&img_wall, screen, x, y);
		}
	}

	void manageWallCollision(vec2 player_pos, WallMap* walls) {
		int x = player_pos.x / TILE_SIZE;
		int y = player_pos.y / TILE_SIZE;

		WallMap::iterator c = wmap_current.begin();
		for (; c != wmap_current.end();)
		{
			int cx = static_cast<int>(c->first.x);
			int cy = static_cast<int>(c->first.y);
			if (cx == x && cy == y) {
				c = wmap_current.erase(c);
				walls_collected++;
			}
			else {
				++c;
			}
		}
	}
}
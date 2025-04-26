#include "wall.h"
#include "tilemap.h"
#include "tile.h"
#include <unordered_map>
#include <iostream>
#include <functional>

namespace Tmpl8
{
	Sprite img_wall(new Surface("assets/images/map/img_wall.png"), 1);
	int walls_collected = 0;

	WallMap wmap;

	void loadAllWalls(int map)
	{
		// Clear wmap
		wmap = WallMap();

		// Select correct map
		const vec2* ptr;
		int size = 0;

		switch (map) {
		case 1:
			ptr = MAP1_WALLS;
			size = sizeof(MAP1_WALLS) / sizeof(MAP1_WALLS[0]);
			break;
		case 2:
			ptr = MAP2_WALLS;
			size = sizeof(MAP2_WALLS) / sizeof(MAP2_WALLS[0]);
			break;
		case 3:
			ptr = MAP3_WALLS;
			size = sizeof(MAP3_WALLS) / sizeof(MAP3_WALLS[0]);
			break;
		case 4:
			ptr = MAP4_WALLS;
			size = sizeof(MAP4_WALLS) / sizeof(MAP4_WALLS[0]);
			break;
		case 5:
			ptr = MAP5_WALLS;
			size = sizeof(MAP5_WALLS) / sizeof(MAP5_WALLS[0]);
			break;
		}

		// Insert walls into wmap
		for (int i = 0; i < size; i++) {
			wmap.insert({ ptr[i], Wall(ptr[i]) });
		}
	}


	void drawWallMap(Camera* camera, Surface* screen, WallMap* walls)
	{
		for (auto& c : wmap)
		{
			float x = c.first.x * TILE_SIZE + TILE_SIZE / 2.0f;
			float y = c.first.y * TILE_SIZE;
			camera->drawWithCam(&img_wall, screen, x, y);
		}
	}

	void manageWallCollision(vec2 player_pos, GameSound* gamesound) {
		int x = (int)player_pos.x / TILE_SIZE;
		int y = (int)player_pos.y / TILE_SIZE;

		WallMap::iterator c = wmap.begin();
		for (; c != wmap.end();)
		{
			int cx = static_cast<int>(c->first.x);
			int cy = static_cast<int>(c->first.y);
			if (cx == x && cy == y) {
				c = wmap.erase(c);
				gamesound->playSound(gamesound->snd_break_wall);
				walls_collected++;
			}
			else {
				++c;
			}
		}
	}
}
#include "wall.h"

namespace Tmpl8
{
	Sprite img_wall(new Surface("assets/images/map/img_wall.png"), 1);
	int walls_count = 0;

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
			vec2 draw_pos = vec2(
				c.first.x * TILE_SIZE + TILE_SIZE / 2.0f,
				c.first.y * TILE_SIZE
			);
			camera->drawWithCam(&img_wall, screen, draw_pos);
		}
	}

	void manageWallCollision(Player* player, GameSound* gamesound)
	{
		float player_x = player->position.x;
		float player_y = player->position.y;

		float player_hitbox = hitbox_radius;

		WallMap::iterator c = wmap.begin();
		while (c != wmap.end())
		{
			float wall_x = c->first.x * TILE_SIZE;
			float wall_y = c->first.y * TILE_SIZE;
			float wall_width = TILE_SIZE;
			float wall_height = TILE_SIZE;

			// AABB collision check
			bool overlap =
								player_x < wall_x + wall_width &&
				player_x + player_hitbox > wall_x &&
								player_y < wall_y + wall_height  &&
				player_y + player_hitbox > wall_y ;

			if (overlap)
			{
				player->move_cooldown = 0.30f;						// Stop the player's input for 0.3 seconds
				player->velocity.x = -player->velocity.x * 2.0f;	// Make the player bounce back in the opposite direction
				player->velocity.y = player->velocity.x / 2.0f;		// Make the player bounce back up based on its horizontal speed

				gamesound->playSound(gamesound->snd_break_wall);

				c = wmap.erase(c);
			}
			else
			{
				++c;
			}
		}
	}

}
#include "wall.h"

namespace Tmpl8
{
	// Importing the sprites.
	Sprite img_wall(new Surface("assets/images/map/img_wall.png"), 1);

	WallMap wmap;

	void loadAllWalls(int map)
	{
		// Clear wmap
		wmap = WallMap();

		// Select correct map
		const vec2* ptr;
		int size = 0;

		// Following the same logic as collectibles.cpp
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
		WallMap::iterator wallIt = wmap.begin();
		WallMap::iterator wallColumnIt = wmap.begin();

		while (wallIt != wmap.end())
		{
			float wall_x = wallIt->first.x * TILE_SIZE + TILE_SIZE / 2.0f;
			float wall_y = wallIt->first.y * TILE_SIZE;
			float wall_width = img_wall.GetWidth();
			float wall_height = img_wall.GetHeight();

			// AABB collision check
			bool overlap =
										player->position.x < wall_x + wall_width &&
				player->position.x + player->hitbox_radius > wall_x &&
										player->position.y < wall_y + wall_height  &&
				player->position.y + player->hitbox_radius > wall_y ;

			if (overlap)
			{
				// Bounce the player
				player->move_cooldown = 0.30f;						// Stop the player's input for 0.3 seconds
				player->velocity.x = -player->velocity.x * 1.5f;	// Make the player bounce back in the opposite direction
				player->velocity.y = player->velocity.x * 1.3f;		// Make the player bounce back up based on its horizontal speed
				gamesound->playSound(gamesound->snd_break_wall);

				// Remove all the walls that are on the same column to make bigger walls
				float hitX = wallIt->first.x; 

				while (wallColumnIt != wmap.end()) // Check through the map a second time to detect walls within the same column
				{
					if (wallColumnIt->first.x == hitX)	// Compare with the wall hit kept in the previous iterator
					{
						wallColumnIt = wmap.erase(wallColumnIt);
					}
					else
					{
						++wallColumnIt;
					}
				}
				break;
			}
			else
			{
				++wallIt;
			}
		}
	}

}
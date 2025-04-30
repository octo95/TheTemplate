#include "bell.h"

namespace Tmpl8
{
	Bell::Bell(){}

	Sprite img_bell(new Surface("assets/images/map/img_bell.png"), 1);
	const int BELL_HEIGHT = img_bell.GetHeight();
	const int BELL_WIDTH = img_bell.GetWidth();

    void Bell::isBellTouchingPlayer(Player* player)
    {
        // Define player bounding box
        float player_x = player->position.x;
        float player_y = player->position.y;
        float player_hitbox = hitbox_radius;  

        // Define bell bounding box
        float bell_x = bell_current_pos.x;
        float bell_y = bell_current_pos.y - BELL_HEIGHT; 
        float bell_width = BELL_WIDTH;
        float bell_height = BELL_HEIGHT;

        float reduce_hitbox = 10.0f;

        // AABB collision check
        bool overlap =
                            player_x < reduce_hitbox + bell_x + bell_width &&
            player_x + player_hitbox > reduce_hitbox + bell_x &&
                            player_y < reduce_hitbox + bell_y + bell_height &&
            player_y + player_hitbox > bell_y;

        touchedPlayer = overlap;
    }

	void Bell::drawBell(Surface* screen, Camera* camera, int map_index)
	{
		vec2 current_pos = { BELL_POS[map_index - 1] * TILE_SIZE };
		bell_current_pos = current_pos;

		vec2 draw_pos = { current_pos.x, current_pos.y - 0.9f * BELL_HEIGHT };
        camera->drawWithCam(&img_bell, screen, draw_pos);
	}
}


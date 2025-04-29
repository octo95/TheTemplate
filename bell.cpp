#include "bell.h"

namespace Tmpl8
{
	Bell::Bell(){}

	Sprite img_bell(new Surface("assets/images/map/img_bell.png"), 1);
	const int BELL_HEIGHT = img_bell.GetHeight();
	const int BELL_WIDTH = img_bell.GetWidth();

    void Bell::isBellTouchingPlayer(Player* player)
    {
        // Player position in tiles
        int player_tpos_x = player->position.x / TILE_SIZE;
        int player_tpos_y = player->position.y / TILE_SIZE;

        // Bell position in tiles
        int bell_tpos_x = bell_current_pos.x / TILE_SIZE;
        int bell_tpos_y = (bell_current_pos.y - BELL_HEIGHT) / TILE_SIZE ;

        // Check collision
        if (player_tpos_x >= bell_tpos_x && player_tpos_x <= bell_tpos_x + 1 &&
            player_tpos_y >= bell_tpos_y && player_tpos_y <= bell_tpos_y + 1)
        {
            touchedPlayer = true;
        }
        else
        {
            touchedPlayer = false;
        }
    }

	void Bell::drawBell(Surface* screen, Camera* camera, int map_index)
	{
		vec2 current_pos = { BELL_POS[map_index - 1] * TILE_SIZE };
		bell_current_pos = current_pos;

		vec2 draw_pos = { current_pos.x, current_pos.y - 0.9f * BELL_HEIGHT };
        camera->drawWithCam(&img_bell, screen, draw_pos);
	}
}


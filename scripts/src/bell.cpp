#include "../include/bell.h"

namespace Tmpl8
{
	Bell::Bell(Level& levelRef):
        level(levelRef)
    {}

    // Importing the sprites
	Sprite img_bell(new Surface("assets/images/map/img_bell.png"), 1);
    Sprite img_bell_animated(new Surface("assets/images/map/img_bell_animated.tga"), 5);

    void Bell::isBellTouchingPlayer(Player* player, GameSound* gamesound)
    {
        // Define the bell's hitbox
        float reduce_hitbox = 10.0f; // Shrink the bell's hitbox
        float bell_x = bell_current_pos.x + reduce_hitbox;
        float bell_y = bell_current_pos.y - BELL_SIZE.y + reduce_hitbox;
        float bell_width = BELL_SIZE.x - 2 * reduce_hitbox;
        float bell_height = BELL_SIZE.y - 2 * reduce_hitbox;

        // AABB collision check with the player
        player_touch_bell =
                                    player->position.x < bell_x + bell_width &&
            player->position.x + player->hitbox_radius > bell_x &&
                                    player->position.y < bell_y + bell_height &&
            player->position.y + player->hitbox_radius > bell_y;

        // If the player touches the bell, play SFX and go to the next level
        if (player_touch_bell)
        {
            gamesound->playSound(gamesound->snd_bell);
            level.nextLevel();
        }
    }

	void Bell::drawBell(Surface* screen, Camera* camera, int map_index, float deltaTime)
	{
        // The bell's position is stored in an array depending on the map_index, we gather it 
        // and multiple it by TILE_SIZE to get the screen coordinates.
		vec2 current_pos = { BELL_POS[map_index - 1] * TILE_SIZE };

        // Pass this position to be used in the hitbox detection check
		bell_current_pos = current_pos;

        // Offset the position for drawing
		vec2 draw_pos = { current_pos.x, current_pos.y - 0.9f * BELL_SIZE.y };

        // Once the player touches the bell, it loops rings twice and shakes the scree
        const int bell_loops = 2;
        float animation_fps = 20.0f;
        const float total_frames = 5.0f;

        if (player_touch_bell)
        {
            camera->shake_conditions = Camera::shakeConditions::Bell;
            camera->shakeCamera(deltaTime);
            if (bell_loop_index == 0) animation_fps *= 2; // Make the bell ring faster on the first loop

            // Update frame
            frame += animation_fps * deltaTime;

            // In loop
            if (frame >= total_frames)
            {
                frame -= total_frames;
                bell_loop_index++;
            }

            // Done looping
            if (bell_loop_index >= bell_loops)
            {
                player_touch_bell = false;
                bell_loop_index = 0;
                frame = 0.0f;
            }
        }

        // Gather the frame to use and draw it on the screen attatched to the camera.
        img_bell_animated.SetFrame(static_cast<int>(frame));
        camera->drawWithCam(&img_bell_animated, screen, draw_pos);
	}
}


#include "bell.h"

namespace Tmpl8
{
	Bell::Bell(Level& levelRef):
        level(levelRef)
    {}

	Sprite img_bell(new Surface("assets/images/map/img_bell.png"), 1);
    Sprite img_bell_animated(new Surface("assets/images/map/img_bell_animated.tga"), 5);

	const int BELL_HEIGHT = img_bell.GetHeight();
	const int BELL_WIDTH = img_bell.GetWidth();

    void Bell::isBellTouchingPlayer(Player* player, GameSound* gamesound)
    {
        // Define player bounding box
        float player_x = player->position.x;
        float player_y = player->position.y;
        float player_hitbox = hitbox_radius;  

        float reduce_hitbox = 10.0f; // Shrink the bell's hitbox
        float bell_x = bell_current_pos.x + reduce_hitbox;
        float bell_y = bell_current_pos.y - BELL_HEIGHT + reduce_hitbox;
        float bell_width = BELL_WIDTH - 2 * reduce_hitbox;
        float bell_height = BELL_HEIGHT - 2 * reduce_hitbox;

        // AABB collision check
        player_touch_bell =
                            player_x < bell_x + bell_width &&
            player_x + player_hitbox > bell_x &&
                            player_y < bell_y + bell_height &&
            player_y + player_hitbox > bell_y;


        if (player_touch_bell)
        {
            gamesound->playSound(gamesound->snd_bell);
            level.nextLevel();
        }
    }

	void Bell::drawBell(Surface* screen, Camera* camera, int map_index, float deltaTime)
	{
		vec2 current_pos = { BELL_POS[map_index - 1] * TILE_SIZE };
		bell_current_pos = current_pos;

		vec2 draw_pos = { current_pos.x, current_pos.y - 0.9f * BELL_HEIGHT };

        static float frame = 0.0f;
        static int bell_loop_index = 0;
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

        img_bell_animated.SetFrame(frame);

        camera->drawWithCam(&img_bell_animated, screen, draw_pos);
	}

    //void Collisions::drawSplash(Surface* screen, vec2 player_pos, float deltaTime)
    //{
    //    if (checkCollisionB(player_pos, false, false) == None || !isOnIce) return;

    //    static float frame = 0.0f;
    //    const float animation_fps = 10.0f;

    //    frame += animation_fps * deltaTime;
    //    if (frame >= 3.0f) frame -= 3.0f;

    //    img_water_slide_right.SetFrame(frame);
    //    img_water_slide_left.SetFrame(frame);

    //    vec2 offset = vec2(
    //        -hitbox_radius,
    //        -hitbox_radius - 2.0f
    //    );

    //    vec2 draw_pos = player_pos + camera.getCamPos() + offset;

    //    if (player.velocity.x > 0)   img_water_slide_right.Draw(screen, draw_pos);
    //    else                         img_water_slide_left.Draw(screen, draw_pos);
    //}
}


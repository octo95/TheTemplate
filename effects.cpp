#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "collisions.h"
#include <cmath>

namespace Tmpl8
{
    void Effects::drawSplash(Surface* screen, vec2 player_pos, float deltaTime)
    {
        if (getCollisionType(player_pos) != TileType::Ice) return;

        static float frame = 0.0f;
        const float animation_fps = 10.0f;

        frame += animation_fps * deltaTime;
        if (frame >= 3.0f) frame -= 3.0f;

        img_water_slide_right.SetFrame(frame);
        img_water_slide_left.SetFrame(frame);

        vec2 offset = vec2(
            img_water_slide_right.GetWidth() / 2 - player_img_width / 2,
            img_water_slide_right.GetHeight() / 2 - player_img_height / 2 + player.PLAYER_DRAW_OFFSET_Y + 1
        );

        vec2 draw_pos = player_pos + camera.getCamPos() + offset;

        if (player.velocity.x > 0)   img_water_slide_right.Draw(screen, draw_pos);
        else                         img_water_slide_left.Draw(screen, draw_pos);
    }
}



//if ((CheckBottom == TileType::Collision && fabs(player.velocity.x) > 2.0f))
//{
//    gamesound.playRollingSound(gamesound.snd_rolling);
//}
//else
//{
//    gamesound.stopRollingSound();
//}
// 
// SFX: if falling from a high distance play <snd_fall_strong.wav>, otherwise from a smaller one play <snd_fall.wav> and if even smaller don't play any SFX.
//if ((TileType::Collision || TileType::Ice) && FallLight) 
//{
//    printf("fall light: %.0f\n", player.velocity.y);
//    bouncing_force = 1.0f;
//}
//if ((TileType::Collision || TileType::Ice) && FallNormal) 
//{
//    gamesound.playSound(gamesound.snd_fall);
//    printf("fall normal: %.0f\n", player.velocity.y);
//    bouncing_force = 1.5f;
//}
//if ((TileType::Collision || TileType::Ice) && FallHard) 
//{
//    gamesound.playSound(gamesound.snd_fall_strong);
//    printf("fall hard: %.0f\n", player.velocity.y);
//    bouncing_force = 10.0f;
//    camera.setShakeState(Camera::shakeConditions::FallHard);
//}

/*  + OLD COLLISION CHECK SYSTEM (for documentation purpose)

    TileType Collisions::CheckCollisionBottom(const vec2int& pos)
    {
        TileType t_left = TileType::None;
        TileType t_right = TileType::None;

        int clamp_pos_x = pos.x / TILE_radius * TILE_radius;
        int clamp_pos_y = pos.y / TILE_radius * TILE_radius;

        if (((pos.y - clamp_pos_y) + hitbox_radius * 2) >= TILE_radius) {
            auto l = tilemap.tile_at(clamp_pos_x, pos.y + TILE_radius);
            if (l.type != TileType::None) t_left = l.type;

            auto r = tilemap.tile_at((pos.x + (hitbox_radius * 2)) / TILE_radius * TILE_radius, pos.y + TILE_radius);
            if (r.type != TileType::None) t_right = r.type;
        }

        // If the player is more than half on the left
        if ((t_left == TileType::Damage || t_left == TileType::End) && (pos.x - (pos.x / TILE_radius * TILE_radius)) < hitbox_radius) {
            return t_left;
        }

        // If the player is more than half on the right
        if ((t_right == TileType::Damage || t_right == TileType::End) && (pos.x - (pos.x / TILE_radius * TILE_radius)) >= hitbox_radius) {
            return t_right;
        }

        return (t_left == TileType::Collision || t_left == TileType::Ice) ? t_left : t_right;
    }
*/
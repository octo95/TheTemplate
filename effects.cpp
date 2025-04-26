#include "effects.h"

namespace Tmpl8
{
    Sprite img_water_slide(new Surface("assets/images/entities/img_water_slide.tga"), 3);
    static int frame = 0;

    void Effects::drawWaterSplash(Surface* screen, float deltaTime, vec2 player_pos)
    {
        img_water_slide.SetFrame(frame);
        img_water_slide.Draw(screen, (int)player_pos.x, (int)player_pos.y);
        if (++frame == 3) frame = 0;
    }
}
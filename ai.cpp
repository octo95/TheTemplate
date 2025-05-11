#include "ai.h"
#include "ai_copy.h"
#include "ai_follow.h"
#include "ai_patrol.h"
#include "surface.h"
#include "camera.h"
#include "tilemap.h"

namespace Tmpl8
{

    void workAI(AIMap* ai_map, float& localTime, Collisions& collisions, TileMap& tilemap) 
    {
        if (ai_map->ai_copy_map.size() > 0)
        {
            for (AI_Copy& ai : ai_map->ai_copy_map) {
                ai.setProperties();
                ai.updatePlayerBuffer();
            }
        }
        if (ai_map->ai_follow_map.size() > 0)
        {
            for (AI_Follow& ai : ai_map->ai_follow_map) {
                ai.followPlayer(localTime);
            }
        }
        if (ai_map->ai_patrol_map.size() > 0) {
            for (AI_Patrol& ai : ai_map->ai_patrol_map) {
                if (!ai.isDead)
                {
                    ai.setProperties();
                    ai.Patrol(localTime, &collisions, &tilemap);
                }
            }
        }
    }

    void drawAI(AIMap* ai_map, Surface* screen, float& deltaTime, Camera& camera) 
    {
        if (ai_map->ai_copy_map.size() > 0)
        {
            for (AI_Copy& ai : ai_map->ai_copy_map) {
                camera.drawAICopy(&img_ai_copy, screen, ai.position, deltaTime, ai.acceleration);
            }
        }
        if (ai_map->ai_follow_map.size() > 0)
        {
            for (AI_Follow& ai : ai_map->ai_follow_map) {
                img_ai_follow.DrawRotated(screen, ai.position + camera.getCamPos(), ai.angle);
            }
        }
        if (ai_map->ai_patrol_map.size() > 0) 
        {
            for (AI_Patrol& ai : ai_map->ai_patrol_map) {
                if(!ai.isDead) img_ai_patrol.DrawRotated(screen, ai.position + camera.getCamPos(), ai.angle);
            }
        }
    }

    bool AI::isTouchingPlayer(Sprite* img)
    {
        float ai_rad = img->GetWidth() / 2.0f;

        // AI center
        vec2 ai_pos = this->position + vec2(ai_rad, ai_rad);

        // Distance between AI's center and the player's one (the player's anchor point being already in the middle).
        vec2 diff = ai_pos - player.position;

        float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);
        float radii_sum = ai_rad + player.hitbox_radius;

        // The AI touches the player if its distance is inferior to the sum of the radii
        bool touch = distance <= radii_sum;

        return touch;
    }
}

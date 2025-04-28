#include "ai_copy.h"

namespace Tmpl8
{

    AI_Copy::AI_Copy(Player& playerRef, Camera& cameraRef) :
        camera(cameraRef),
        player(playerRef)
    {}


    Sprite img_ai_copy(new Surface("assets/images/entities/img_ai_copy.png"), 1);

    void AI_Copy::setPos()
    {
		this->position.x = player.position.x + 100;
		this->position.y = player.position.y + 100;
    }

    bool AI_Copy::isTouchingPlayer()
    {
        float ai_rad = img_ai_copy.GetWidth() / 2.0f;
        float player_rad = player_img_width / 2.0f;

        float radii_sum = ai_rad + player_rad;

        // AI center
        float ai_center_x = this->position.x + ai_rad;
        float ai_center_y = this->position.y + ai_rad;

        // Player center
        float player_center_x = player.position.x + player_rad;
        float player_center_y = player.position.y + player_rad;

        // Distance between AI's center and the player's one.
        float dx = ai_center_x - player_center_x;
        float dy = ai_center_y - player_center_y;
        float distance = sqrtf(dx * dx + dy * dy);

        return (distance <= radii_sum);
    }
}


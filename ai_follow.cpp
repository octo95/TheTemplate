#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "ai_follow.h"
#include <cmath>

namespace Tmpl8
{

    AI_Follow::AI_Follow(Player& playerRef, Camera& cameraRef) :
        camera(cameraRef),
        player(playerRef)
    {}

    Sprite img_ai_follow(new Surface("assets/images/entities/img_ai_follow.png"), 1);

    void AI_Follow::followPlayer(float deltaTime)
    {
        if (!is_following) return;

        const float delayAmplifier = 0.5f;

        float diffX = player.position.x - this->position.x;
        float diffY = player.position.y - this->position.y;

        this->position.x += diffX * deltaTime * delayAmplifier;
        this->position.y += diffY * deltaTime * delayAmplifier;
    }

    bool AI_Follow::isTouchingPlayer()
    {
        float ai_rad = img_ai_follow.GetWidth() / 2.0f;
        float player_rad = player_img_width / 2.0f;

        float radii_sum = ai_rad + player_rad;

        float dx = this->position.x - player.position.x;
        float dy = this->position.y - player.position.y;
        float distance = sqrtf(dx * dx + dy * dy);

        return (distance <= radii_sum);
    }
}

// follow the player's pos with a delay of deltaTime * k
// get the delayed position with a buffer (probably its own class player_pos_record)
// if player stops then start the auto_follow logic
/*
* Auto follow logic:
* 
* if velocity < 0 set previousDirection to left else set it to right
* when velocity = 0 <=> player stopped
* check previousDirection and increment towards it
* if it touches the player count it as a damage
*/

/*
* 
Floating movement
const float delayAmplifier = 1.0f;

float diffX = player.position.x - ai_follow_pos.x;
float diffY = player.position.y - ai_follow_pos.y;

ai_follow_pos.x += diffX * deltaTime * delayAmplifier;
ai_follow_pos.y += diffY * deltaTime * delayAmplifier;

*/

/*
Remaining logic todo:
give the ai a default_pos
reset ai pos when switching levels
*/
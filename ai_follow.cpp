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

    Sprite img_ai_follow(new Surface("assets/evil_tangerine.png"), 1);

    vec2 ai_follow_pos = { 0, 0 };

    void AI_Follow::followPlayer(float deltaTime) // TODO
    {
        const float delayAmplifier = 0.5f;

        float diffX = player.position.x - ai_follow_pos.x;
        float diffY = player.position.y - ai_follow_pos.y;

        ai_follow_pos.x += diffX * deltaTime * delayAmplifier;
        ai_follow_pos.y += diffY * deltaTime * delayAmplifier;
    }

    void AI_Follow::manageDefaultPosAI_Follow(int index)
    {
        switch (index)
        {
        case 1 :
            ai_follow_pos = AI_FOLLOW_DEFAULT_POS[0];
        case 2 :
            ai_follow_pos = AI_FOLLOW_DEFAULT_POS[1];
        case 3:
            ai_follow_pos = AI_FOLLOW_DEFAULT_POS[2];
        }
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
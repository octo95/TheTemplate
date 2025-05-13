#pragma once
#include "player.h"

namespace Tmpl8 {

    // Categorize all the AIs we have.
    /*--------------------------------
    * AI Copy:      copies the player's movement from <pastState> seconds ago.
    * AI Follow:    follows the player flying at a speed that depends on its distance with the player.
    * AI Patrol     patrols left / right until it hits a collision, can be stomped by the player.
    */
    enum AIType {
        Follow,
        Copy,
        Patrol
    };

    class Collisions;
    class AI_Copy;
    class AI_Patrol;
    class AI_Follow;

    class AI
    {
    public:
        // Constructor
        AI(
            Player& playerRef,
            vec2 spawn_pos
        ) :
            player(playerRef),
            position(spawn_pos)
        {
        };

        // Variables
        float angular_acceleration = 0;     // Angular acceleration used to draw with an angle.
        bool stop = false;                  // Stops the AI if true (for debug).
        vec2 default_pos = { -500, -500 };  // Make the AI appear out of bounds when not on screen.
        vec2 position;
        Player& player;

        // Functions
        bool isTouchingPlayer(Sprite* img);
        void setProperties() {};
    };

    // Create a map containing all the AI types.
    struct AIMap {
        std::vector<AI_Copy> ai_copy_map;
        std::vector<AI_Follow> ai_follow_map;
        std::vector<AI_Patrol> ai_patrol_map;
    };

    // We seperate the logic of the AIs with work and draw to be able to pause their logic properly when pausing the game.
    void workAI(AIMap* ai_map, float& localTime, Collisions& collisions, TileMap& tilemap);
    void drawAI(AIMap* ai_map, Surface* screen, float& deltaTime, Camera& camera);
}
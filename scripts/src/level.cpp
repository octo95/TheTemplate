#include "../include/level.h"
#include "../include/ai.h"
#include "../include/ai_copy.h"
#include "../include/ai_patrol.h"
#include "../include/ai_follow.h"

namespace Tmpl8
{
    Level::Level(AIMap& ai_mapRef, Camera& cameraRef, CloudMap& cloudRef, CollectibleMap& collectibleRef, GameSound& gamesoundRef, Player& playerRef, TileMap& tilemapRef, WallMap& wallRef) :
        ai_map(ai_mapRef),
        camera(cameraRef),
        cloud(cloudRef),
        collectible(collectibleRef),
        gamesound(gamesoundRef),
        player(playerRef),
        tilemap(tilemapRef),
        wall(wallRef)
    {}

    void Level::loadLevel(int map_index)
    {
        // Load a level by setting its logic.
        /*-------------------------------------
        * - Set the state of the collectibles.
        * - Set the player's dashes.
        * - Make sure the camera is not shaking after a bell collision of a previous level by setting it to None.
        * - Load the proper map at given index.
        * - Put the player at its default position for the given map.
        * - Load all the collectibles, walls and clouds.
        * - Reset the AIs
        * - Load the new AIs
        */

        tilemap.secret_collected = false;
        collected_new = false;
        collectible_timer_active = false;
        player.dash_count = 0;
        camera.shake_conditions = Camera::shakeConditions::None;
        tilemap.loadMap(map_index);
        tilemap.current_level = map_index;
        manageDefaultPos(map_index);
        loadAllCollectibles(map_index);
        loadAllWalls(map_index);
        loadAllClouds(&tilemap);
        ai_map.ai_copy_map.clear();
        ai_map.ai_follow_map.clear();
        ai_map.ai_patrol_map.clear();
        manageAIsPerMap(map_index);
    }

    void Level::manageDefaultPos(int map_index)
    {
        // Manage the player's default when loading a level.
        /*---------------------------------------------------
        * - Reset the player's velocity.
        * - Set the player's default position to the given map index's one.
        * - Set the player's position to the default position that was assigned.
        */

        player.resetPlayerVelocity();
        player.setPlayerDefaultPos(PLAYER_DEFAULT_POS[map_index-1]);
        player.setPlayerPos(PLAYER_DEFAULT_POS[map_index - 1]);
    }

    void Level::manageAIsPerMap(int map_index)
    {
        switch (map_index)
        {
        // * No AI on LVL1
        case 1: 
            break;
        // * 2 AI patrol on LVL2
        case 2: 
            addAiPatrol(&ai_map, AI_PATROL_SPAWN_POS[0]);
            addAiPatrol(&ai_map, AI_PATROL_SPAWN_POS[1]);
            break;
        // * 1 AI follow on LVL3
        case 3: 
            addAiFollow(&ai_map, AI_FOLLOW_SPAWN_POS[0]);
            break;
        // * 1 AI copy on LVL4
        case 4: 
            addAiCopy(&ai_map, 5.0f);
            break;
        // * 2 AI copy, 1 AI follow and 2 AI patrol on LVL5
        case 5: 
            addAiCopy(&ai_map, 5.0f);
            addAiCopy(&ai_map, 6.0f);
            addAiFollow(&ai_map, AI_FOLLOW_SPAWN_POS[1]);
            addAiPatrol(&ai_map, AI_PATROL_SPAWN_POS[2]);
            addAiPatrol(&ai_map, AI_PATROL_SPAWN_POS[3]);
            break;
        default:
            break;
        }
    }

    void Level::nextLevel()
    {
        // If the current level is the same as the total amount of levels it means it's the last one and the game is finished.
        if (tilemap.getCurrentLevel() == MAP_AMOUNT)
        {
            game_finished = true;
            return;
        }

        // Otherwise we can still set the level's state to finish to go to the next one.
        level_finished = true;
    }

    // Helper functions to add AIs in the levels by pushing them back from their respective maps.
    void Level::addAiCopy(AIMap* ai_map, float timer) 
    {
        ai_map->ai_copy_map.push_back(AI_Copy(player, timer));
    }

    void Level::addAiFollow(AIMap* ai_map, vec2 spawn_pos) 
    {
        ai_map->ai_follow_map.push_back(AI_Follow(player, spawn_pos * TILE_SIZE, camera));
    }

    void Level::addAiPatrol(AIMap* ai_map, vec2 spawn_pos) 
    {
        ai_map->ai_patrol_map.push_back(AI_Patrol(player, spawn_pos * TILE_SIZE, camera));
    }
}

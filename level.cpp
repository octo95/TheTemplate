#include "level.h"
#include "ai.h"
#include "ai_copy.h"
#include "ai_patrol.h"
#include "ai_follow.h"

namespace Tmpl8
{
    Level::Level(TileMap& tilemapRef, Player& playerRef, CollectibleMap& collectibleRef,WallMap& wallRef, GameSound& gamesoundRef, AIMap& ai_mapRef, Camera& cameraRef) :
        tilemap(tilemapRef),
        player(playerRef),
        collectible(collectibleRef),
        wall(wallRef),
        gamesound(gamesoundRef),
        ai_map(ai_mapRef),
        camera(cameraRef)
    {}

    void Level::loadLevel(int map_index)
    {
        collected_new = false;
        collectible_timer_active = false;
        player.dash_count = 0;
        tilemap.loadMap(map_index);
        tilemap.current_level = map_index;
        player.position = player.default_pos;
        manageDefaultPos(map_index);
        loadAllCollectibles(map_index);
        loadAllWalls(map_index);

        // reset AI
        ai_map.ai_copy_map.clear();
        ai_map.ai_follow_map.clear();
        ai_map.ai_patrol_map.clear();

        // load new AI
        manageAIsPerMap(map_index);
    }

    void Level::manageDefaultPos(int map_index)
    {
        player.resetPlayerVelocity();
        player.setPlayerDefaultPos(PLAYER_DEFAULT_POS[map_index-1]);
        player.setPlayerPos(PLAYER_DEFAULT_POS[map_index - 1]);
    }

    void Level::manageAIsPerMap(int map_index)
    {
        switch (map_index)
        {
        case 1: // No AI on LVL1
            break;
        case 2: // 2 AI patrol on LVL2
            addAiPatrol(&ai_map, AI_PATROL_SPAWN_POS[0]);
            addAiPatrol(&ai_map, AI_PATROL_SPAWN_POS[1]);
            break;
        case 3: // AI follow on LVL3
            addAiFollow(&ai_map, AI_FOLLOW_SPAWN_POS[0]);
            break;
        case 4: // AI copy on LVL4
            addAiCopy(&ai_map, 5.0f);
            break;
        case 5: // All AIs on LVL5
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
        if (tilemap.getCurrentLevel() == MAP_AMOUNT)
        {
            game_finished = true;
            return;
        }
        level_finished = true;
    }

    void Level::addAiCopy(AIMap* ai_map, float timer) {
        ai_map->ai_copy_map.push_back(AI_Copy(player, timer));
    }

    void Level::addAiFollow(AIMap* ai_map, vec2 spawn_pos) {
        ai_map->ai_follow_map.push_back(AI_Follow(player, spawn_pos * TILE_SIZE, camera));
    }

    void Level::addAiPatrol(AIMap* ai_map, vec2 spawn_pos) {
        ai_map->ai_patrol_map.push_back(AI_Patrol(player, spawn_pos * TILE_SIZE, camera));
    }
}

#include "level.h"


namespace Tmpl8
{
    Level::Level(TileMap& tilemapRef, Player& playerRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef,WallMap& wallRef, GameSound& gamesoundRef, AI_Patrol& ai_patrolRef, AI_Copy& ai_copyRef) :
        tilemap(tilemapRef),
        player(playerRef),
        ai_follow(ai_followRef),
        collectible(collectibleRef),
        wall(wallRef),
        gamesound(gamesoundRef),
        ai_patrol(ai_patrolRef),
        ai_copy(ai_copyRef)
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
        manageAIsPerMap(map_index);
    }

    void Level::manageDefaultPos(int map_index)
    {
        player.resetPlayerVelocity();
        player.setPlayerDefaultPos(PLAYER_DEFAULT_POS[map_index-1]);
        player.setPlayerPos(PLAYER_DEFAULT_POS[map_index - 1]);
        ai_follow.setAIFollowDefaultPos(AI_FOLLOW_DEFAULT_POS[map_index - 1]);
        ai_follow.setAIFollowPos(AI_FOLLOW_DEFAULT_POS[map_index - 1]);
    }

    void Level::manageAIsPerMap(int map_index)
    {
        ai_follow.setAIFollowPos(AI_FOLLOW_DEFAULT_POS[map_index - 1]);
        ai_patrol.setAIPatrolPos(AI_PATROL_DEFAULT_POS[map_index - 1]);
        switch (map_index)
        {
        case 1: // No AI on LVL1
            // ai_map.insert(AI_Copy(player, AI_FOLLOW_DEFAULT_POS[map_index - 1]));
            // ai_map.insert(AI_Follow(player, AI_FOLLOW_DEFAULT_POS[map_index - 1]));
            // ai_map.insert(AI_Patrol(player, AI_PATROL_DEFAULT_POS[map_index - 1]));
            ai_copy.stop = true;
            ai_patrol.isDead = true;
            ai_follow.is_following = false;
            break;
        case 2: // AI patrol on LVL2
            ai_copy.stop = true;
            ai_patrol.isDead = false;
            break;
        case 3: // AI follow on LVL3
            ai_copy.stop = true;
            ai_follow.is_following = true;
            break;
        case 4: // AI copy on LVL4
            ai_copy.stop = false;
            ai_copy.playerBuffer.reset();
            ai_copy.position = ai_copy.default_pos;
            ai_copy.copyTimer = 3.0f;
            ai_follow.is_following = false;
            ai_patrol.isDead = true;
            break;
        case 5: // All AIs on LVL5
            ai_copy.stop = false;
            ai_copy.playerBuffer.reset();
            ai_copy.position = ai_copy.default_pos;
            ai_copy.copyTimer = 3.0f;
            ai_follow.is_following = true;
            ai_patrol.isDead = false;
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
}

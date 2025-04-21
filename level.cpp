#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "level.h"

namespace Tmpl8
{
    Level::Level(TileMap& tilemapRef, Player& playerRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef,WallMap& wallRef) :
        tilemap(tilemapRef),
        player(playerRef),
        ai_follow(ai_followRef),
        collectible(collectibleRef),
        wall(wallRef)
    {}

    void Level::loadLevel(int map_index)
    {
        manageDefaultPos(map_index);
        clearCollectibles();
        clearWalls();
        tilemap.setMapIndex(map_index);
        loadAllWalls();
        loadAllCollectibles();
        loadCollectiblesForMap(map_index);
        loadWallsForMap(map_index);
    }

    void Level::manageDefaultPos(int map_index)
    {
        switch (map_index)
        {
        case 1:
            player.setPlayerDefaultPos(PLAYER_DEFAULT_POS[0]);
            player.setPlayerPos(PLAYER_DEFAULT_POS[0]);
            ai_follow.setAIFollowDefaultPos(AI_FOLLOW_DEFAULT_POS[0]);
            ai_follow.setAIFollowPos(AI_FOLLOW_DEFAULT_POS[0]);
            break;
        case 2:
            player.setPlayerDefaultPos(PLAYER_DEFAULT_POS[1]);
            player.setPlayerPos(PLAYER_DEFAULT_POS[1]);
            ai_follow.setAIFollowDefaultPos(AI_FOLLOW_DEFAULT_POS[1]);
            ai_follow.setAIFollowPos(AI_FOLLOW_DEFAULT_POS[1]);
            break;
        case 3:
            player.setPlayerDefaultPos(PLAYER_DEFAULT_POS[2]);
            player.setPlayerPos(PLAYER_DEFAULT_POS[2]);
            ai_follow.setAIFollowDefaultPos(AI_FOLLOW_DEFAULT_POS[2]);
            ai_follow.setAIFollowPos(AI_FOLLOW_DEFAULT_POS[2]);
            break;
        }
    }
}

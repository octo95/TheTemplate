#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "level.h"

namespace Tmpl8
{
    Level::Level(TileMap& tilemapRef, Player& playerRef, AI_Follow& ai_followRef, CollectibleMap& collectibleRef,WallMap& wallRef, GameSound& gamesoundRef) :
        tilemap(tilemapRef),
        player(playerRef),
        ai_follow(ai_followRef),
        collectible(collectibleRef),
        wall(wallRef),
        gamesound(gamesoundRef)
    {}

    void Level::loadLevel(int map_index)
    {
        collectibles_collected = 0;
        tilemap.current_level = map_index;
        player.position = player.default_pos;
        tilemap.setMapIndex(map_index);
        manageDefaultPos(map_index);
        loadAllCollectibles(map_index);
        loadAllWalls(map_index);
        ai_follow.setAIFollowPos(AI_FOLLOW_DEFAULT_POS[map_index-1]);
    }

    void Level::manageDefaultPos(int map_index)
    {
        player.resetPlayerVelocity();
        player.setPlayerDefaultPos(PLAYER_DEFAULT_POS[map_index-1]);
        player.setPlayerPos(PLAYER_DEFAULT_POS[map_index - 1]);
        ai_follow.setAIFollowDefaultPos(AI_FOLLOW_DEFAULT_POS[map_index - 1]);
        ai_follow.setAIFollowPos(AI_FOLLOW_DEFAULT_POS[map_index - 1]);
    }
}

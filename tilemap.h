#pragma once
#include "surface.h"
#include "tile.h"
#include "player.h"

namespace Tmpl8
{
    const int TOTAL_MAPS = 3;
    const int TILE_ROWS = 32;
    const int TILE_COLUMNS = 27;

    const char MAP1[TILE_ROWS][TILE_COLUMNS * 3] = {
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca da da da da da da da ca ca da da da da da da da da da da da da da da ca ca",
    "ca ca da da da da da da da da ca da da da da da da da da da da da da da da ca ca",
    "ca ca ca ca ca ca ca da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca ca ca ca ca ca da ca ca ca ca ca ca ca ca ca ca da da da da da da da ca ca",
    "ca ca ca ca ca ca ca da da da da da da da da da da da da ca ca ca ca da da ca ca",
    "ca ca ca ca ca ca ca da da da da da da da da da da da da ca ca ca ca da da ca ca",
    "ca ca ca ca ca ca ca da da da da da da da da da da da da ca ca ca ca da da ca ca",
    "ca ca ca ca ca ca ca da da da da da da da da da da da da ca ca ca ca da da ca ca",
    "ca ca ca ca ca ca ca aa aa aa aa aa aa aa aa aa aa aa aa ca ca ca ca da da ca ca",
    "ca ca ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da ca ca",
    "ca ca ca da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca",
    "ca ca ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca",
    "ca ca da da da da da ca ca ca da da da ca ca da da da da ca ca ca da da da ca ca",
    "ca ca da da da da da ca ca da da da da da ca da da da da da ca da da da da ca ca",
    "ca ca da da da da da da ca da da da da da da da da da da da da da da da da ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca da da da da ea ea ea ea ea ea ea ea ea ea ea ea ea ea ca ca ca ca aa ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca aa aa ca ca ca ca ca da da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca da da da da da da da da da da da da da da da da da da da da da da da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da da ca ca",
    "ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da da ca ca",
    "ca ca aa ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da da da ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ba ba ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca"
    };
    const char MAP2[TILE_ROWS][TILE_COLUMNS * 3] = {
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da ca ca ca ca da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da ca da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da ca da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da ca da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da ca ea ea ea da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da ca ca da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da ca da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da ea da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da aa da da da aa da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da ca da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da aa da da da aa da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca ca ba ba ca ca aa ca ca ca ca ca ba ba ca ca ca ca ca ca aa ca ca ba ba ca ca"
    };
    const char MAP3[TILE_ROWS][TILE_COLUMNS * 3] = {
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da da da da da da da da da da da da da da ca",
    "ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca",
    "ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca",
    "ca da da da da da da da da da da da da ca da da da da da da da da da da da da ca",
    "ca da da da da da da da da da da da da ca da da da da da da da da da da da da ca",
    "ca ca ca ca ca ca ca ca ca da da da ca ca ca da da da ca ca ca ca ca ca ca ca ca",
    "ca ca ca ca ca ca ca ca ca da da da ca ca ca da da da ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da ea ea ea ea ea ea ea ea ea ea ea ea ea ea ea da da da ca ca ca",
    "ca ca ca da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da da da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca aa aa da da ca ca ca ca da da da da da ca ca ca ca ca ca aa aa ca ca ca",
    "ca ca ca ca ca da da ca ca ca ca da da da da da ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da da ca ca ca ca da da da da da ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca aa aa da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da ca da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca da da da ca ca ca ca ca da da da da da ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca ca da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca ca ca da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca da da da da da ca ca ca ca ca ca ca ca ca ca ca ca ca ca ca da ca ca ca",
    "ca ca ca ca ca da da aa ca ca ca da da da da da ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca da da da da da da da da da da da da da da da da da da da da da ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca ca",
    "ca ca ca ca ca ca ca ca ca ca ca ba ba ba ba ba ca ca ca ca ca ca ca ca ca ca ca"
    };

    class Player;

    class TileMap {
    public:
        const char (*current_map)[TILE_COLUMNS * 3];

        TileMap();
        void setPlayer(Player* p) { player = p; }
        int getCurrentLevel() const;
        void setMapIndex(int index);
        int incrementMapIndex();
        Tile tile_at(int x, int y);
        void drawMap(Surface* screen, const Camera& camera);
    private:
        Player* player;
        int current_level = 1;
    };
};


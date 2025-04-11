#ifndef TANK_H
#define TANK_H

#include "surface.h"
#include <vector>
#include <utility>

namespace Tmpl8
{
    extern const int tile_size;
    extern const int tank_width;
    extern const int screen_width;
    extern const int screen_height;

    std::vector<std::pair<int, int>> GetSpawnableTiles();
    bool isValidPosition(int x, int y);
    void TurnBack(int& x, int& y);
    extern Sprite tank;

    class AI_Tank
    {
    public:
        AI_Tank();
        void Move(Surface* gameScreen);

        int x, y;

    private:
        bool moveUp;
        int rotation;
    };
}

#endif // TANK_H

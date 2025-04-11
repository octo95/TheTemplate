#include "tank.h"
#include <cstdlib>
#include <ctime>

namespace Tmpl8
{
    AI_Tank::AI_Tank()
    {
        static bool seeded = false;
        if (!seeded)
        {
            srand(static_cast<unsigned int>(time(0)));
            seeded = true;
        }

        auto spawnable = GetSpawnableTiles();
        if (!spawnable.empty())
        {
            int r = rand() % spawnable.size();
            int tx = spawnable[r].first;
            int ty = spawnable[r].second;

            x = tx * tile_size + tile_size / 2 - tank_width / 2;
            y = ty * tile_size + tile_size / 2 - tank_width / 2;
        }
        else
        {
            x = 0;
            y = 300;
        }
        rotation = 0;
        moveUp = false; // Start by moving right
    }

    void AI_Tank::Move(Surface* gameScreen)
    {
        int nx = x + 1;
        int ny = y;

        // If nothing on the way, move right
        if (isValidPosition(nx, ny))
        {
            x = nx;
            moveUp = false; // Reset the flag when we can move right
        }
        else
        {
            // If stuck, move up or down based on the flag
            if (moveUp)
            {
                ny = y - 1;
                if (isValidPosition(x, ny))
                {
                    y = ny;
                }
            }
            else
            {
                ny = y + 1;
                if (isValidPosition(x, ny))
                {
                    y = ny;
                }
            }

            // If still stuck, change direction
            if (!isValidPosition(x, ny))
            {
                moveUp = !moveUp;
            }
        }

        TurnBack(x, y);
        tank.Draw(gameScreen, x, y);
    }
}

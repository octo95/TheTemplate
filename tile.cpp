#include "game.h"
#include "surface.h"
#include "tile.h"

namespace Tmpl8
{
    // Variables
    Surface tiles("assets/nc2tiles.png");
    
    // Tile functions
    void Tile::DrawTile(Surface* screen, int x, int y)
    {
        Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
        Pixel* dst = screen->GetBuffer();

        for (int yl = 0; yl < TILE_SIZE; yl++)
        {
            for (int xl = 0; xl < TILE_SIZE; xl++) 
            {
                // Cut out of the screen pixels
                int x_t = x + xl + CAM_OFFSET_X;
                int y_t = y + yl + CAM_OFFSET_Y;

                if (x_t <= 800 && x_t >= 0 && y_t <= 512 && y_t >= 0) {
                    dst[x_t + y_t * 800] = src[xl + yl * 595];
                }
            }
        }
    }
};
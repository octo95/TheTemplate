#include "tile.h"

namespace Tmpl8
{
    // Variables
    Surface tiles("assets/nc2tiles.png");
    const int IMG_TILEMAP_WIDTH = tiles.GetWidth();
    
    // Tile functions
    void Tile::DrawTile(Surface* screen, int x, int y, const Camera& camera)
    {
        Pixel* src = tiles.GetBuffer() + 1 + tx * (1 + TILE_SIZE) + (1 + ty * (1 + TILE_SIZE)) * IMG_TILEMAP_WIDTH;
        Pixel* dst = screen->GetBuffer();

        for (int yl = 0; yl < TILE_SIZE; yl++)
        {
            for (int xl = 0; xl < TILE_SIZE; xl++) 
            {
                // Cut out of the screen pixels
                int x_t = x + xl + camera.getCamPos().x;
                int y_t = y + yl + camera.getCamPos().y;

                if (x_t <= SCREEN_WIDTH && x_t >= 0 && y_t <= SCREEN_HEIGHT && y_t >= 0) {
                    dst[x_t + y_t * SCREEN_WIDTH] = src[xl + yl * IMG_TILEMAP_WIDTH];
                }
            }
        }
    }
};
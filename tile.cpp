#include "game.h"
#include "surface.h"
#include "tile.h"
#include "camera.h"

namespace Tmpl8
{
    // Variables
    Surface tiles("assets/nc2tiles.png");
    const int IMG_TILEMAP_WIDTH = tiles.GetWidth();
    
    // Tile functions
    void Tile::DrawTile(Surface* screen, int x, int y)
    {
        Pixel* src = tiles.GetBuffer() + 1 + tx * (1 + TILE_SIZE) + (1 + ty * (1 + TILE_SIZE)) * IMG_TILEMAP_WIDTH;
        Pixel* dst = screen->GetBuffer();

        for (int yl = 0; yl < TILE_SIZE; yl++)
        {
            for (int xl = 0; xl < TILE_SIZE; xl++) 
            {
                // Cut out of the screen pixels
                int x_t = x + xl + cam_offset_x + 1; // Note: doing +1 makes it a bit better?
                int y_t = y + yl + cam_offset_y;

                if (x_t <= SCREEN_WIDTH && x_t >= 0 && y_t <= SCREEN_HEIGHT && y_t >= 0) {
                    dst[x_t + y_t * SCREEN_WIDTH] = src[xl + yl * IMG_TILEMAP_WIDTH];
                }
            }
        }
    }
};
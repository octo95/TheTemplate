#include "game.h"
#include "surface.h"
#include "tile.h"

namespace Tmpl8
{
    Surface tiles("assets/nc2tiles.png");

    void Tile::DrawTile(Surface* screen, int x, int y)
    {
        Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
        Pixel* dst = screen->GetBuffer() + x + y * 800;
        for (int i = 0; i < TILE_SIZE; i++, src += 595, dst += 800)
            for (int j = 0; j < TILE_SIZE; j++)
                dst[j] = src[j];
    }
};

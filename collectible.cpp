#define WIN32_LEAN_AND_MEAN
#include "collectible.h"
#include "surface.h"
#include <stdio.h>
#include "tile.h"
#include "camera.h"

namespace Tmpl8
{
	Sprite img_collectible(new Surface("assets/collectible.png"), 1);

	void Collectible::drawCollectible(Surface* screen, int x, int y)
	{
		int tx = x / TILE_SIZE + camera.getCamPos().x;
		int ty = y / TILE_SIZE + camera.getCamPos().y;
		img_collectible.Draw(screen, tx, ty);
	}

	int Collectible::setCPos(int value)
	{
		return value * TILE_SIZE + TILE_SIZE / 2;
	}
}

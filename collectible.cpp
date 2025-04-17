#include "collectible.h"
#include "tile.h"

namespace Tmpl8
{
	Sprite img_collectible(new Surface("assets/collectible.png"), 1);

	void Collectible::drawCollectible(Surface* screen, int x, int y)
	{
		int tx = x / TILE_SIZE;
		int ty = y / TILE_SIZE;
		img_collectible.Draw(screen, tx, ty);
	}

	int Collectible::setCPos(int value)
	{
		return value * TILE_SIZE + TILE_SIZE / 2;
	}
}

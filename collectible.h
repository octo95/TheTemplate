#pragma once
#include "surface.h"
#include "camera.h"

namespace Tmpl8
{
	extern Sprite img_collectible;

	class Collectible
	{
	public:
		void drawCollectible(Surface* screen, int x, int y);
		int setCPos(int value);
	private:
		Camera camera;
	};
}
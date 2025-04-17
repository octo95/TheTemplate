#pragma once
#include "surface.h"
#include "camera.h"

namespace Tmpl8
{
	class Collectible
	{
	public:
		void drawCollectible(Surface* screen, int x, int y);
	private:
		Camera camera;
	};
}
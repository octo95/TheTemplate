#pragma once
#include "template.h"
#include "surface.h"

namespace Tmpl8
{
	class Camera
	{
	public:
		void setCamPos(const vec2 &position);
		void camShake(float deltatime);
		vec2 getCamPos() const;
		void Shake();
		void drawWithCam(Sprite* img, Surface* screen, int x, int y);
	private:
		vec2 position = { 0, 0 };
		vec2 shake = { 0, 0 };
		float total_time = 0;
	};
}

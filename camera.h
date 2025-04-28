#pragma once
#include "surface.h"
#include "template.h"
#include <cmath>

namespace Tmpl8
{
	class Camera
	{
		public:
			// Shaking functions
			void shakeCamera(float deltaTime);
			void setShakeState(bool is_shaking);

			// Draw
			void drawWithCam(Sprite* img, Surface* screen, int x, int y);
			void drawPlayer(Sprite* img, Surface* screen, int x, int y, float deltaTime);

			// Getters / Setters
			void setCamPos(const vec2 &position);
			vec2 getCamPos() const;
			float getAngleAcceleration(float value) { return value; }
			void setAngleAcceleration(float value) { acceleration = value; }
		private:
			vec2 position = { 0, 0 };
			vec2 shake = { 0, 0 };
			float total_time = 0;
			float player_angle = 0;
			float acceleration = 0;
			bool shake_state = false;
	};
}

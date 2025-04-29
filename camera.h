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

			// Draw
			void drawWithCam(Sprite* img, Surface* screen, int x, int y);
			void drawWithCam(Sprite* img, Surface* screen, vec2 pos);
			void drawPlayer(Sprite* img, Surface* screen, int x, int y, float deltaTime);
			void drawPlayer(Sprite* img, Surface* screen, vec2 pos, float deltaTime);

			// Getters / Setters
			vec2 getCamPos() const { return position + shake; }
			void setCamPos(const vec2& position) { this->position = position; }
			float getAngleAcceleration(float value) { return value; }
			void setAngleAcceleration(float value) { acceleration = value; }
			void setShakeState(bool is_shaking) { shake_state = is_shaking; }

		private:
			vec2 position = { 0, 0 };
			vec2 shake = { 0, 0 };
			float total_time = 0;
			float player_angle = 0;
			float acceleration = 0;
			bool shake_state = false;
	};
}

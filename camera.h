#pragma once
#include "surface.h"
#include "template.h"
#include <cmath>

namespace Tmpl8
{
	class Camera
	{
		public:
			enum class shakeConditions {
				None,
				Damage,
				FallHard
			};

			shakeConditions shake_conditions = shakeConditions::None;

			// Shaking functions
			void shakeCamera(float deltaTime);

			// Draw
			void drawWithCam(Sprite* img, Surface* screen, vec2 pos);
			void drawPlayer(Sprite* img, Surface* screen, vec2 pos, float deltaTime, float acceleration);
			void drawAICopy(Sprite* img, Surface* screen, vec2 pos, float deltaTime, float acceleration);

			// Getters / Setters
			vec2 getCamPos() const { return position + shake; }
			void setCamPos(const vec2& position) { this->position = position; }
			void setShakeState(shakeConditions condition) { shake_conditions = condition, printf("set: %d\n", (int)shake_conditions); }

		private:
			vec2 position = { 0, 0 };
			vec2 shake = { 0, 0 };
			float total_time = 0;
			float player_angle = 0;
			float ai_copy_angle = 0;
			float player_acceleration = 0;
			float ai_copy_acceleration = 0;
			bool shake_state = false;
	};
}

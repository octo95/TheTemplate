#pragma once
#include "surface.h"
#include "template.h"
#include <cmath>

namespace Tmpl8
{
	class Camera
	{
		public:
			// The camera can shake when getting hit, making a hard fall or ringing the bell, each with different shaking intensity.
			enum class shakeConditions {
				None,
				Damage,
				FallHard,
				Bell
			};

			// Initialize the shake to None by default.
			shakeConditions shake_conditions = shakeConditions::None;

			// Shaking functions
			void shakeCamera(float deltaTime);

			// Helper functions to draw objects that follow the camera logic.
			void drawWithCam(Sprite* img, Surface* screen, vec2 pos);
			void drawPlayer(Sprite* img, Surface* screen, vec2 pos, float deltaTime, float acceleration);
			void drawAICopy(Sprite* img, Surface* screen, vec2 pos, float deltaTime, float acceleration);

			// Getters / Setters
			vec2 getCamPos() const { return position + shake; }
			void setCamPos(const vec2& position) { this->position = position; }
			void setShakeState(shakeConditions condition) { shake_conditions = condition; }

		private:
			vec2 position = { 0, 0 };
			vec2 shake = { 0, 0 };
			float total_time = 0.0f;	// Timer for the shake.
			float player_angle = 0.0f;	// Angle to draw the player.
			float ai_copy_angle = 0.0f;	// Angle to draw the AI copy that follows a pastState angle of the player. (cf. circular_buffer)
	};
}

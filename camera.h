#pragma once
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
	class Camera
	{
	public:
		void setCamPos(const vec2 &position);
		void shakeCamera(float deltaTime);
		vec2 getCamPos() const;
		void setShakeState(bool is_shaking);
		void drawWithCam(Sprite* img, Surface* screen, int x, int y);
		void drawWithCamAndAngle(Sprite* img, Surface* screen, int x, int y, float deltaTime, float acceleration);
		float getAngleAcceleration(float value) { return value; }
		void Camera::setAngleAcceleration(float value) { acceleration = value; }
		void drawPlayer(Sprite* img, Surface* screen, int x, int y, float deltaTime);
	private:
		bool shake_state = false;
		vec2 position = { 0, 0 };
		vec2 shake = { 0, 0 };
		float total_time = 0;
		float player_angle = 0;
		float acceleration = 0;
	};
}

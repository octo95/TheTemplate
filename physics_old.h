#pragma once 

#include "template.h"

namespace Tmpl8
{
	class vec2;
	class Surface;
}

class PhysicsOld
{
public: // Private by default.
	PhysicsOld() = default; // Default constructor
	PhysicsOld(const Tmpl8::vec2& pos, float radius); // Parameratized constructor

	// Follow the rule of 5 -or rule of 7 now with move constructs).

	const Tmpl8::vec2& getPos() const;
	void setPos(const Tmpl8::vec2& pos); // non-const!

	const Tmpl8::vec2& getVel() const;
	void setVel(const Tmpl8::vec2& vel);

	float getRadius() const;
	void setRadius(float radius);

	bool checkCollision(const PhysicsOld& other) const;

	// Update the ball
	// deltaTime: Elapsed time in seconds.
	void update(float deltaTime);

	// Draw the ball to the screen.{0.0f}
	void draw(Tmpl8::Surface* surface);

private:
	Tmpl8::vec2 position{ 0 }; // Prefer default on declaration.
	Tmpl8::vec2 velocity{ 0 }; // Initial velocity both direction and magnitude
	float radius{ 0.0f };
};
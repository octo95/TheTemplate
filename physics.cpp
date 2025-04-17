#include "physics.h"
#include "surface.h"

using namespace Tmpl8;

Physics::Physics(const Tmpl8::vec2& pos, float radius)
    : position{ pos }
    , radius{ radius } // Needs to be in the same order than the declaration of the variables in the private part of the constructor in Ball.hpp
{
}

const Tmpl8::vec2& Physics::getPos() const // Getter
{
    return position;
}

void Physics::setPos(const Tmpl8::vec2& pos) // Setter
{
    position = pos;
}

const Tmpl8::vec2& Physics::getVel() const
{
    return velocity;
}

void Physics::setVel(const Tmpl8::vec2& vel)
{
    velocity = vel;
}

float Physics::getRadius() const // Getter
{
    return radius;
}

void Physics::setRadius(float _radius)
{
    radius = _radius;
}

bool Physics::checkCollision(const Physics& other) const
{
    Tmpl8::vec2 d = other.position - position; // Displacement.
    const float l = d.sqrLentgh();
    const float r = other.radius + radius; // Sum of the radii.

    return l < (r * r);
}

void Physics::update(float deltaTime)
{
    position += velocity * deltaTime;
}

void Physics::draw(Tmpl8::Surface* surface)
{
    for (int i = 0; i < 64; i++)
    {
        const float r1 = static_cast<float>(i) * PI / 32;
        const float r2 = (float)(i + 1) * PI / 32;

        surface->Line(position.x - radius * sinf(r1), position.y - radius * cosf(r1),
            position.x - radius * sinf(r2), position.y - radius * cosf(r2), 0xff0000);
    }
}

/* [game.cpp]
#include "game.h"
#include "surface.h"
#include "template.h"
#include "windows.h"
#include "physics.h"

namespace Tmpl8
{
    void Game::Init() {}

    void Game::Shutdown() {}

    // Draw balls
    Physics ball1{ {300,0}, 16 };
    Physics ball2{ {320, ScreenHeight - 50}, 49 };

    // Initialize x, y and px py
    float x[2] = { 300, 320 };
    float y[2] = { 0, ScreenHeight - 50 };

    float px[2] = { 300, 320 };
    float py[2] = { 0, ScreenHeight - 50 };

    // Force due to gravity in pixels/second.
    const vec2 GRAVITY{ 0.0f, 200.0f };

    // Debug
    void DrawDebugInfo(Surface* screen, const Physics& ball1, const Physics& ball2)
    {
        char buffer[128];

        // Ball1 position
        sprintf(buffer, "Ball1: (%.1f, %.1f)", ball1.getPos().x, ball1.getPos().y);
        screen->Print(buffer, 10, 10, 0xffffff);

        // Ball2 position
        sprintf(buffer, "Ball2: (%.1f, %.1f)", ball2.getPos().x, ball2.getPos().y);
        screen->Print(buffer, 10, 25, 0xffffff);

        // Ball1 velocity
        sprintf(buffer, "Vel1: (%.1f; %.1f)", ball1.getVel().x, ball1.getVel().y);
        screen->Print(buffer, 10, 50, 0xff0000);

        // Collision status
        if (ball1.checkCollision(ball2))
            screen->Print("Collision: YES", 10, 40, 0x00ff00);
        else
            screen->Print("Collision: NO", 10, 40, 0xff0000);
    }

    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Converts deltaTime to seconds because it's in ms by default.

        // Apply gravity.
        {
            vec2 vel1 = ball1.getVel();
            vel1 += GRAVITY * deltaTime;
            // Other velocity..
            ball1.setVel(vel1);
        }

        // Update
        ball1.update(deltaTime);
        ball2.update(deltaTime);

        // Apply constraints.

        // Ground constraint.
        {
            vec2 pos = ball1.getPos();
            vec2 vel = ball1.getVel();
            const float r = ball1.getRadius();

            // Test collision with the bottom of the screen.
            if (pos.y > ScreenHeight - r)
            {
                pos.y = ScreenHeight - r - 1;
                vel.y *= -0.50f; // How much velocity it loses per bounce.
            }
            // Test collision with the right side of the screen.
            if (pos.x < r)
            {
                pos.x = r;
            }
            else if (pos.x > ScreenWidth - r)
            {
                pos.x = ScreenWidth - r - 1;
            }

            // Update ball.
            ball1.setPos(pos);
            ball1.setVel(vel);
        }

        // Ball collision.
        if (ball1.checkCollision(ball2))
        {
            // Norm
            vec2 vel = ball1.getVel();
            float norm_vel = sqrt(pow(vel.x, 2) + pow(vel.y, 2));

            // Angle
            float radii = ball1.getRadius() + ball2.getRadius();
            if (ball1.getPos().x <= ball2.getPos().x)
            {
                radii *= -1;
            }

            float adjacent = abs(ball1.getPos().y - ball2.getPos().y);
            float angle = acos(adjacent / radii);

            vel.x = norm_vel * cos(angle);
            vel.y = -norm_vel * sin(angle);
            ball1.setVel(vel);
        }

        // Draw
        screen->Clear(0);

        ball1.draw(screen);
        ball2.draw(screen);

        // Debug
        DrawDebugInfo(screen, ball1, ball2);
    }
};
*/
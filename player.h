#pragma once
#include "surface.h"
#include "tilemap.h"
#include "collectible.h"
#include <unordered_map>
#include "camera.h"

namespace Tmpl8
{
    extern Sprite player_img;
    extern int hitbox_size;
    extern int player_img_width;
    extern int player_img_height;

    class TileMap;

    class Player {
    public:
        Player(TileMap& mapRef, Camera& cameraRef);
        vec2 velocity = { 0, 0 };
        vec2 position = { 0, 0 };
        vec2 default_pos = { 0, 0 };

        TileType CheckCollisionBottom(const vec2& pos);
        TileType CheckCollisionSides(const vec2& pos);
        void movePlayer(vec2& new_pos);
        bool manageCollisions(vec2& new_pos, Surface* screen, CollectibleMap* collectibles);
        void getPlayerPos(vec2& pos);
        void setPlayerPos(const vec2& pos);
        void setPlayerDefaultPos(const vec2& pos);
        void getPlayerDefaultPos(vec2& pos);
        vec2 camFollowPlayer();
        void manageDefaultPos(int index);
        void rotatePlayer(Surface* screen, float deltaTime);
    private:
        TileMap& tilemap;
        Camera& camera;
        float gravity = 0.5f;
        float vertical_speed = 0;
        float horizontal_speed = 0;
        float friction = 0.05f;
        float wall_force = 7.0f;
        float rotation_speed = 90.0f;
        const float ENERGY_LOSS = 0.15f;
        const float ACCELERATION = 0.3f;
        const float MAX_HORIZONTAL_SPEED = 3.0f;
    };
}

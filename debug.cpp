//#define WIN32_LEAN_AND_MEAN
//#include "debug.h"
//#include "surface.h"
//#include "windows.h"
//#include "player.h"
//#include "tilemap.h"
//#include "game.h"
//#include "tile.h"
//#include "camera.h"
//#include <stdio.h>
//
//namespace Tmpl8
//{
//    // Debug functions
//    void Debug::drawHitbox(int x, int y, Surface* screen)
//    {
//        int squareTop = y + player_img_width / 2 - hitbox_size + cam_offset_y;
//        int squareRight = x + player_img_width / 2 + hitbox_size + cam_offset_x;
//        int squareBottom = y + player_img_width / 2 + hitbox_size + cam_offset_y;
//        int squareLeft = x + player_img_width / 2 - hitbox_size + cam_offset_x;
//
//        screen->Box(squareLeft, squareTop, squareRight, squareBottom, 0xFF0000);
//    }
//
//    void Debug::displayDebug(Surface* screen)
//    {
//        if (GetAsyncKeyState(VK_SPACE))
//        {
//            // PRESS <R> : Teleports player back to default position of the level.
//            if (GetAsyncKeyState('R') & 0x8000) defaultPos();
//
//            // PRESS <TAB> : Switches to the next level.
//            nextDebugMap();
//
//            // Display the player's hitbox
//            drawHitbox(px, py, screen);
//
//            // Display "debug active"
//            char debug_active_coords[100];
//            sprintf(debug_active_coords, "-- DEBUG MODE --");
//            screen->Print(debug_active_coords, 10, 10, 0x00FF00);
//
//            // Display the player's screen coordinates
//            char player_pos_coords[100];
//            sprintf(player_pos_coords, "px: %d, py: %d", px, py);
//            screen->Print(player_pos_coords, 10, 30, 0xFFFF00);
//
//            // Display the current map level alongside its default spawn coordinates
//            char map_lvl_coords[100];
//            sprintf(map_lvl_coords, "current map: %d - (%d, %d)", map.getCurrentLevel(), spawn_px, spawn_py);
//            screen->Print(map_lvl_coords, 10, 50, 0xFFFF00);
//        }
//    }
//
//    void Debug::defaultPos()
//    {
//        Player player;
//        int x = spawn_px;
//        int y = spawn_py;
//        player.setPlayerPos(x, y);
//    }
//
//    bool tabPressedLastFrame = false;
//
//    void Debug::nextDebugMap()
//    {
//        bool isTabDown = GetAsyncKeyState(VK_TAB) & 0x8000;
//        if (isTabDown && !tabPressedLastFrame)
//        {
//            map.setMapIndex(map.incrementMapIndex());
//            defaultPos();
//        }
//        tabPressedLastFrame = isTabDown;
//    }
//};

//#include "tile_old.h"
//
//namespace Tmpl8
//{
//    // Variables
//    //Surface img_tilemap("assets/images/map/img_tilemap.png");
//    //const int IMG_TILEMAP_WIDTH = img_tilemap.GetWidth();
//    
//    //// Tile functions
//    //void DrawTile(Surface* screen, int x, int y, const Camera& camera)
//    //{
//    //    Pixel* src = img_tilemap.GetBuffer() + tx * TILE_SIZE + ty * TILE_SIZE * IMG_TILEMAP_WIDTH;
//    //    Pixel* dst = screen->GetBuffer();
//    //
//    //    for (int yl = 0; yl < TILE_SIZE; yl++)
//    //    {
//    //        for (int xl = 0; xl < TILE_SIZE; xl++) 
//    //        {
//    //            // Cut out of the screen pixels
//    //            int x_t = x + xl + camera.getCamPos().x;
//    //            int y_t = y + yl + camera.getCamPos().y;
//    //
//    //            if (x_t < SCREEN_WIDTH && x_t > 0 && y_t < SCREEN_HEIGHT && y_t > 0) {
//    //                dst[x_t + y_t * SCREEN_WIDTH] = src[xl + yl * IMG_TILEMAP_WIDTH];
//    //            }
//    //        }
//    //    }
//    //}
//};
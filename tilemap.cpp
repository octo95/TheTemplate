#include "tilemap.h"

namespace Tmpl8
{
    Sprite img_map1_data_read(new Surface("assets/images/map/data_read/img_map1_data_read.png"), 1);
    Sprite img_map1_draw(new Surface("assets/images/map/draw/img_map1_draw.png"), 1);
    Sprite img_map1_draw_bg(new Surface("assets/images/map/draw/img_map1_draw_bg.png"), 1);

    Sprite img_map2_data_read(new Surface("assets/images/map/data_read/img_map2_data_read.png"), 1);
    Sprite img_map2_draw(new Surface("assets/images/map/draw/img_map2_draw.png"), 1);
    Sprite img_map2_draw_bg(new Surface("assets/images/map/draw/img_map2_draw_bg.png"), 1);

    Sprite img_map3_data_read(new Surface("assets/images/map/data_read/img_map3_data_read.png"), 1);
    Sprite img_map3_draw(new Surface("assets/images/map/draw/img_map3_draw.png"), 1);
    Sprite img_map3_draw_bg(new Surface("assets/images/map/draw/img_map3_draw_bg.png"), 1);

    Sprite img_map4_data_read(new Surface("assets/images/map/data_read/img_map4_data_read.png"), 1);
    Sprite img_map4_draw(new Surface("assets/images/map/draw/img_map4_draw.png"), 1);
    Sprite img_map4_draw_bg(new Surface("assets/images/map/draw/img_map4_draw_bg.png"), 1);

    Sprite img_map5_data_read(new Surface("assets/images/map/data_read/img_map5_data_read.png"), 1);
    Sprite img_map5_draw(new Surface("assets/images/map/draw/img_map5_draw.png"), 1);
    Sprite img_map5_draw_bg(new Surface("assets/images/map/draw/img_map5_draw_bg.png"), 1);

    //Sprite img_cloud(new Surface("assets/images/map/img_cloud.png"), 1);

    void TileMap::loadMap(int index)
    {
        Sprite* maps_data[5] = {
            &img_map1_data_read,
            &img_map2_data_read,
            &img_map3_data_read,
            &img_map4_data_read,
            &img_map5_data_read,
        };
        Sprite* maps_draw[5] = {
            &img_map1_draw,
            &img_map2_draw,
            &img_map3_draw,
            &img_map4_draw,
            &img_map5_draw,
        };
        Sprite* maps_draw_bg[5] = {
            &img_map1_draw_bg,
            &img_map2_draw_bg,
            &img_map3_draw_bg,
            &img_map4_draw_bg,
            &img_map5_draw_bg,
        };

        current_map_data_read = maps_data[index-1];
        current_map_draw = maps_draw[index-1];
        current_map_draw_bg = maps_draw_bg[index - 1];
        current_level = index;

        // Load collision
        this->readImageToMap(current_map_data_read);
    }

    void TileMap::readImageToMap(Sprite* image) {
        Pixel* src = image->GetBuffer();
        size_t width = static_cast<size_t>(image->GetWidth());
        size_t height = static_cast<size_t>(image->GetHeight());
        std::unordered_map<vec2, TileType> new_map = std::unordered_map<vec2, TileType>{};

        for ( size_t y = 0; y < height; y += static_cast<size_t>(TILE_SIZE) ) 
        {
            for ( size_t x = 0; x < width; x += static_cast<size_t>(TILE_SIZE) ) 
            {

                TileType type = TileType::Ice;
                Pixel p = src[(y * width) + x];
                if (p == 0xFFFF0000) type = TileType::Damage;    // Red      (Damage)
                if (p == 0xFF00FF00) type = TileType::End;       // Green    (End)
                if (p == 0xFF0000FF) type = TileType::Collision; // Blue     (Collision)
                if (p == 0xFF000000) type = TileType::None;      // Black    (None)
                if (p == 0xFFFFDE00) type = TileType::Ice;       // Cyan     (Ice)

                new_map.insert({ vec2{(float)x,(float)y}, type });
            }
        }
        map_collision = new_map;
    }
}

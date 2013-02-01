#include <iostream>
#include "phoboz/map.h"

bool Map::load(Tmx::Map *tmx)
{
    bool result = true;

    // Load tile sprites for each tileset
    for (int i = 0; i < tmx->GetNumTilesets(); i++) {
        const Tmx::Tileset *tileset = tmx->GetTileset(i);
        Sprite *tiles = new Sprite(tileset->GetImage()->GetSource().c_str(),
                                   tileset->GetTileWidth(),
                                   tileset->GetTileHeight(),
                                   tileset->GetMargin(), tileset->GetSpacing());
        if (tiles->get_loaded()) {
            m_tiles.push_back(tiles);
        }
        else {
            result = false;
            break;
        }

    }

    if (result) {
        m_tmx = tmx;
    }

    m_loaded = result;

    return m_loaded;
}

int Map::get_tile_id(int x, int y, int layer_id) const
{
    const Tmx::Layer *layer = m_tmx->GetLayer(layer_id);
    int tw = m_tiles[0]->get_width();
    int th = m_tiles[0]->get_height();
    int col = x / tw;
    int row = y / th;
    return layer->GetTileId(col, row);
}

void Map::set_x(int value)
{
    m_x = value;
    if (m_x < 0) {
        m_x = 0;
    }
}

void Map::set_y(int value)
{
    m_y = value;
    if (m_y < 0) {
        m_x = 0;
    }
}

void Map::draw_layer(SDL_Surface *dest, int x, int y, int w, int h, int layer_id) const
{
    const Tmx::Layer *layer = m_tmx->GetLayer(layer_id);
    int tw = m_tiles[0]->get_width();
    int th = m_tiles[0]->get_height();

    int j = y - m_y % th;
    for(int row = m_y / th; ; row++) {

        int i = x - m_x % tw;
        for(int col = m_x / tw; ; col++) {

            int tile_id = layer->GetTileId(col, row);
            if(tile_id) {
                const Sprite *tiles = m_tiles[get_tileset_index(tile_id)];
                tiles->draw(dest, i, j, tile_id, x, y, w, h);
            }

            // Advance anlong x-axis
            i += tw;
            if (i >= w) {
                break;
            }

        }

        // Advance along y-axis
        j += th;
        if (j >= h) {
            break;
        }

    }
}


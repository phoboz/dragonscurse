#include <string.h>
#include "phoboz/map.h"

Map::Map(Tmx::Map *tmx, const char *prefix)
    : m_loaded(false),
      m_x(0), m_y(0)
{
    std::string pathname = tmx->GetFilename();
    m_filename = pathname.substr(strlen(prefix));
    load(tmx, prefix);
}

Map::~Map()
{
    // TODO: Free resource
    m_loaded = false;
}

bool Map::load(Tmx::Map *tmx, const char *prefix)
{
    bool result = true;

    // Load tile sprites for each tileset
    for (int i = 0; i < tmx->GetNumTilesets(); i++) {
        const Tmx::Tileset *tileset = tmx->GetTileset(i);
        std::string pathname = std::string(prefix) +
                               tileset->GetImage()->GetSource();
        Sprite *tiles = new Sprite(pathname.c_str(),
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
    int result = 0;

    const Tmx::Layer *layer = m_tmx->GetLayer(layer_id);
    int tw = m_tmx->GetTileWidth();
    int th = m_tmx->GetTileHeight();
    int col = x / tw;
    int row = y / th;

    if (col >= 0 && col < m_tmx->GetWidth() &&
        row >= 0 && row < m_tmx->GetHeight()) {
        result = layer->GetTileId(col, row);
    }

    return result;
}

void Map::set_tile_id(int x, int y, int layer_id, int id)
{
    // Hack, not nice to cast from const to non const
    // TODO: Add method to retreive non const layer
    Tmx::Layer *layer = (Tmx::Layer *) m_tmx->GetLayer(layer_id);
    int tw = m_tmx->GetTileWidth();
    int th = m_tmx->GetTileHeight();
    int col = x / tw;
    int row = y / th;

    if (col >= 0 && col < m_tmx->GetWidth() &&
        row >= 0 && row < m_tmx->GetHeight()) {
        layer->SetTileId(col, row, id);
    }
}

void Map::set_x(int value, int window_width)
{
    int max_width = m_tmx->GetTileWidth() * m_tmx->GetWidth() - window_width;

    m_x = value;
    if (m_x < 0) {
        m_x = 0;
    }
    if (m_x > max_width) {
        m_x = max_width;
    }
}

void Map::set_y(int value, int window_height)
{
    int max_height = m_tmx->GetTileHeight() * m_tmx->GetHeight() - window_height;

    m_y = value;
    if (m_y < 0) {
        m_x = 0;
    }
    if (m_y > max_height) {
        m_y = max_height;
    }
}

int Map::get_numeric_property(const std::string &name) const
{
    const Tmx::PropertySet prop = m_tmx->GetProperties();

    return prop.GetNumericProperty(name);
}

std::string Map::get_literal_property(const std::string &name) const
{
    const Tmx::PropertySet prop = m_tmx->GetProperties();

    return prop.GetLiteralProperty(name);
}

void Map::draw_layer(SDL_Surface *dest, int x, int y, int w, int h, int layer_id) const
{
    const Tmx::Layer *layer = m_tmx->GetLayer(layer_id);
    int tw = m_tmx->GetTileWidth();
    int th = m_tmx->GetTileHeight();

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


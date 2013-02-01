#ifndef _Map_H
#define _Map_H

#include <vector>
#include "SDL.h"
#include "Tmx/Tmx.h"
#include "Tmx/TmxLayer.h"
#include "phoboz/sprite.h"

class Map {
public:
    Map(Tmx::Map *tmx) : m_loaded(false), m_x(0), m_y(0) { load(tmx); }
    ~Map() { }
    bool load(Tmx::Map *tmx);
    bool get_loaded() const { return m_loaded; }
    int get_num_tilesets() const { return m_tiles.size(); }
    const Sprite* get_tileset(int index) const { return m_tiles[index]; }
    int get_tile_id(int x, int y, int layer_id) const;
    void set_x(int value);
    void set_y(int value);
    int get_x() const { return m_x; }
    int get_y() const { return m_y; }
    void draw_layer(SDL_Surface *dest, int x, int y, int w, int h, int layer_id) const;

private:
    int get_tileset_index(int index) const { return m_tmx->FindTilesetIndex(index); }
    bool m_loaded;
    int m_x, m_y;
    Tmx::Map *m_tmx;
    std::vector<const Sprite*> m_tiles;
};

#endif


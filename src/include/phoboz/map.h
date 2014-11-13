#ifndef _Map_H
#define _Map_H

#include <vector>
#include <string>
#include "Tmx/Tmx.h"
#include "Tmx/TmxLayer.h"
#include "Tmx/TmxTileset.h"
#include "Tmx/TmxObjectGroup.h"
#include "phoboz/sprite.h"

class Map {
public:
    Map(Tmx::Map *tmx, const char *prefix);
    ~Map();
    bool load(Tmx::Map *tmx, const char *prefix);
    bool get_loaded() const { return m_loaded; }
    int get_tile_id(int x, int y, int layer_id) const;
    void set_tile_id(int x, int y, int layer_id, int id);
    void set_x(int value, int window_width);
    void set_y(int value, int window_height);
    const char* get_filename() const { return m_filename.c_str(); }
    int get_x() const { return m_x; }
    int get_y() const { return m_y; }
    int get_tile_width() const { return m_tmx->GetTileWidth(); }
    int get_tile_height() const { return m_tmx->GetTileHeight(); }
    int get_num_layers() const { return m_tmx->GetNumLayers(); }
    int get_tileset_index(int index) const { return m_tmx->FindTilesetIndex(index); }
    int get_num_tilesets() const { return m_tmx->GetNumTilesets(); }
    const Tmx::Tileset* get_tileset(int index) const {
        return m_tmx->GetTileset(index);
    }
    int get_num_object_groups() const { return m_tmx->GetNumObjectGroups(); }
    const Tmx::ObjectGroup* get_object_group(int index) const {
        return m_tmx->GetObjectGroup(index);
    }
    int get_numeric_property(const std::string &name) const;
    std::string get_literal_property(const std::string &name) const;
    void draw_layer(Surface *dest, int x, int y, int w, int h, int layer_id) const;

private:
    bool m_loaded;
    int m_x, m_y;
    Tmx::Map *m_tmx;
    std::vector<const Sprite*> m_tiles;
    std::string m_filename;
};

#endif


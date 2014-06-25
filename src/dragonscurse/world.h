#ifndef _World_H
#define _World_H

#include <list>
#include "SDL.h"
#include "SDL_mixer.h"
#include "phoboz/map.h"
#include "object.h"
#include "player.h"
#include "area.h"
#include "world_db.h"

class World {
public:
    World(Map *map, WorldDB *db, bool load_music = true);

    WorldDB* get_db() const { return m_db; }
    const char* get_filename() const { return m_map->get_filename().c_str(); }

    bool start();
    void end();
    Area* move(Player *player,
               int clip_x, int clip_y, int clip_w, int clip_h);
    void draw(SDL_Surface *dest, Player *player,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    Map *m_map;
    int m_bg_color;
    Mix_Music *m_music;
    std::list<Object*> m_objects;
    WorldDB *m_db;
};

#endif


#ifndef _World_H
#define _World_H

#include <list>
#include "SDL.h"
#include "phoboz/map.h"
#include "object.h"
#include "player.h"

class World {
public:
    World(Map *map, int object_group);
    void move(Player *player,
              int clip_x, int clip_y, int clip_w, int clip_h);
    void draw(SDL_Surface *dest, Player *player,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    Map *m_map;
    int m_bg_color;
    std::list<Object*> m_objects;
};

#endif


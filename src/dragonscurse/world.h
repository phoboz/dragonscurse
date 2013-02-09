#ifndef _World_H
#define _World_H

#include <vector>
#include "SDL.h"
#include "phoboz/map.h"
#include "object.h"
#include "player.h"

class World {
public:
    World(Map *map, int object_group);
    void move(Player *player, int window_width, int window_height);
    void draw(SDL_Surface *dest, Player *player,
              int clip_x, int clip_y, int clip_w, int clip_h);

private:
    Map *m_map;
    std::vector<Object*> m_objects;
};

#endif


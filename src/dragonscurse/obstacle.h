#ifndef _Obstacle_H
#define _Obstacle_H

#include "monster.h"

class Obstacle : public Monster {
public:
    Obstacle(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir) { set_recursive_hit(false); }
    virtual void move(Map *map);
};

#endif


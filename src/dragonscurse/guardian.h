#ifndef _Guardian_H
#define _Guardian_H

#include "actor.h"

class Guardian : public Actor {
public:
    Guardian(const char *fn, int x, int y, Direction dir)
        : Actor(Object::TypeEnemy, x, y, dir) { load(fn); }
    virtual void move(Map *map);
};

#endif


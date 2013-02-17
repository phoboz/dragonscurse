#ifndef _Walker_H
#define _Walker_H

#include "phoboz/timer.h"
#include "actor.h"

class Walker : public Actor {
public:
    Walker(const char *fn, int x, int y, Direction dir)
        : Actor(Object::TypeEnemy, x, y, dir) { load(fn); }
    virtual void move(Map *map);

private:
    Timer m_hit_timer;
};

#endif


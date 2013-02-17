#ifndef _Guardian_H
#define _Guardian_H

#include "phoboz/timer.h"
#include "actor.h"

class Guardian : public Actor {
public:
    Guardian(const char *fn, int x, int y, Direction dir)
        : Actor(Object::TypeEnemy, x, y, dir) { load(fn); }
    virtual void set_hit(Object *object);
    virtual void move(Map *map);

private:
    Timer m_hit_timer;
};

#endif


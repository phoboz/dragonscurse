#ifndef _Monster_H
#define _Monster_H

#include "phoboz/timer.h"
#include "actor.h"

class Monster : public Actor {
public:
    Monster(const char *fn, int x, int y, Direction dir);
    virtual bool set_hit(Object *object);
    virtual void move(Map *map);

private:
    int m_curr_hp;
    Timer m_perish_timer;
};

#endif


#ifndef _Monster_H
#define _Monster_H

#include "actor.h"

class Monster : public Actor {
public:
    Monster(const char *fn, int x, int y, Direction dir);
    virtual bool set_hit(Object *object);

private:
    int m_curr_hp;
};

#endif


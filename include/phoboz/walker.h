#ifndef _Walker_H
#define _Walker_H

#include "phoboz/actor.h"

class Walker : public Actor {
public:
    Walker(const char *fn, int x, int y, Direction dir);
    virtual void move(Map *map);
};

#endif


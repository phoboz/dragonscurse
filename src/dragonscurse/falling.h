#ifndef _Falling_H
#define _Falling_H

#include "monster.h"

class Falling : public Monster {
public:
    Falling(const char *fn, int x, int y, Direction dir)
        : Monster(fn, x, y, dir) { set_invinsible(true); }
    virtual void move(Map *map);
};

#endif


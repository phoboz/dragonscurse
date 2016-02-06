#ifndef _Trap_H
#define _Trap_H

#include "monster.h"

class Trap : public Monster {
public:
    Trap(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir) { }
    virtual bool set_hit(Object *object, Status *status);
    virtual void move(Map *map);
};

#endif


#ifndef _Swimmer_H
#define _Swimmer_H

#include "phoboz/timer.h"
#include "floater.h"

class Swimmer : public Floater {
public:
    Swimmer(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Floater(fn, media, x, y, dir) { }

    virtual void world_initialize(World *world);
};

#endif


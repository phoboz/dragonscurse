#ifndef _Natator_H
#define _Natator_H

#include "phoboz/timer.h"
#include "flyer.h"

class Natator : public Flyer {
public:
    Natator(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Flyer(fn, media, x, y, dir) { }

private:
    virtual bool in_medium(Map *map);
};

#endif


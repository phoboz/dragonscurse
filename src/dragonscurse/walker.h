#ifndef _Walker_H
#define _Walker_H

#include "phoboz/timer.h"
#include "monster.h"

class Walker : public Monster {
public:
    Walker(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir) { }
    virtual void move(Map *map);

private:
    Timer m_hit_timer;
};

#endif


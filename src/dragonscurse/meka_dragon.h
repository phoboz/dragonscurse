#ifndef _MekaDragon_H
#define _MekaDragon_H

#include "phoboz/timer.h"
#include "monster.h"

class MekaDragon : public Monster {
public:
    MekaDragon(const char *fn, int x, int y, Direction dir)
        : Monster(fn, x, y, dir) { }
    virtual void move(Map *map);

private:
    Timer m_hit_timer;
};

#endif


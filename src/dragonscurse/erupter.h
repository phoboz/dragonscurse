#ifndef _Erupter_H
#define _Erupter_H

#include "phoboz/timer.h"
#include "monster.h"

class Erupter : public Monster {
public:
    Erupter(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir) { }
    virtual void move(Map *map);

private:
    Timer m_attack_timer;
    Timer m_jump_timer;
    Timer m_hit_timer;
};

#endif


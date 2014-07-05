#ifndef _Dancer_H
#define _Dancer_H

#include "phoboz/timer.h"
#include "monster.h"

class Dancer : public Monster {
public:
    Dancer(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir) { }
    virtual void move(Map *map);

private:
    Timer m_attack_timer;
    Timer m_jump_timer;
    Timer m_hit_timer;
};

#endif


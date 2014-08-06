#ifndef _Swimmer_H
#define _Swimmer_H

#include "phoboz/timer.h"
#include "monster.h"

class Swimmer : public Monster {
public:
    Swimmer(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir) { }

    virtual void move(Map *map);

private:
    Timer m_attack_timer;
    int m_lock_x, m_lock_y;
};

#endif


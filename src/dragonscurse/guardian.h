#ifndef _Guardian_H
#define _Guardian_H

#include "phoboz/timer.h"
#include "monster.h"

class Guardian : public Monster {
public:
    Guardian(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir) { }
    virtual void move(Map *map);

private:
    Timer m_attack_timer;
};

#endif


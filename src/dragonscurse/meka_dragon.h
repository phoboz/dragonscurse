#ifndef _MekaDragon_H
#define _MekaDragon_H

#include "phoboz/timer.h"
#include "monster.h"
#include "bullet.h"

class MekaDragon : public Monster {
public:
    MekaDragon(const char *fn, int x, int y, Direction dir);
    virtual void move(Map *map);

private:
    Timer m_hit_timer;
    Bullet *m_bullet;
};

#endif


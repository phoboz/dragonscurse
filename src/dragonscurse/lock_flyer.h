#ifndef _LockFlyer_H
#define _LockFlyer_H

#include "phoboz/timer.h"
#include "monster.h"

class LockFlyer : public Monster {
public:
    LockFlyer(const char *fn, int x, int y, Direction dir)
        : Monster(fn, x, y, dir),
          m_vertical_dir(Object::VerticalNone) { }
    virtual void move(Map *map);

private:
    Object::VerticalDirection m_vertical_dir;
    int m_lock_y;
    Timer m_attack_timer;
    Timer m_hit_timer;
};

#endif


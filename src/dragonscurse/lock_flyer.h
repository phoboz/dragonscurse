#ifndef _LockFlyer_H
#define _LockFlyer_H

#include "phoboz/timer.h"
#include "monster.h"

class LockFlyer : public Monster {
public:
    enum VerticalDirection { VerticalNone,
                             VerticalUp, VerticalDown,
                             VerticalDone };
    LockFlyer(const char *fn, int x, int y, Direction dir)
        : Monster(fn, x, y, dir),
          m_vertical_dir(VerticalNone) { }
    virtual void move(Map *map);

private:
    VerticalDirection m_vertical_dir;
    int m_lock_y;
    Timer m_attack_timer;
    Timer m_hit_timer;
};

#endif


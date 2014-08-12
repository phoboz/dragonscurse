#ifndef _Floater_H
#define _Floater_H

#include "phoboz/timer.h"
#include "monster.h"

class Floater : public Monster {
public:
    Floater(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir),
          m_start_env(0), m_end_env(0) { }

    virtual void move(Map *map);

private:
    bool check_env(Map *map);

    int m_start_env, m_end_env;
    Timer m_attack_timer;
    int m_lock_x, m_lock_y;
};

#endif


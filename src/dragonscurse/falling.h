#ifndef _Falling_H
#define _Falling_H

#include "phoboz/timer.h"
#include "monster.h"

class Falling : public Monster {
public:
    Falling(const char *fn, int x, int y, Direction dir);
    virtual void move(Map *map);

private:
    void fall();

    int m_fall_distance;
    Timer m_trigger_timer;
};

#endif


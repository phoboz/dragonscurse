#ifndef _Diver_H
#define _Diver_H

#include "phoboz/timer.h"
#include "monster.h"

class Diver : public Monster {
public:
    Diver(const char *fn, MediaDB *media, int x, int y, Direction dir);
    virtual void move(Map *map);

private:
    int m_y0;
    bool m_flying;
    Timer m_dive_timer;
};

#endif


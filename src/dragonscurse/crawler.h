#ifndef _Crawler_H
#define _Crawler_H

#include "phoboz/timer.h"
#include "monster.h"

class Crawler : public Monster {
public:
    Crawler(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir), m_hit_ground(false) { }

    void check_ground(Map *map);

    virtual void move(Map *map);

private:
    bool m_hit_ground;
    Timer m_hit_timer;
};

#endif


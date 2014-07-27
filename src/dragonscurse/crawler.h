#ifndef _Crawler_H
#define _Crawler_H

#include "monster.h"

class Crawler : public Monster {
public:
    Crawler(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir) { }

    void check_ground(Map *map);

    virtual void move(Map *map);
};

#endif


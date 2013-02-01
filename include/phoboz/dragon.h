#ifndef _Dragon_H
#define _Dragon_H

#include "phoboz/player.h"

class Dragon : public Player {
public:
    Dragon(const char *fn) : Player(fn) { }
    virtual void move(Map *map);
};

#endif


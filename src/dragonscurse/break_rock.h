#ifndef _BreakRock_H
#define _BreakRock_H

#include "collectable.h"

class BreakRock : public Collectable {
public:
    BreakRock(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeBreakRock, fn, media, x, y) { set_value(1); }

private:
};

#endif


#ifndef _Stone_H
#define _Stone_H

#include "collectable.h"

class Stone : public Collectable {
public:
    Stone(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeStone, fn, media, x, y) { set_value(1); }

private:
};

#endif


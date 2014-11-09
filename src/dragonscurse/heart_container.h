#ifndef _HeartContainer_H
#define _HeartContainer_H

#include "collectable.h"

class HeartContainer : public Collectable {
public:
    HeartContainer(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeHeartContainer, fn, media, x, y) { set_value(1); }

private:
};

#endif


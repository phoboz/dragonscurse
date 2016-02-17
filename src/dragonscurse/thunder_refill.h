#ifndef _ThunderRefill_H
#define _ThunderRefill_H

#include "collectable.h"

class ThunderRefill : public Collectable {
public:
    ThunderRefill(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeThunderRefill, fn, media, x, y) { set_value(1); }

private:
};

#endif


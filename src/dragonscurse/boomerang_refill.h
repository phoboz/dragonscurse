#ifndef _BoomerangRefill_H
#define _BoomerangRefill_H

#include "collectable.h"

class BoomerangRefill : public Collectable {
public:
    BoomerangRefill(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeBoomerangRefill, fn, media, x, y) { set_value(1); }

private:
};

#endif


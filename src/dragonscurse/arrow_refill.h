#ifndef _ArrowRefill_H
#define _ArrowRefill_H

#include "collectable.h"

class ArrowRefill : public Collectable {
public:
    ArrowRefill(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeArrowRefill, fn, media, x, y) { set_value(1); }

private:
};

#endif


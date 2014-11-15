#ifndef _HeartRefill_H
#define _HeartRefill_H

#include "collectable.h"

class HeartRefill : public Collectable {
public:
    HeartRefill(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeHeartRefill, fn, media, x, y) {
        set_value(get_attribute("max_value"));
    }

private:
};

#endif


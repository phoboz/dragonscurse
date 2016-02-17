#ifndef _FireRefill_H
#define _FireRefill_H

#include "collectable.h"

class FireRefill : public Collectable {
public:
    FireRefill(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeFireRefill, fn, media, x, y) { set_value(1); }

private:
};

#endif


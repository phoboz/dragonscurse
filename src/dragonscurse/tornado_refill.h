#ifndef _TornadoRefill_H
#define _TornadoRefill_H

#include "collectable.h"

class TornadoRefill : public Collectable {
public:
    TornadoRefill(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeTornadoRefill, fn, media, x, y) { set_value(1); }

private:
};

#endif


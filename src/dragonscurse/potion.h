#ifndef _Potion_H
#define _Potion_H

#include "collectable.h"

class Potion : public Collectable {
public:
    Potion(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypePotion, fn, media, x, y) { set_value(1); }

private:
};

#endif


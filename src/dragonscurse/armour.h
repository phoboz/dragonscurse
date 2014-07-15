#ifndef _Armour_H
#define _Armour_H

#include "item.h"

class Armour : public Item  {
public:
    Armour(const char *fn, MediaDB *media, int x, int y)
        : Item(TypeArmour, fn, media, x, y) { }
};

#endif


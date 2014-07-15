#ifndef _Sword_H
#define _Sword_H

#include "item.h"

class Sword : public Item  {
public:
    Sword(const char *fn, MediaDB *media, int x, int y)
        : Item(TypeSword, fn, media, x, y) { }
};

#endif


#ifndef _Shield_H
#define _Shield_H

#include "item.h"

class Shield : public Item  {
public:
    Shield(const char *fn, MediaDB *media, int x, int y)
        : Item(TypeShield, fn, media, x, y) { }
};

#endif


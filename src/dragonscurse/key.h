#ifndef _Key_H
#define _Key_H

#include "item.h"

class Key : public Item  {
public:
    Key(const char *fn, MediaDB *media, int x, int y)
        : Item(TypeKey, fn, media, x, y) { }
};

#endif


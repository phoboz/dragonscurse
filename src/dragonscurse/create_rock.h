#ifndef _CreateRock_H
#define _CreateRock_H

#include "collectable.h"

class CreateRock : public Collectable {
public:
    CreateRock(const char *fn, MediaDB *media, int x, int y)
        : Collectable(TypeCreateRock, fn, media, x, y) { set_value(1); }

private:
};

#endif


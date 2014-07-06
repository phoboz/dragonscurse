#ifndef _Coin_H
#define _Coin_H

#include "collectable.h"

class Coin : public Collectable {
public:
    Coin(const char *fn, MediaDB *media)
        : Collectable(fn, media) { }

private:
};

#endif


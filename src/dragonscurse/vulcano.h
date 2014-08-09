#ifndef _Vulcano_H
#define _Vulcano_H

#include <vector>
#include "phoboz/timer.h"
#include "monster.h"
#include "gravity_bullet.h"
#include "erupter.h"

class Vulcano : public Erupter {
public:
    Vulcano(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Erupter(fn, media, x, y, dir) { }

protected:
    virtual void fire();
};

#endif


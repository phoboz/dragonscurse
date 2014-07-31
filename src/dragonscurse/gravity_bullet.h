#ifndef _GravityBullet_H
#define _GravityBullet_H

#include "phoboz/timer.h"
#include "bullet.h"

class GravityBullet : public Bullet {
public:
    GravityBullet(const char *fn, MediaDB *media)
        : Bullet(fn, media) { set_solid(false); }

    virtual bool fire(int x, int y, int dx, int dy);
};

#endif


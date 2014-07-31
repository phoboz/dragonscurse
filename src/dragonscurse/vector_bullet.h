#ifndef _VectorBullet_H
#define _VectorBullet_H

#include "bullet.h"

class VectorBullet : public Bullet {
public:
    VectorBullet(const char *fn, MediaDB *media)
        : Bullet(fn, media) { }

    virtual bool fire(int x, int y, int dx, int dy);
};

#endif


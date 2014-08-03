#ifndef _SolidBullet_H
#define _SolidBullet_H

#include "bullet.h"

class SolidBullet : public Bullet {
public:
    SolidBullet(const char *fn, MediaDB *media);

    virtual bool fire(int x, int y, int dx, int dy);

    virtual void move(Map *map);

private:
    int m_speed;
};

#endif


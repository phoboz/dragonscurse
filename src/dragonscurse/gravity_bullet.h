#ifndef _GravityBullet_H
#define _GravityBullet_H

#include "phoboz/timer.h"
#include "bullet.h"

class GravityBullet : public Bullet {
public:
    GravityBullet(const char *fn, MediaDB *media)
        : Bullet(fn, media) { m_follow_terrain = false; }

    virtual void move(Map *map);

private:
    Timer m_rise_timer;
};

#endif


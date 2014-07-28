#ifndef _GravityBullet_H
#define _GravityBullet_H

#include "phoboz/timer.h"
#include "body.h"

class Actor;

class GravityBullet : public Body {
public:
    GravityBullet(const char *fn, MediaDB *media);
    bool fire(int x, int y, int dx, int dy);

    virtual bool get_moving() const;

    bool hit_actor(Actor *actor);

    void move(Map *map);

private:
    int m_distance;
};

#endif


#ifndef _GravityBullet_H
#define _GravityBullet_H

#include "phoboz/timer.h"
#include "body.h"

class GravityBullet : public Body {
public:
    GravityBullet(const char *fn, MediaDB *media);
    bool fire(int x, int y, int dx, int dy);

    virtual bool get_moving() const;

    bool hit_object(Object *object);

    void move(Map *map);

private:
    int m_distance;
};

#endif


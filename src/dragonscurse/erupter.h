#ifndef _Erupter_H
#define _Erupter_H

#include <vector>
#include "phoboz/timer.h"
#include "monster.h"
#include "gravity_bullet.h"

class Erupter : public Monster {
public:
    Erupter(const char *fn, MediaDB *media, int x, int y, Direction dir);

    virtual bool attack_object(Object *object);

    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const;

    virtual void move(Map *map);

    virtual void draw(Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    virtual void fire();

    Timer m_attack_timer;
    std::vector<GravityBullet*> m_bullets;
};

#endif


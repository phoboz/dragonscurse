#ifndef _Erupter_H
#define _Erupter_H

#include <list>
#include "phoboz/timer.h"
#include "monster.h"
#include "gravity_bullet.h"

class Erupter : public Monster {
public:
    Erupter(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Monster(fn, media, x, y, dir) { }

    virtual bool attack_object(Object *object);

    virtual void move(Map *map);

    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    void fire();

    Timer m_attack_timer;
    std::list<GravityBullet*> m_bullets;
};

#endif


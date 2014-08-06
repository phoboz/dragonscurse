#ifndef _Hovering_H
#define _Hovering_H

#include <vector>
#include "phoboz/timer.h"
#include "monster.h"
#include "solid_bullet.h"

class Hovering : public Monster {
public:
    Hovering(const char *fn, MediaDB *media, int x, int y, int w,
             Direction dir);

    bool attack_object(Object *object);

    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const;

    virtual void move(Map *map);

    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    void fire();

    int m_x0, m_x1;
    Timer m_attack_timer;
    std::vector<SolidBullet*> m_bullets;
};

#endif


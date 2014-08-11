#ifndef _Crawler_H
#define _Crawler_H

#include "phoboz/timer.h"
#include "monster.h"
#include "vector_bullet.h"

class Crawler : public Monster {
public:
    Crawler(const char *fn, MediaDB *media, int x, int y, Direction dir);

    virtual bool attack_object(Object *object);

    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const;

    virtual void move(Map *map);

    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);

private:
    void check_ground(Map *map);
    void fire();

    std::vector<VectorBullet*> m_bullets;
    Timer m_attack_timer;
};

#endif


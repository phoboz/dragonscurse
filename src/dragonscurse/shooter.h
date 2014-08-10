#ifndef _Shooter_H
#define _Shooter_H

#include <vector>
#include "phoboz/timer.h"
#include "monster.h"
#include "vector_bullet.h"

class Shooter : public Monster {
public:
    Shooter(const char *fn, MediaDB *media, int x, int y, Direction dir);

    virtual bool attack_object(Object *object);

    virtual bool get_visible(Map *map, int clip_x, int clip_y,
                             int clip_w, int clip_h) const;

    virtual void move(Map *map);

    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h);
private:
    void fire();

    bool m_face_reference;
    std::vector<VectorBullet*> m_bullets;
    Timer m_attack_timer;
};

#endif


#ifndef _Bullet_H
#define _Bullet_H

#include "phoboz/object.h"

class Bullet : public Object {
public:
    Bullet(const char *fn)
        : Object(Object::Projectile),
          m_moving(false) { load(fn); }
    void fire(int x, int y, Direction dir);
    virtual void move(Map *map);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h) const {
        if (m_moving) Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }

private:
    bool m_moving;
};

#endif


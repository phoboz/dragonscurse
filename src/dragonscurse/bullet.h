#ifndef _Bullet_H
#define _Bullet_H

#include "phoboz/timer.h"
#include "object.h"

class Bullet : public Object {
public:
    Bullet(const char *fn)
        : Object(Object::TypeBullet),
          m_moving(false), m_loaded(true),
          m_distance(0) { load(fn); }
    bool fire(int x, int y, Direction dir);
    virtual void move(Map *map);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h) const {
        if (m_moving) Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }

private:
    void reload();

    bool m_moving;
    bool m_loaded;
    int m_distance;
    Timer m_reload_timer;
};

#endif


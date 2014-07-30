#ifndef _Bullet_H
#define _Bullet_H

#include "phoboz/timer.h"
#include "object.h"

class Bullet : public Object {
public:
    Bullet(const char *fn, MediaDB *media)
        : Object(Object::TypeBullet),
          m_follow_terrain(true), m_moving(false), m_loaded(true),
          m_distance(0), m_hit_one(false) { load(fn, media); }

    void set_hit_one(bool value) { m_hit_one = value; }
    bool fire(int x, int y, int speed, Direction dir);
    bool fire(int x, int y, int dx, int dy);

    bool hit_object(Object *object);

    virtual void move(Map *map);
    virtual void draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h) {
        if (m_moving) Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }

protected:
    bool m_follow_terrain;
    VerticalDirection m_vertical_dir;

private:
    void reload();

    bool m_hit_one;
    bool m_moving;
    bool m_loaded;
    int m_distance;
    Timer m_reload_timer;
};

#endif


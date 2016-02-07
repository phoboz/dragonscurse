#ifndef _Roller_H
#define _Roller_H

#include "monster.h"

class Roller : public Monster {
public:
    Roller(const char *fn, MediaDB *media, int x, int y,
           const Tmx::Polyline *polyline)
        : Monster(fn, media, x, y, Right),
          m_polyline(polyline),
          m_curr_point(0),
          m_reverse(false),
          m_x0(x), m_y0(y) { set_solid(false); set_recursive_hit(false); }

    virtual bool set_hit(Object *object, Status *status);
    virtual void move(Map *map);

private:
    const Tmx::Polyline *m_polyline;
    int m_curr_point;
    bool m_reverse;
    int m_x0, m_y0;
    int m_tx, m_ty;

    void update_speed(void);
};

#endif


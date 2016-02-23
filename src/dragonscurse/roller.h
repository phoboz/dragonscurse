#ifndef _Roller_H
#define _Roller_H

#include "monster.h"

class Roller : public Monster {
public:
    Roller(const char *fn, MediaDB *media, int x, int y,
           const Tmx::Polyline *polyline);

    virtual bool set_hit(Object *object, Status *status, Map *map);
    virtual void move(Map *map);

private:
    const Tmx::Polyline *m_polyline;
    int m_curr_point;
    bool m_reverse;
    bool m_was_hit;
    int m_x0, m_y0;
    int m_tx, m_ty;
    int m_old_dx, m_old_dy;

    void next_point();
    void prev_point();
    void update_speed(Map *map);
};

#endif


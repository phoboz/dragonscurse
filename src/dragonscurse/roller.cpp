#include <math.h>
#include "roller.h"

bool Roller::set_hit(Object *object, Status *status)
{
    set_speed(0, 0);
    Monster::set_hit(object, status);
}

void Roller::update_speed()
{
    int x0 = m_polyline->GetPoint(m_curr_point).x + m_x0;
    int y0 = m_polyline->GetPoint(m_curr_point).y + m_y0;

    if (!m_reverse) {
        if (++m_curr_point == m_polyline->GetNumPoints() - 1) {
            m_reverse = true;
        }
    }
    else {
        if (--m_curr_point == 0) {
            m_reverse = false;
        }
    }

    int x1 = m_polyline->GetPoint(m_curr_point).x + m_x0;
    int y1 = m_polyline->GetPoint(m_curr_point).y + m_y0;

    float dx = x1 - x0;
    float dy = y1 - y0;

    float len = sqrt(dx * dx + dy * dy);
    dx /= len;
    dy /= len;

    int speed = get_attribute("move_speed");
    set_speed(dx * speed, dy * speed);

    m_tx = x1;
    m_ty = y1;

    set_action(Move);
}

void Roller::move(Map *map)
{
    int speed = 0;

    Body::move(map);

    switch(m_action) {
       case Still:
           update_speed();
           break;

       case Move:
           animate_move();
           speed = get_attribute("move_speed");
           if (abs(m_x - m_tx) <= speed && abs(m_y - m_ty) <= speed) {
               set_speed(0, 0);
               set_action(Still);
           }
           break;

       case Hit:
       case HitPerish:
           process_hit();
           break;

       default:
           break;
    }
}


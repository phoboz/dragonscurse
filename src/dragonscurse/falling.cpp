#include <iostream>
#include "falling.h"

void Falling::move(Map *map)
{
    int x, dist;

    Monster::move(map);

    switch(m_action) {
        case Still:
            dist = get_attribute("attack_distance");
            x = m_xref - get_front();
            if (abs(x) < dist) {
                set_fall();
                m_dy = get_attribute("weight");
            }
            break;

        case Fall:
            if (check_below(map, 1)) {
                m_dy = get_attribute("weight");
            }
            else {
                if (check_below(map)) {
                    Actor::set_hit(0);
                    set_invisible(true);
                    m_hit = HitPerish;
                }
            }
            m_y += m_dy;
            break;

        default:
            break;
    }
}


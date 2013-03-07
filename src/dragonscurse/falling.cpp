#include <iostream>
#include "falling.h"

void Falling::move(Map *map)
{
    int x, dist;

    Monster::move(map);

    switch(m_action) {
        case Still:
            if (m_hit == HitNone) {
                dist = get_attribute("attack_distance");
                x = m_xref - get_front();
                if (abs(x) < dist) {
                    set_fall();
                    m_fall_distance = 0;
                    m_dy = get_attribute("weight");
                }
            }
            break;

        case Fall:
            dist = get_attribute("freefall_distance");
            if (m_fall_distance < dist) {
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
            m_fall_distance += m_dy;

            // TODO: Check if the block shall stay on the map
            if (m_hit == HitPerish) {
                map->set_tile_id(get_front(), get_bottom(), 0, 1);
            }
            break;

        default:
            break;
    }
}


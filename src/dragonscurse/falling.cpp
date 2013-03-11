#include <iostream>
#include "falling.h"

Falling::Falling(const char *fn, int x, int y, Direction dir)
    : Monster(fn, x, y, dir),
      m_initialized(false)
{
    set_invinsible(true);
}

void Falling::initialize()
{
    if (!m_initialized) {
        if (get_attribute("stay")) {
            set_always_visible(true);
        }
        m_initialized = true;
    }
}

void Falling::fall()
{
    set_fall();
    m_fall_distance = 0;
    m_dy = get_attribute("weight");
}

void Falling::move(Map *map)
{
    int x, dist, tmr;

    Monster::move(map);

    switch(m_action) {
        case Still:
            if (m_hit == HitNone) {
                dist = get_attribute("attack_distance");
                if (dist) {
                    x = m_xref - get_front();
                    if (abs(x) < dist) {
                        tmr = get_attribute("trigger_time");
                        if (tmr) {
                            if (m_trigger_timer.expired(tmr)) {
                                fall();
                            }
                        }
                        else {
                            fall();
                        }
                    }
                }
                else {
                    fall();
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

            if (m_hit == HitPerish) {
                if (get_attribute("stay")) {
                    map->set_tile_id(get_x() + get_image_width() / 4,
                                     get_y() + get_image_height() / 4,
                                     0, 1);
                }
            }
            break;

        default:
            break;
    }
}


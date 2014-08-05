#include "falling.h"

Falling::Falling(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir),
      m_initialized(false)
{
    set_invinsible(true);
    set_solid(false);
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
    set_action(Fall);
    m_fall_distance = 0;
    set_ay(get_attribute("weight"));
}

void Falling::move(Map *map)
{
    int x, dist, tmr;

    switch(m_action) {
        case Still:
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
            break;

        case Fall:
            dist = get_attribute("freefall_distance");
            if (m_fall_distance >= dist) {
                set_solid(true);
            }

            Body::move(map);
            if (!get_fall()) {
                Actor::set_hit();
                set_perish();
            }
            m_fall_distance += m_dy;
            break;

        case HitPerish:
            process_hit();
            if (get_attribute("stay")) {
                map->set_tile_id(get_x() + get_image_width() / 4,
                                 get_y() + get_image_height() / 4,
                                 0, 1);
            }
            break;

        default:
            Monster::move(map);
            break;
    }
}


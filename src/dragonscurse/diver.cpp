#include "diver.h"

Diver::Diver(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir),
      m_y0(get_y()),
      m_flying(false)
{
    set_ay(0);
    set_solid(false);
}

void Diver::move(Map *map)
{
    switch(m_action) {
        case Still:
            set_action(Move);
            break;

        case Move:
            face_reference(get_attribute("turn_width"));
            animate_move();
            if (!m_flying) {
                int dist = get_attribute("attack_distance");
                int x = m_xref - get_front();
                int y = m_yref - get_y();
                if (x * x + y * y < dist * dist) {
                    set_ay(get_attribute("weight"));
                    if (m_dir == Right) {
                        set_vx(get_attribute("move_speed"));
                    }
                    else {
                        set_vx(-get_attribute("move_speed"));
                    }
                }
            }
            else if (m_y <= m_y0) {
                set_ay(0);
                set_speed(0, 0);
                m_flying = false;
            }
            Body::move(map);
            if (get_fall()) {
                set_action(Fall);
            }
            break;

        case Fall:
            animate_move();
            if (m_dive_timer.expired(get_attribute("dive_time"))) {
                set_ay(-get_attribute("fly_power"));
                m_flying = true;
            }
            Body::move(map);
            if (!get_fall()) {
                set_action(Move);
            }
            break;

        case Hit:
        case HitPerish:
            set_ay(0);
            set_vy(0);
            process_hit();
            Monster::move(map);
            break;

        default:
            break;
    }
}


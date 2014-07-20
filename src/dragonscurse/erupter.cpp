#include "erupter.h"

void Erupter::move(Map *map)
{
    Monster::move(map);

    // Check ground
    check_ground(map);

    if (m_hit == HitOne) {
        if (m_hit_timer.expired(get_attribute("hit_time"))) {
            m_dx = 0;
            reset_hit();
        }
    }

    switch(m_action) {
        case Still:
            if (m_hit == HitNone) {
                set_move_dir();
            }
            break;

        case Move:
            if (m_hit == HitNone) {
                if (m_attack_timer.check(get_attribute("attack_timer"))) {
                    int dist = get_attribute("attack_distance");
                    int x = m_xref - get_front();
                    int y = m_yref - get_y();
                    if (x * x + y * y < dist * dist) {
                        m_attack_timer.reset();
                        set_jump_dir();
                        m_dx = get_attribute("jump_forward");
                        m_dy = get_attribute("jump_speed");
                    }
                }
            }
            break;

        case Fall:
            check_ahead(map);

            // Move
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }

            check_below(map);
            m_y += m_dy;
            break;

        default:
            break;
    }
}


#include "floater.h"

bool Floater::check_env(Map *map)
{
    bool result = false;

    if (!m_start_env || check_above(map, 1, m_start_env, m_end_env) == 0) {
        result = true;
    }

    return result;
}

void Floater::move(Map *map)
{
    switch(m_action) {
        case Still:
            if (check_env(map)) {
                int dist = get_attribute("attack_distance");
                int x = m_xref - get_front();
                int y = m_yref - get_y();
                if (x * x + y * y < dist * dist) {
                    m_lock_x = m_xref;
                    m_lock_y = m_yref;
                    set_action(Move);
                }
            }
            break;

        case Move:
            animate_move();
            if (check_env(map)) {
                int delta = get_attribute("turn_width");
                if (m_lock_x + delta < m_x) {
                    set_vx(-get_attribute("move_speed"));
                }
                else if (m_lock_x - delta > m_x) {
                    set_vx(get_attribute("move_speed"));
                }

                if (m_lock_y + delta < m_y) {
                    set_vy(-get_attribute("move_speed"));
                }
                else if (m_lock_y - delta > m_y) {
                    set_vy(get_attribute("move_speed"));
                }

                if (m_attack_timer.expired(get_attribute("attack_timer"))) {
                    set_speed(0, 0);
                    set_action(Still);
                }
            }
            else {
                set_speed(0, 0);
                set_action(Still);
            }
            Body::move(map);
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


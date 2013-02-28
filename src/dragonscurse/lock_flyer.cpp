#include "lock_flyer.h"

void LockFlyer::move(Map *map)
{
    Monster::move(map);

    if (m_hit == HitOne) {
        if (m_hit_timer.expired(get_attribute("hit_time"))) {
            m_dx = 0;
            reset_hit();
        }
        else {
            // Move backwards
            m_dx = get_attribute("move_speed");

            // Check for collision with map
            check_behind(map);

            // Move
            if (m_dir == Right) {
                m_x -= m_dx;
            }
            else if (m_dir == Left) {
                m_x += m_dx;
            }
        }
    }

    switch(m_action) {
        case Still:
            if (m_hit == HitNone) {
                if (m_attack_timer.expired(get_attribute("attack_timer"))) {
                    const Sprite *spr = get_sprite();
                    int dist = get_attribute("attack_distance");
                    int x = m_xref - get_front();
                    int y = m_yref - (get_y() + spr->get_height() / 2);
                    if (x * x + y * y < dist * dist) {
                        set_move_dir();
                        m_lock_y = m_yref + spr->get_height() / 2;
                    }
                }
            }
            break;

        case Move:
            if (m_hit == HitNone) {
                if (abs(m_lock_y - m_y) > 10) {
                    if (m_y < m_lock_y) {
                        m_vertical_dir = VerticalDown;
                    }
                    else if (m_y > m_lock_y) {
                        m_vertical_dir = VerticalUp;
                    }
                }
                else {
                    m_vertical_dir = VerticalNone;
                }

                // Move
                if (m_vertical_dir == VerticalDown) {
                    m_dy = get_attribute("move_speed");
                    check_below(map);
                    m_y += m_dy;
                }
                else if (m_vertical_dir == VerticalUp) {
                    m_dy = get_attribute("move_speed");
                    check_above(map);
                    m_y -= m_dy;
                }
                else {
                    m_dx = get_attribute("move_speed");
                    face_reference();
                    check_ahead(map);
                    if (m_dir == Right) {
                        m_x += m_dx;
                    }
                    else if (m_dir == Left) {
                        m_x -= m_dx;
                    }
                }
                animate_move();
            }
            break;

        default:
            break;
    }
}


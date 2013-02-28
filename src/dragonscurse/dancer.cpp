#include "dancer.h"

void Dancer::move(Map *map)
{
    Monster::move(map);

    // Check ground
    check_ground(map);

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

#include <iostream>
    switch(m_action) {
        case Still:
            if (m_hit == HitNone) {
                set_move_dir();
            }
            break;

        case Move:
            if (m_hit == HitNone) {
                int dist = get_attribute("attack_distance");
                int x = m_xref - get_front();
                int y = m_yref - get_y();
                if (x * x + y * y < dist * dist) {
                    set_jump_dir();
                    m_dx = get_attribute("jump_forward");
                    m_dy = get_attribute("jump_speed");
                }
                else {
                    m_dx = get_attribute("move_speed");
                    face_reference(get_attribute("turn_width"));
                    check_ahead(map);
                    if (m_dir == Right) {
                        m_x += m_dx;
                    }
                    else if (m_dir == Left) {
                        m_x -= m_dx;
                    }
                    animate_move();
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

        case Jump:
            if (m_hit == HitNone) {
                // Check jump height
                if (m_jump_timer.expired(get_attribute("jump_limit"))) {
                    set_fall();
                }

                // Check horizontal direction
                check_ahead(map);

                // Move
                if (m_dir == Right) {
                    m_x += m_dx;
                }
                else if (m_dir == Left) {
                    m_x -= m_dx;
                }

                // Check if hit head
                if (check_above(map)) {
                    m_jump_timer.reset();
                    set_fall();
                }
                m_y -= m_dy;
            }
            else {
                m_jump_timer.reset();
                set_fall();
            }
            break;

        default:
            break;
    }
}


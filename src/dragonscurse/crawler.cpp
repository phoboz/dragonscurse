#include "crawler.h"

void Crawler::check_ground(Map *map)
{
    if (!m_hit_ground) {
        Actor::check_ground(map);
        if (!m_dy) {
            m_hit_ground = true;
        }
    }
    else {
        if (m_dir == Right) {
            if (!check_collision(m_x + get_attribute("right"),
                                 m_y + get_attribute("bottom") + 1, map, 0)) {
                set_move_dir(Left);
            }
        }
        else if (m_dir == Left) {
            if (!check_collision(m_x + get_attribute("left"),
                                 m_y + get_attribute("bottom") + 1, map, 0)) {
                set_move_dir(Right);
            }
        }
    }
}

void Crawler::move(Map *map)
{
    Monster::move(map);

    // Check ground
    check_ground(map);

    if (m_hit == HitOne) {
        if (m_hit_timer.expired(get_attribute("hit_time"))) {
            m_dx = 0;
            m_hit_ground = false;
            reset_hit();
        }
        else {
            // Move backwards
            m_dx = get_attribute("move_speed");

            // Check for collision with map
            check_behind(map);

            // Right of player
            if (get_reference() == Right) {
                m_x -= m_dx;
            }
            else {
                m_x += m_dx;
            }
        }
    }

    switch(m_action) {
        case Still:
            if (m_hit == HitNone) {
                set_move_dir();
            }
            break;

        case Move:
            m_dx = get_attribute("move_speed");

            check_ahead(map);
            if (!m_dx) {
                swap_move_dir();
                check_ahead(map);
            }

            // Move
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }
            animate_move();
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
            set_move_dir();
            break;
    }
}


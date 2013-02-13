#include "walker.h"

void Walker::move(Map *map)
{
    // Check ground
    if (m_action != Jump && m_action != Hit) {
        check_ground(map);
    }

    switch(m_action) {
        case Move:
            check_ground(map);
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
            check_ground(map);
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
            check_ground(map);
            set_move_dir(Keep);
            break;
    }

}


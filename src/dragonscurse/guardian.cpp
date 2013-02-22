#include "guardian.h"

void Guardian::move(Map *map)
{
    Actor::move(map);

    // Check ground
    if (m_action != Jump && m_action != Hit) {
        check_ground(map);
    }

    switch(m_action) {
        case Still:
        case Move:
            face_reference();
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

        case Hit:
            if (m_hit_timer.expired(get_attribute("hit_time"))) {
                m_dx = 0;
                set_still();
            }
            else {
                // Move backwards
                m_dx = get_attribute("move_speed");

                // Check for collision with map
                check_behind(map);
                check_above(map);

                // Move
                if (m_dir == Right) {
                    m_x -= m_dx;
                }
                else if (m_dir == Left) {
                    m_x += m_dx;
                }

                // Check fall in hit
                m_dy = get_attribute("weight");
                check_below(map);
                m_y += m_dy;
            }
            break;

        default:
            break;
    }

}


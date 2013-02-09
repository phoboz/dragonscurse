#include "guardian.h"

void Guardian::move(Map *map)
{
    // Check ground
    if (m_action != Jump) {
        m_dy = get_attribute("weight");
        check_below(map);
        if (m_dy) {
            m_action = Fall;
        }
        else if (m_action == Fall) {
            set_still();
        }
    }

    switch(m_action) {
        case Move:
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
            set_move_dir(Keep);
            break;
    }

}


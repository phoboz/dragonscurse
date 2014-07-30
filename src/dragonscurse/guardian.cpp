#include "guardian.h"

void Guardian::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            face_reference();
            break;

        case Move:
            face_reference();
            animate_move();

            if (m_attack_timer.check(get_attribute("attack_timer"))) {
                int dist = get_attribute("attack_distance");
                int x = m_xref - get_front();
                int y = m_yref - get_y();
                if (x * x + y * y < dist * dist) {
                    m_attack_timer.reset();
                    set_action(Jump);
                    if (get_reference() == Right) {
                        set_vx(get_attribute("jump_forward"));
                    }
                    else {
                        set_vx(-get_attribute("jump_forward"));
                    }
                }
            }
            break;

        default:
            break;
    }
}


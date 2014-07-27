#include "dancer.h"

void Dancer::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            set_move_dir();
            break;

        case Move:
            face_reference(get_attribute("turn_width"));
            animate_move();

            if (m_attack_timer.check(get_attribute("attack_timer"))) {
                int dist = get_attribute("attack_distance");
                int x = m_xref - get_front();
                int y = m_yref - get_y();
                if (x * x + y * y < dist * dist) {
                    m_attack_timer.reset();
                    set_action(Jump);
                    if (get_reference() == Right) {
                        set_speed(get_attribute("jump_forward"),
                                  -get_attribute("jump_speed"));
                    }
                    else {
                        set_speed(-get_attribute("jump_forward"),
                                  -get_attribute("jump_speed"));
                    }
                }
            }
            else {
                if (m_dir == Right) {
                    set_vx(get_attribute("move_speed"));
                }
                else {
                    set_vx(-get_attribute("move_speed"));
                }
            }
            break;

        default:
            break;
    }
}


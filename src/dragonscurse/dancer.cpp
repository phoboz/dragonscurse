#include <stdlib.h>
#include "dancer.h"

void Dancer::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            set_action(Move);
            break;

        case Move:
            face_reference(get_attribute("turn_width"));
            animate_move();
            if (m_dir == Right) {
                set_vx(get_attribute("move_speed"));
            }
            else {
                set_vx(-get_attribute("move_speed"));
            }

            if (m_attack_timer.check(get_attribute("attack_timer"))) {
                int dist = m_xref - get_front();
                if (abs(dist) < get_attribute("attack_distance")) {
                    m_attack_timer.reset();
                    set_jump(map);
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
            break;

        default:
            break;
    }
}


#include "walker.h"

void Walker::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            set_move_dir();
            break;

        case Move:
            if (check_ahead(map)) {
                swap_move_dir();
            }

            if (m_dir == Right) {
                set_vx(get_attribute("move_speed"));
            }
            else {
                set_vx(-get_attribute("move_speed"));
            }
            animate_move();
            break;

        default:
            break;
    }

}


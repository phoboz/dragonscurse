#include "walker.h"

void Walker::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            set_action(Move);
            break;

        case Move:
            if (check_ahead(map)) {
                swap_move_dir();
            }

            if (m_dir == Right) {
                set_vx(get_move_speed(map));
            }
            else {
                set_vx(-get_move_speed(map));
            }
            animate_move();
            break;

        default:
            break;
    }

}


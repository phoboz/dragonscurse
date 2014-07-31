#include "crawler.h"

void Crawler::check_ground(Map *map)
{
    if (get_hit_ground()) {
        if (m_dir == Right) {
            if (!check_collision(m_x + get_attribute("right"),
                                 m_y + get_attribute("bottom") + 1, map)) {
                set_move_dir(Left);
            }
        }
        else if (m_dir == Left) {
            if (!check_collision(m_x + get_attribute("left"),
                                 m_y + get_attribute("bottom") + 1, map)) {
                set_move_dir(Right);
            }
        }
    }
}

void Crawler::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            face_reference();
            set_action(Move);
            break;

        case Move:
            if (check_ahead(map)) {
                swap_move_dir();
            }
            check_ground(map);
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


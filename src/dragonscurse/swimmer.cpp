#include "swimmer.h"

void Swimmer::move(Map *map)
{
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if under water
    int start = prop.GetNumericProperty("water_start");
    int end = prop.GetNumericProperty("water_end");

    switch(m_action) {
        case Still:
            if (start && check_above(map, 1, start, end) == 0) {
                int dist = get_attribute("attack_distance");
                int x = m_xref - get_front();
                int y = m_yref - get_y();
                if (x * x + y * y < dist * dist) {
                    m_lock_x = m_xref;
                    m_lock_y = m_yref;
                    set_action(Move);
                }
            }
            break;

        case Move:
            animate_move();
            if (start && check_above(map, 1, start, end) == 0) {
                int delta = get_attribute("turn_width");
                if (m_lock_x + delta < m_x) {
                    set_vx(-get_attribute("move_speed"));
                }
                else if (m_lock_x - delta > m_x) {
                    set_vx(get_attribute("move_speed"));
                }

                if (m_lock_y + delta < m_y) {
                    set_vy(-get_attribute("move_speed"));
                }
                else if (m_lock_y - delta > m_y) {
                    set_vy(get_attribute("move_speed"));
                }

                if (m_attack_timer.expired(get_attribute("attack_timer"))) {
                    set_speed(0, 0);
                    set_action(Still);
                }
            }
            else {
                set_speed(0, 0);
                set_action(Still);
            }
            Body::move(map);
            break;

        case Hit:
        case HitPerish:
            set_ay(0);
            set_vy(0);
            process_hit();
            Monster::move(map);
            break;

        default:
            break;
    }
}


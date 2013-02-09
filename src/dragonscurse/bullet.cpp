#include "bullet.h"

void Bullet::reload()
{
    m_loaded = false;
    m_distance = 0;
    m_counter = 0;
}

bool Bullet::fire(int x, int y, Direction dir)
{
    bool result = false;

    if (!m_moving && m_loaded) {
        m_x = x;
        m_y = y;
        m_dir = dir;

        if (dir == Right) {
            m_dx = get_attribute("move_speed");
            m_frame = get_attribute("right_move_start");
        }
        else if (dir == Left) {
            m_dx = get_attribute("move_speed");
            m_frame = get_attribute("left_move_start");
        }

        m_moving = true;
        reload();
        result = true;
    }

    return result;
}

void Bullet::move(Map *map)
{
    if (++m_counter == get_attribute("reload_time")) {
        m_counter = 0;
        m_loaded = true;
    }

    if (m_moving) {
        check_ahead(map);
        if (m_dx) {
            m_distance += m_dx;
            if (m_distance < get_attribute("distance")) {
                if (m_dir == Right) {
                    m_x += m_dx;
                }
                else if (m_dir == Left) {
                    m_x -= m_dx;
                }
            }
            else {
                m_moving = false;
                reload();
            }
        }
        else {
            m_moving = false;
        }
    }
}


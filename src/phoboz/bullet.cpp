#include "phoboz/bullet.h"

void Bullet::fire(int x, int y, Direction dir)
{
    if (!m_moving) {
        m_moving = true;
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
    }
}

void Bullet::move(Map *map)
{
    if (m_moving) {
        check_ahead(map);
        if (m_dx) {
            // Move
            if (m_dir == Right) {
                m_x += m_dx;
                if (m_x > 640) {
                    m_moving = false;
                }
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
                if (m_x < 0) {
                    m_moving = false;
                }
            }
        }
        else {
            m_moving = false;
        }
    }
}


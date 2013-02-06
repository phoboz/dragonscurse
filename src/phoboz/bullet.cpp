#include "phoboz/bullet.h"

void Bullet::fire(int x, int y, Direction dir)
{
    if (!m_moving) {
        m_moving = true;
        m_x = x;
        m_y = y;
        m_dir = dir;
        if (dir == Right) {
            m_dx = get_attribute("speed");
            m_frame = get_attribute("right_start");
        }
        else if (dir == Left) {
            m_dx = -get_attribute("speed");
            m_frame = get_attribute("left_start");
        }
    }
}

void Bullet::move(Map *map)
{
    if (m_moving) {
        m_x += m_dx;
        if (m_x < 0 || m_x > 640) {
            m_moving = false;
        }
    }
}


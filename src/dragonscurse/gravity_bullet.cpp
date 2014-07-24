#include "gravity_bullet.h"

void GravityBullet::move(Map *map)
{
    Bullet::move(map);

    if (m_rise_timer.expired(get_attribute("rise_limit"))) {
        m_rise_timer.reset();
        m_vertical_dir = VerticalDown;
        m_dy = get_attribute("weight");
    }
}


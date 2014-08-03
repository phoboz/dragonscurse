#include <math.h>
#include "solid_bullet.h"

SolidBullet::SolidBullet(const char *fn, MediaDB *media)
    : Bullet(fn, media)
{
    set_ay(get_attribute("weight"));
}

bool SolidBullet::fire(int x, int y, int dx, int dy)
{
    bool result = false;

    if (!get_active() && get_ready()) {
        set_x(x);
        set_y(y);
        set_speed(0, 0);
        m_speed = dx;
        reload(true);
        result = true;
    }

    return result;
}

void SolidBullet::move(Map *map)
{
    if (!get_moving()) {
        set_vx(m_speed);
    }
    Bullet::move(map);
}


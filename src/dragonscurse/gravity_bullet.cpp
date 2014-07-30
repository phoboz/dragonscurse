#include <math.h>
#include "gravity_bullet.h"

GravityBullet::GravityBullet(const char *fn, MediaDB *media)
    : Body(TypeBullet)
{
    load(fn, media);
    set_solid(false);
}

bool GravityBullet::fire(int x, int y, int dx, int dy)
{
    set_x(x);
    set_y(y);
    m_distance = 0;
    set_speed(dx, dy);
    set_accelration(0, get_attribute("weight"));
}

bool GravityBullet::get_moving() const
{
    bool result = Body::get_moving();
    if (result) {
        if (m_distance >= get_attribute("distance")) {
            result = false;
        }
     }

    return result;
}

bool GravityBullet::hit_object(Object *object)
{
    bool result = false;

    if (get_moving()) {
        if (object->check_weak_collision(this)) {
            result = true;
        }
    }

    return result;
}

void GravityBullet::move(Map *map)
{
    if (m_distance < get_attribute("distance")) {
        Body::move(map);
        m_distance += sqrt(m_dx * m_dx + m_dy * m_dy);
    }
}


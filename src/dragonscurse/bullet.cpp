#include <math.h>
#include "bullet.h"

void Bullet::set_dir(Direction dir)
{
    if (dir == Right) {
        m_frame = get_attribute("right_move_start");
    }
    else if (dir == Left) {
        m_frame = get_attribute("left_move_start");
    }

    Body::set_dir(dir);
}

void Bullet::reload(bool active)
{
    m_ready = false;
    m_distance = 0;
    m_reload_timer.reset();
    m_active = active;
}

bool Bullet::hit_object(Object *object)
{
    bool result = false;

    if (m_active) {
        if (object->check_shielded_collision(this)) {
            // Remove bullet if it hits a shielded area
            reload(false);
        }
        else if (object->check_weak_collision(this)) {

            // Remove bullet if it only is supposed to hit one target
            if (m_hit_one) {
                reload(false);
            }
            result = true;
        }
    }

    return result;
}

void Bullet::move(Map *map)
{
    if (m_reload_timer.expired(get_attribute("reload_time"))) {
        m_ready = true;
    }

    if (m_active) {
        if (m_distance < get_attribute("distance")) {
            Body::move(map);
            if (get_moving()) {
                m_distance += sqrt(m_dx * m_dx + m_dy * m_dy);
            }
            else {
                reload(false);
            }
        }
        else {
            reload(false);
        }
    }
}


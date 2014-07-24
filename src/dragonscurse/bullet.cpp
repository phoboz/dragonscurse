#include <math.h>
#include "bullet.h"

void Bullet::reload()
{
    m_loaded = false;
    m_distance = 0;
    m_reload_timer.reset();
}

bool Bullet::fire(int x, int y, int dx, int dy)
{
    bool result = false;

    if (!m_moving && m_loaded) {
        m_x = x;
        m_y = y;

        if (dx > 0) {
            m_dir = Right;
            m_dx = dx;
            m_frame = get_attribute("right_move_start");
        }
        else if (dx < 0) {
            m_dir = Left;
            m_dx = -dx;
            m_frame = get_attribute("left_move_start");
        }

        if (dy < 0) {
            m_vertical_dir = VerticalUp;
            m_dy = -dy;
        }
        else if (dy > 0) {
            m_vertical_dir = VerticalDown;
            m_dy = dy;
        }

        m_moving = true;
        reload();
        result = true;
    }

    return result;
}

bool Bullet::hit_object(Object *object)
{
    bool result = false;

    if (m_moving) {
        const Sprite *spr = get_sprite();
        if (spr->check_collision(m_frame, m_x, m_y,
                                 object->get_sprite(), object->get_frame(),
                                 object->get_x(), object->get_y(),
                                 object->get_attribute("weak_left"),
                                 object->get_attribute("weak_top"),
                                 object->get_attribute("weak_right"),
                                 object->get_attribute("weak_bottom"))) {
            result = true;
        }
    }

    return result;
}

void Bullet::move(Map *map)
{
    if (m_reload_timer.expired(get_attribute("reload_time"))) {
        m_loaded = true;
    }

    if (m_moving) {
        if (m_follow_terrain) {
            check_ahead(map);
        }
        if (m_vertical_dir == VerticalDown) {
            if (m_follow_terrain) {
                check_below(map);
            }
        }
        else if (m_vertical_dir == VerticalUp) {
            if (m_follow_terrain) {
                check_above(map);
            }
        }
        if (m_dx || m_dy) {
            if (m_distance < get_attribute("distance")) {
                if (m_dir == Right) {
                    m_x += m_dx;
                }
                else if (m_dir == Left) {
                    m_x -= m_dx;
                }
                if (m_vertical_dir == VerticalDown) {
                    m_y += m_dy;
                }
                else if (m_vertical_dir == VerticalUp) {
                    m_y -= m_dy;
                }
                m_distance += sqrt(m_dx * m_dx + m_dy * m_dy);
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


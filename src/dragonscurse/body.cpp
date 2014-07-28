#include <math.h>
#include "body.h"

void Body::set_accelration(int ax, int ay)
{
    m_ax = float(ax) * c_g;
    m_ay = float(ay) * c_g;
}

void Body::set_speed(int vx, int vy)
{
    m_vx = float(vx);
    m_vy = float(vy);
}

void Body::set_dir(Direction dir)
{
    if (dir != Keep) {
        m_dir = dir;
    }
}


bool Body::get_moving() const
{
    bool result = false;

    if (fabs(m_vx) >= c_sigma || fabs(m_vy) >= c_sigma) {
        result = true;
    }

    return result;
}

void Body::move(Map *map)
{
    float tw = float(map->get_tile_width());
    float th = float(map->get_tile_height());

    m_vx += m_ax;
    if (m_vx < -tw) {
        m_vx = -tw;
    }
    else if (m_vx > tw) {
        m_vx = tw;
    }

    m_vy += m_ay;
    if (m_vy < -th) {
        m_vy = -th;
    }
    else if (m_vy > th) {
        m_vy = th;
    }

    if (m_vx > 0.0f) {
        m_dx = int(m_vx);
        if (!m_lock_dir) {
            set_dir(Right);
            if (m_solid) {
                if (check_ahead(map)) {
                    m_vx = 0.0f;
                }
            }
        }
        else if (m_dir == Right) {
            if (m_solid) {
                if (check_ahead(map)) {
                    m_vx = 0.0f;
                }
            }
        }
        else if (m_dir == Left) {
            if (m_solid) {
                if (check_behind(map)) {
                    m_vx = 0.0f;
                }
            }
        }
        m_x += m_dx;
    }
    else if (m_vx < 0.0f) {
        m_dx = -int(m_vx);
        if (!m_lock_dir) {
            set_dir(Left);
            if (m_solid) {
                if (check_ahead(map)) {
                    m_vx = 0.0f;
                }
            }
        }
        else if (m_dir == Right) {
            if (m_solid) {
                if (check_behind(map)) {
                    m_vx = 0.0f;
                }
            }
        }
        else if (m_dir == Left) {
            if (m_solid) {
                if (check_ahead(map)) {
                    m_vx = 0.0f;
                }
            }
        }
        m_x -= m_dx;
    }
    else {
        set_dir(Keep);
        m_dx = 0;
    }

    if (m_vy > 0.0f) {
        m_dy = int(m_vy);
        if (m_solid) {
            if (check_below(map)) {
                m_vy = 0.0f;
            }
        }
        m_y += m_dy;
    }
    else if (m_vy < 0.0f) {
        m_dy = -int(m_vy);
        if (m_solid) {
            if (check_above(map)) {
                m_vy = 0.0f;
            }
        }
        m_y -= m_dy;
    }
    else {
        m_dy = 0;
    }
}


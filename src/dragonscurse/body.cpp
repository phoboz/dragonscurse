#include "body.h"

void Body::set_accelration(int ax, int ay)
{
    m_ax = ax;
    m_ay = ay;
}

void Body::set_speed(int vx, int vy)
{
    m_vx = vx;
    m_vy = vy;
}

void Body::set_move_dir(Direction dir)
{
    if (dir != Keep) {
        m_dir = dir;
    }
}

void Body::set_vertical_dir(VerticalDirection dir)
{
    if (dir != VerticalNone) {
        m_vert_dir = dir;
    }
}

void Body::move(Map *map)
{
    int tw = map->get_tile_width();
    int th = map->get_tile_height();

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

    if (m_vx > 0) {
        set_move_dir(Right);
        m_dx = m_vx;
        if (!check_ahead(map)) {
            m_x += m_dx;
        }
        else {
            m_vx = 0;
        }
    }
    else if (m_vx < 0) {
        set_move_dir(Left);
        m_dx = -m_vx;
        if (!check_ahead(map)) {
            m_x -= m_dx;
        }
        else {
            m_vx = 0;
        }
    }
    else {
        set_move_dir(Keep);
        m_dx = 0;
    }

    if (m_vy > 0) {
        set_vertical_dir(VerticalDown);
        m_dy = m_vy;
        if (!check_below(map)) {
            m_y += m_dy;
        }
        else {
            m_vy = 0;
        }
    }
    else if (m_vy < 0) {
        set_vertical_dir(VerticalUp);
        m_dy = -m_vy;
        if (!check_above(map)) {
            m_y -= m_dy;
        }
        else {
            m_vy = 0;
        }
    }
    else {
        set_vertical_dir(VerticalNone);
        m_dy = 0;
    }
}


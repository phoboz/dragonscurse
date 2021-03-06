#include <stdlib.h>
#include "hovering.h"

Hovering::Hovering(const char *fn, MediaDB *media, int x, int y, int w,
                   Direction dir)
    : Monster(fn, media, x + w / 2, y, dir),
      m_x0(x), m_x1(x + w)
{
    set_ay(0);
    set_solid(false);

    const char* bullet_name = get_string("bullet");
    int num_bullets = get_attribute("num_bullets");

    for (int i = 0; i < num_bullets; i++) {
        SolidBullet *bullet = new SolidBullet(bullet_name, media);
        if (!bullet->get_loaded()) {
            exit(1);
        }
        m_bullets.push_back(bullet);
    }
}

bool Hovering::attack_object(Object *object)
{
    bool result = false;
    unsigned n = m_bullets.size();

    for (int i = 0; i < n; i++) {
        if (m_bullets[i]->hit_object(object)) {
            result = true;
            break;
        }
    }

    return result;
}

void Hovering::fire()
{
    bool result = false;

    unsigned n = m_bullets.size();
    for (int i = 0; i < n; i++) {
        if (!m_bullets[i]->get_active()) {
            int dx = get_attribute("bullet_speed");
            if (get_reference() == Right) {
                result = m_bullets[i]->fire(m_x, m_y, dx, 0);
            }
            else {
                result = m_bullets[i]->fire(m_x, m_y, -dx, 0);
            }
        }

        if (result) {
            break;
        }
    }
}

bool Hovering::get_visible(Map *map, int clip_x, int clip_y,
                           int clip_w, int clip_h) const
{
    bool result = false;

    if (m_bullets.size()) {
        result = true;
    }
    else {
        result = Object::get_visible(map, clip_x, clip_y, clip_w, clip_h);
    }

    return result;
}

void Hovering::move(Map *map)
{
    switch(m_action) {
        case Still:
            set_action(Move);
            break;

        case Move:
            face_reference(get_attribute("turn_width"));
            animate_move();
            if (m_dir == Right) {
                if (m_x < m_x1) {
                    set_vx(get_move_speed(map));
                }
                else {
                    swap_move_dir();
                    set_vx(0);
                }
            }
            else {
                if (m_x > m_x0) {
                    set_vx(-get_move_speed(map));
                }
                else {
                    swap_move_dir();
                    set_vx(0);
                }
            }

            if (m_attack_timer.expired(get_attribute("attack_timer"))) {
                int dist = m_xref - get_front();
                if (abs(dist) < get_attribute("attack_distance")) {
                    fire();
                }
            }
            Body::move(map);
            break;

        case Hit:
        case HitPerish:
            set_vy(0);
            process_hit();
            Monster::move(map);
            break;

        default:
            break;
    }

    // Move bullets
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->move(map);
    }
}

void Hovering::draw(Surface *dest, Map *map,
                    int clip_x, int clip_y, int clip_w, int clip_h)
{
    Monster::draw(dest, map, clip_x, clip_y, clip_w, clip_h);

    // Draw bullets
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


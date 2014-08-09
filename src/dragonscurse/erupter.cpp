#include <stdlib.h>
#include <vector>
#include "erupter.h"

Erupter::Erupter(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir)
{
    const char* bullet_name = get_string("bullet");
    int num_bullets = get_attribute("num_bullets");

    for (int i = 0; i < num_bullets; i++) {
        GravityBullet *bullet = new GravityBullet(bullet_name, media);
        if (!bullet->get_loaded()) {
            exit(1);
        }
        m_bullets.push_back(bullet);
    }
}

bool Erupter::attack_object(Object *object)
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

void Erupter::fire()
{
    bool result = false;

    unsigned n = m_bullets.size();
    for (int i = 0; i < n; i++) {
        if (!m_bullets[i]->get_active()) {
            int x = m_x + get_attribute("attack_medium");
            int dx = get_attribute("fire_dx");
            int rnd_dx = get_attribute("fire_rand_dx");
            if (rnd_dx) {
                dx += rand() % rnd_dx;
            }
            int dy = get_attribute("fire_dy");
            int rnd_dy = get_attribute("fire_rand_dy");
            if (rnd_dy) {
                dy += rand() % rnd_dy;
            }
            if (get_reference() == Right) {
                result = m_bullets[i]->fire(x, m_y, dx, -dy);
            }
            else {
                result = m_bullets[i]->fire(x, m_y, -dx, -dy);
            }

            if (result) {
                set_attack();
                break;
            }
        }
    }
}

bool Erupter::get_visible(Map *map, int clip_x, int clip_y,
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

void Erupter::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            if (m_attack_timer.check(get_attribute("attack_timer"))) {
                m_attack_timer.reset();
                int dist = get_attribute("attack_distance");
                int x = m_xref - get_front();
                int y = m_yref - get_y();
                if (x * x + y * y < dist * dist) {
                    m_attack_timer.reset();
                    fire();
                }
            }
            break;

        case AttackMedium:
            if (m_anim_timer.expired(get_attribute("treshold"))) {
                m_attack_timer.reset();
                reset_attack();
            }
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

void Erupter::draw(SDL_Surface *dest, Map *map,
                   int clip_x, int clip_y, int clip_w, int clip_h)
{
    Monster::draw(dest, map, clip_x, clip_y, clip_w, clip_h);

    // Draw bullets
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


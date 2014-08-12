#include <stdlib.h>
#include "shooter.h"

Shooter::Shooter(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir)
{
    if (get_attribute("face_reference")) {
        m_face_reference = true;
    }
    else {
        m_face_reference = false;
    }

    const char* bullet_name = get_string("bullet");
    int num_bullets = get_attribute("num_bullets");

    for (int i = 0; i < num_bullets; i++) {
        VectorBullet *bullet = new VectorBullet(bullet_name, media);
        if (!bullet->get_loaded()) {
            exit(1);
        }
        m_bullets.push_back(bullet);
    }
}

bool Shooter::attack_object(Object *object)
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

bool Shooter::fire()
{
    bool result = false;

    unsigned n = m_bullets.size();
    for (int i = 0; i < n; i++) {
        if (!m_bullets[i]->get_active()) {
            switch(get_dir()) {
                case Right: 
                    result = m_bullets[i]->fire(
                        m_x + get_attribute("attack_right"),
                        m_y + get_attribute("attack_medium"),
                        get_attribute("bullet_speed"), 0);
                    break;

                case Left:
                    result = m_bullets[i]->fire(
                        m_x + get_attribute("attack_left"),
                        m_y + get_attribute("attack_medium"),
                        -get_attribute("bullet_speed"), 0);
                    break;

                case Down:
                    result = m_bullets[i]->fire(
                        m_x + get_attribute("attack_left"),
                        m_y + get_attribute("attack_medium"),
                        0, get_attribute("bullet_speed"));
                    break;

                case Up:
                    result = m_bullets[i]->fire(
                        m_x + get_attribute("attack_left"),
                        m_y + get_attribute("attack_medium"),
                        0, -get_attribute("bullet_speed"));
                    break;

                default:
                    break;
            }

            if (result) {
                break;
            }
        }
    }

    return result;
}

bool Shooter::get_visible(Map *map, int clip_x, int clip_y,
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

void Shooter::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            set_action(Move);
            break;

        case Move:
            if (m_face_reference) {
                face_reference();
            }

            animate_move();

            if (m_attack_timer.expired(get_attribute("attack_timer"))) {
                int dist = m_xref - m_x;
                if (abs(dist) < get_attribute("attack_distance")) {
                    if (fire()) {
                        set_action(Attack);
                    }
                }
            }
            break;

        case Attack:
            if (animate_attack()) {
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

void Shooter::draw(SDL_Surface *dest, Map *map,
                   int clip_x, int clip_y, int clip_w, int clip_h)
{
    Monster::draw(dest, map, clip_x, clip_y, clip_w, clip_h);

    // Draw bullets
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


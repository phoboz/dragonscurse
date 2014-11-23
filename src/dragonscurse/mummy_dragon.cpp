#include <stdlib.h>
#include "mummy_dragon.h"

MummyDragon::MummyDragon(const char *fn, MediaDB *media,
                         int x, int y, Direction dir)
    : Monster(fn, media, x, y, dir),
      m_bullet_index(0), m_is_flying(false)
{
    set_always_visible(true);
    const char* bullet_name = get_string("bullet");
    int num_bullets = get_attribute("num_bullets");

    m_left = get_left() + get_attribute("turn_left");
    m_right = get_right() + get_attribute("turn_right");
    m_top = m_y + get_attribute("fly_top");
    m_bottom = m_y;
    m_attack_timer.enable(false);

    for (int i = 0; i < num_bullets; i++) {
        VectorBullet *bullet = new VectorBullet(bullet_name, media);
        if (!bullet->get_loaded()) {
            exit(1);
        }
        m_bullets.push_back(bullet);
    }
}

bool MummyDragon::attack_object(Object *object)
{
    bool result = false;
    int num_bullets = m_bullets.size();

    for (int i = 0; i < num_bullets; i++) {

        if (m_bullets[i]->hit_object(object)) {
            result = true;
            break;
        }
    }

    return result;
}

void MummyDragon::fire()
{
    if (m_fire_timer.expired(get_attribute("fire_next"))) {
        if (m_bullet_index < m_bullets.size()) {
            int delta_x =
                get_attribute("fire_max_dx") - get_attribute("fire_min_dx");
            int delta_y =
                get_attribute("fire_max_dy") - get_attribute("fire_min_dy");
            int fire_dx = (rand() % delta_x) + get_attribute("fire_min_dx");
            int fire_dy = (rand() % delta_y) + get_attribute("fire_min_dy");

            if (m_dir == Right) {
                m_bullets[m_bullet_index]->fire(
                    m_x + get_attribute("attack_right"),
                    m_y + get_attribute("attack_medium"),
                    fire_dx, fire_dy);
            }
            else if (m_dir == Left) {
                m_bullets[m_bullet_index]->fire(
                    m_x + get_attribute("attack_left"),
                    m_y + get_attribute("attack_medium"),
                    -fire_dx, fire_dy);
            }
            m_bullet_index++;
        }
        else {
            m_bullet_index = 0;
            set_action(Move);
            reset_attack();
        }
    }
}

bool MummyDragon::get_visible(Map *map, int clip_x, int clip_y,
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

void MummyDragon::move(Map *map)
{
    Monster::move(map);

    switch(m_action) {
        case Still:
            set_action(Move);
            break;

        case Move:
            if (m_is_flying) {
                set_speed(0, m_fly_speed);
                if (m_fly_timer.check(m_fly_time) ||
                    m_y < m_top || m_y > m_bottom) {
                    m_fly_timer.reset();
                    m_is_flying = false;
                }
            }
            else {
                if (get_left() < m_left || get_right() > m_right) {
                    swap_move_dir();
                    if (m_turn_counter.expired(get_attribute("num_turns"))) {
                        m_fly_time = 600;
                        if (m_y < m_top + 100) {
                            m_fly_speed = get_attribute("fly_speed");
                        }
                        else {
                            m_fly_speed = -get_attribute("fly_speed");
                        }
                        m_is_flying = true;
                    }
                    else {
                        m_attack_timer.enable(true);
                    }
                }

                if (m_dir == Right) {
                    set_speed(get_attribute("move_speed"), 0);
                }
                else {
                    set_speed(-get_attribute("move_speed"), 0);
                }
            }

            animate_move();

            if (m_attack_timer.expired(get_attribute("attack_timer"))) {
                m_attack_timer.enable(false);
                set_attack();
            }
            break;

        case Attack:
            fire();
            break;

        case Hit:
            m_fly_time = get_attribute("fly_time_after_hit");
            m_fly_speed = -get_attribute("fly_speed");
            m_is_flying = true;
            break;

        default:
            break;
    }

    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->move(map);
    }
}

void MummyDragon::draw(Surface *dest, Map *map,
                       int clip_x, int clip_y, int clip_w, int clip_h)
{
    Monster::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


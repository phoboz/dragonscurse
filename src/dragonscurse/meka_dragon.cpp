#include <iostream>
#include <stdlib.h>
#include "meka_dragon.h"

MekaDragon::MekaDragon(const char *fn, int x, int y, Direction dir)
    : Monster(fn, x, y, dir),
      m_horizontal_dir(HorizontalForward),
      m_bullet_index(0)
{
    set_always_visible(true);

    const char* bullet_name = get_string("bullet");
    int num_bullets = get_attribute("num_bullets");

    for (int i = 0; i < num_bullets; i++) {
        Bullet *bullet = new Bullet(bullet_name);
        if (!bullet->get_loaded()) {
            exit(1);
        }
        m_bullets.push_back(bullet);
    }
}

bool MekaDragon::attack_actor(Actor *actor)
{
    bool result = false;
    int num_bullets = m_bullets.size();

    for (int i = 0; i < num_bullets; i++) {

        if (m_bullets[i]->hit_object(actor)) {
            result = true;
            break;
        }
    }

    return result;
}

void MekaDragon::fire()
{
    if (m_fire_timer.expired(get_attribute("fire_next"))) {
        if (m_bullet_index < m_bullets.size()) {
            if (m_dir == Right) {
                m_bullets[m_bullet_index]->fire(
                    m_x + get_attribute("attack_right"),
                    m_y + get_attribute("attack_medium"),
                    get_attribute("fire_dx"),
                    get_attribute("fire_dy"));
            }
            else if (m_dir == Left) {
                m_bullets[m_bullet_index]->fire(
                    m_x + get_attribute("attack_left"),
                    m_y + get_attribute("attack_medium"),
                    -get_attribute("fire_dx"),
                    get_attribute("fire_dy"));
            }
            m_bullet_index++;
        }
        else {
            m_bullet_index = 0;
            m_idle_timer.reset();
            set_move_dir();
            reset_attack();
        }
    }
}

void MekaDragon::move(Map *map)
{
    Monster::move(map);

    // Check ground
    check_ground(map);

    if (m_hit == HitOne) {
        if (m_hit_timer.expired(get_attribute("hit_time"))) {
            m_dx = 0;
            reset_hit();
            m_idle_timer.reset();
            set_still();
            set_attack();
        }
        else {
            // Move backwards
            m_dx = get_attribute("move_speed");

            // Check for collision with map
            check_behind(map);

            // Move
            if (m_dir == Right) {
                m_x -= m_dx;
            }
            else if (m_dir == Left) {
                m_x += m_dx;
            }
        }
    }

    switch(m_action)
    {
        case Still:
           if (m_hit == HitNone && m_attack == AttackNone) {
                set_move_dir();
            }
            else if (m_hit == HitNone && m_attack == AttackMedium) {
                if (m_idle_timer.check(get_attribute("attack_idle"))){
                    fire();
                }
            }
            break;

        case Move:
           if (m_hit == HitNone && m_attack == AttackNone) {
                if (m_horizontal_dir == HorizontalForward) {

                    face_reference(get_attribute("turn_width"));
                    m_dx = get_attribute("move_speed");

                    check_ahead(map);

                    // Move
                    if (m_dir == Right) {
                        m_x += m_dx;
                    }
                    else if (m_dir == Left) {
                        m_x -= m_dx;
                    }
                    animate_move();

                    if (abs(m_xref - m_x) < get_attribute("attack_distance")) {
                        m_horizontal_dir = HorizontalBackward;
                    }
                }
                else if (m_horizontal_dir == HorizontalBackward) {

                    face_reference(get_attribute("turn_width"));
                    m_dx = get_attribute("move_speed");

                    if (check_behind(map)) {
                        // Fire directly if pushed against the wall
                        fire();
                    }

                    // Move
                    if (m_dir == Right) {
                        m_x -= m_dx;
                    }
                    else if (m_dir == Left) {
                        m_x += m_dx;
                    }
                    animate_move();

                    if (abs(m_xref - m_x) > get_attribute("retreat_distance")) {
                        m_horizontal_dir = HorizontalForward;
                    }
                }

                if (m_attack_timer.expired(get_attribute("attack_timer"))) {
                    set_still();
                    set_attack();
                }
            }
            break;

        case Fall:
            check_ahead(map);

            // Move
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }

            check_below(map);
            m_y += m_dy;
            break;

        default:
            break;
    }

    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->move(map);
    }
}

void MekaDragon::draw(SDL_Surface *dest, Map *map,
                      int clip_x, int clip_y, int clip_w, int clip_h)
{
    Monster::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    unsigned n = m_bullets.size();
    for (unsigned i = 0; i < n; i++) {
        m_bullets[i]->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


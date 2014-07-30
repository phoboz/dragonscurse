#include <stdlib.h>
#include <string.h>
#include "phoboz/ctrl.h"
#include "dragon.h"

Dragon::Dragon(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Player(fn, media, x, y, dir),
          m_attack_ready(true)
{
    m_bullet = new Bullet(get_string("bullet"), media);
    if (!m_bullet->get_loaded()) {
        exit(1);
    }
    m_bullet->set_hit_one(true);
}

bool Dragon::attack_object(Object *object)
{
    bool result = false;

    if (m_bullet->hit_object(object)) {
        result = true;
    }

    return result;
}

void Dragon::move(Map *map)
{
    int input = get_input();

    Player::move(map);

    // Handle attack
    if (m_action == MediumAttack || m_action == LowAttack) {
        if (m_attack_timer.expired(get_attribute("attack_time"))) {
            reset_attack();
        }
    }
    else if (m_hit == HitNone && !get_invisible()) {
        if (input & PRESS_ATTACK) {
            if (m_attack_ready) {
                m_attack_ready = false;
                int y;
                if (m_action == Crouch) {
                    y = get_attribute("attack_low");
                }
                else {
                    y = get_attribute("attack_medium");
                }

                if (m_dir == Right) {
                    if (m_bullet->fire(m_x + get_attribute("attack_right"),
                                       m_y + y,
                                       get_attribute("bullet_speed"),
                                       0)) {
                        set_attack();
                    }
                }
                else if (m_dir == Left) {
                    if (m_bullet->fire(m_x + get_attribute("attack_left"),
                                       m_y + y,
                                       -get_attribute("bullet_speed"),
                                       0)) {
                        set_attack();
                    }
                }
            }
        }
        else {
            m_attack_ready = true;
        }
    }

    // Move bullet
    m_bullet->move(map);
}

void Dragon::draw(SDL_Surface *dest, Map *map,
                  int clip_x, int clip_y, int clip_w, int clip_h)
{
    Player::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    m_bullet->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
}


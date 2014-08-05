#include <stdlib.h>
#include <string.h>
#include "phoboz/ctrl.h"
#include "dragon.h"

Dragon::Dragon(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Player(fn, media, x, y, dir),
          m_attack_ready(true)
{
    const char *bullet_name = get_string("bullet");
    m_bullet = new VectorBullet(bullet_name, media);
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

bool Dragon::check_shielded_collision(Object *object) const
{
    bool result = Object::check_shielded_collision(object);
    if (!result && m_bullet->get_active()) {
        const Sprite *spr = object->get_sprite();
        result = spr->check_collision(object->get_frame(),
                                      object->get_x(), object->get_y(),
                                      m_bullet->get_sprite(),
                                      m_bullet->get_frame(),
                                      m_bullet->get_x(), m_bullet->get_y());

    }

    return result;
}

void Dragon::move(Map *map)
{
    int input = get_input();

    Player::move(map);

    // Handle attack
    if (m_action == AttackMedium || m_action == AttackLow) {
        if (m_attack_timer.expired(get_attribute("attack_time"))) {
            reset_attack();
        }
    }
    else if (!get_invisible()) {
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


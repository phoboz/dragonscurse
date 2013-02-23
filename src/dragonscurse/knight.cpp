#include <iostream>
#include <string.h>
#include "phoboz/ctrl.h"
#include "knight.h"

bool Knight::attack_actor(Actor *actor)
{
    bool result = false;
    const Sprite *spr = get_sprite();

    if (m_attack == AttackMedium) {
        if (m_dir == Right) {
            if (spr->check_collision(m_frame, m_x, m_y,
                                     get_attribute("attack_right"),
                                     get_attribute("attack_medium_top"),
                                     spr->get_width(),
                                     get_attribute("attack_medium_bottom"),
                                     actor->get_sprite(), actor->get_frame(),
                                     actor->get_x(), actor->get_y())) {
                result = true;
            }
        }
        else if (m_dir == Left) {
            if (spr->check_collision(m_frame, m_x, m_y,
                                     0,
                                     get_attribute("attack_medium_top"),
                                     get_attribute("attack_left"),
                                     get_attribute("attack_medium_bottom"),
                                     actor->get_sprite(), actor->get_frame(),
                                     actor->get_x(), actor->get_y())) {
                result = true;
            }
        }
    }
    else if (m_attack == AttackLow) {
        if (m_dir == Right) {
            if (spr->check_collision(m_frame, m_x, m_y,
                                     get_attribute("attack_right"),
                                     get_attribute("attack_low_top"),
                                     spr->get_width(),
                                     get_attribute("attack_low_bottom"),
                                     actor->get_sprite(), actor->get_frame(),
                                     actor->get_x(), actor->get_y())) {
                result = true;
            }
        }
        else if (m_dir == Left) {
            if (spr->check_collision(m_frame, m_x, m_y,
                                     0,
                                     get_attribute("attack_low_top"),
                                     get_attribute("attack_left"),
                                     get_attribute("attack_low_bottom"),
                                     actor->get_sprite(), actor->get_frame(),
                                     actor->get_x(), actor->get_y())) {
                result = true;
            }
        }
    }

    return result;
}

void Knight::move(Map *map)
{
    int input = get_input();

    Player::move(map);

    // Handle attack
    if (m_attack != AttackNone) {
        if (m_attack_timer.expired(get_attribute("attack_time"))) {
            reset_attack();
        }
    }
    else if (m_hit == HitNone && !get_invisible()) {
        if (input & PRESS_ATTACK) {
            if (m_attack_ready) {
                m_attack_ready = false;

                // Attack
                set_attack();
            }
        }
        else {
            m_attack_ready = true;
        }
    }
}


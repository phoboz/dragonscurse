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
            if (m_frame == get_attribute("right_attack") &&
                spr->check_collision(m_frame, m_x, m_y,
                                     get_attribute("attack_right"),
                                     get_attribute("attack_medium_top"),
                                     spr->get_width(),
                                     get_attribute("attack_medium_bottom"),
                                     actor->get_sprite(), actor->get_frame(),
                                     actor->get_x(), actor->get_y(),
                                     actor->get_attribute("weak_left"),
                                     actor->get_attribute("weak_top"),
                                     actor->get_attribute("weak_right"),
                                     actor->get_attribute("weak_bottom"))) {
                result = true;
            }
        }
        else if (m_dir == Left) {
            if (m_frame == get_attribute("left_attack") &&
                spr->check_collision(m_frame, m_x, m_y,
                                     0,
                                     get_attribute("attack_medium_top"),
                                     get_attribute("attack_left"),
                                     get_attribute("attack_medium_bottom"),
                                     actor->get_sprite(), actor->get_frame(),
                                     actor->get_x(), actor->get_y(),
                                     actor->get_attribute("weak_left"),
                                     actor->get_attribute("weak_top"),
                                     actor->get_attribute("weak_right"),
                                     actor->get_attribute("weak_bottom"))) {
                result = true;
            }
        }
    }
    else if (m_attack == AttackLow) {
        if (m_dir == Right) {
            if (m_frame == get_attribute("right_attack_low") &&
                spr->check_collision(m_frame, m_x, m_y,
                                     get_attribute("attack_right"),
                                     get_attribute("attack_low_top"),
                                     spr->get_width(),
                                     get_attribute("attack_low_bottom"),
                                     actor->get_sprite(), actor->get_frame(),
                                     actor->get_x(), actor->get_y(),
                                     actor->get_attribute("weak_left"),
                                     actor->get_attribute("weak_top"),
                                     actor->get_attribute("weak_right"),
                                     actor->get_attribute("weak_bottom"))) {
                result = true;
            }
        }
        else if (m_dir == Left) {
            if (m_frame == get_attribute("left_attack_low") &&
                spr->check_collision(m_frame, m_x, m_y,
                                     0,
                                     get_attribute("attack_low_top"),
                                     get_attribute("attack_left"),
                                     get_attribute("attack_low_bottom"),
                                     actor->get_sprite(), actor->get_frame(),
                                     actor->get_x(), actor->get_y(),
                                     actor->get_attribute("weak_left"),
                                     actor->get_attribute("weak_top"),
                                     actor->get_attribute("weak_right"),
                                     actor->get_attribute("weak_bottom"))) {
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
                m_media->play_sound(get_string("strike"));
                set_attack();
            }
        }
        else {
            m_attack_ready = true;
        }
    }
}


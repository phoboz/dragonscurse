#include <string.h>
#include "phoboz/ctrl.h"
#include "knight.h"

bool Knight::attack_object(Object *object)
{
    bool result = false;
    const Sprite *spr = get_sprite();

    if (m_action == MediumAttack) {
        if (m_dir == Right) {
            if (m_frame == get_attribute("right_attack") &&
                object->check_weak_collision(
                    this,
                    get_attribute("attack_right"),
                    get_attribute("attack_medium_top"),
                    spr->get_width(),
                    get_attribute("attack_medium_bottom"))) {
                result = true;
            }
        }
        else if (m_dir == Left) {
            if (m_frame == get_attribute("left_attack") &&
                object->check_weak_collision(
                    this,
                    0,
                    get_attribute("attack_medium_top"),
                    get_attribute("attack_left"),
                    get_attribute("attack_medium_bottom"))) {
                result = true;
            }
        }
    }
    else if (m_action == LowAttack) {
        if (m_dir == Right) {
            if (m_frame == get_attribute("right_attack_low") &&
                object->check_weak_collision(
                    this,
                    get_attribute("attack_right"),
                    get_attribute("attack_low_top"),
                    spr->get_width(),
                    get_attribute("attack_low_bottom"))) {
                result = true;
            }
        }
        else if (m_dir == Left) {
            if (m_frame == get_attribute("left_attack_low") &&
                object->check_weak_collision(
                    this,
                    0,
                    get_attribute("attack_low_top"),
                    get_attribute("attack_left"),
                    get_attribute("attack_low_bottom"))) {
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
    if (m_action == MediumAttack || m_action == LowAttack) {
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


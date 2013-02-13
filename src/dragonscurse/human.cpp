#include <iostream>
#include <string.h>
#include "phoboz/ctrl.h"
#include "human.h"

void Human::move(Map *map)
{
    int input = get_input();

    Player::move(map);

    // Handle attack
    if (m_action == Attack || m_action == AttackLow) {
        if (m_attack_timer.expired(get_attribute("attack_time"))) {
            reset_attack();
        }
    }
    else {
        if (input & PRESS_ATTACK) {
            if (m_attack_ready) {
                m_attack_ready = false;
#if 0
                int y;
                if (m_action == Crouch) {
                    y = get_attribute("attack_low");
                }
                else {
                    y = get_attribute("attack_medium");
                }
#endif

                // Attack
                set_attack();
            }
        }
        else {
            m_attack_ready = true;
        }
    }
}


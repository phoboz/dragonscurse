#include <iostream>
#include <string.h>
#include "phoboz/ctrl.h"
#include "human.h"

Human::Human(const char *fn, int x, int y, Direction dir)
        : Player(fn, x, y, dir),
          m_attack_ready(true)
{
}

void Human::move(Map *map)
{
    int input = get_input();

    Player::move(map);

    // Handle attack
    if (m_action == Attack || m_action == AttackLow) {
        if (++m_attack_counter == get_attribute("attack_time")) {
            m_attack_counter = 0;
            reset_attack();
        }
    }
    else {
        if (input & PRESS_ATTACK) {
            if (m_attack_ready) {
                m_attack_ready = false;
                m_attack_counter = 0;
                int y;
                if (m_action == Crouch) {
                    y = get_attribute("attack_low");
                }
                else {
                    y = get_attribute("attack_medium");
                }

                if (m_dir == Right) {
                    set_attack();
                }
                else if (m_dir == Left) {
                    set_attack();
                }
            }
        }
        else {
            m_attack_ready = true;
        }
    }
}


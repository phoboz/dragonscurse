#include <string.h>
#include "phoboz/ctrl.h"
#include "knight.h"

bool Knight::attack_object(Object *object)
{
    bool result = false;

    if (m_action == Attack || m_action == AttackLow) {
        result = check_attack_collision(object);
    }

    return result;
}

void Knight::move(Map *map)
{
    int input = get_input();

    Player::move(map);

    // Handle attack
    if (m_action == Attack || m_action == AttackLow) {
        if (animate_attack()) {
            reset_attack();
        }
    }
    else if (!get_invisible()) {
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


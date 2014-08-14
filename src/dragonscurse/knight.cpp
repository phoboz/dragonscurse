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

    if (m_action != Hit && m_action != HitPerish) {
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


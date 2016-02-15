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

bool Knight::check_attack(int input)
{
    int result = false;

    if (m_action != Hit && m_action != HitPerish) {
        if (input & PRESS_ATTACK) {
            if (m_attack_ready) {
                m_attack_ready = false;

                // Attack
                m_media->play_sound(get_string("strike"));
                set_attack();
                result = true;
            }
        }
        else {
            m_attack_ready = true;
        }
    }

    return result;
}

bool Knight::check_break_rock(int *x, int *y, Map *map)
{
    bool result = false;

    if (m_create_rock_timer.check(c_rock_timeout)) {
        const Tmx::Tileset *tileset = map->get_tileset(0);
        const Tmx::PropertySet prop = tileset->GetProperties();
        int rockid = prop.GetNumericProperty("rock");

        if (rockid && check_attack_collision(x, y, map, rockid, rockid)) {
            map->set_tile_id(*x, *y, 0, prop.GetNumericProperty("rock_broken"));
            m_break_rock_timer.reset();
            result = true;
        }
    }

    return result;
}

bool Knight::check_create_rock(Map *map)
{
    int x, y;
    bool result = false;

    if (m_break_rock_timer.check(c_rock_timeout)) {
        const Tmx::Tileset *tileset = map->get_tileset(0);
        const Tmx::PropertySet prop = tileset->GetProperties();
        int rockid = prop.GetNumericProperty("create_rock");

        if (rockid && check_attack_collision(&x, &y, map, rockid, rockid)) {
            map->set_tile_id(x, y, 0, prop.GetNumericProperty("rock"));
            m_create_rock_timer.reset();
            result = true;
        }
    }

    return result;
}

void Knight::move(Map *map)
{
    int input = get_input();

    Player::move(map);
    check_attack(input);
}


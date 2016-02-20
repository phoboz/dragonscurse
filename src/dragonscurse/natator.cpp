#include <iostream>
#include "phoboz/ctrl.h"
#include "natator.h"

bool Natator::in_water(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if under water
    int start = prop.GetNumericProperty("water_start");
    int end = prop.GetNumericProperty("water_end");
    if (check_center(map, start, end)) {
        result = true;
    }

    return result;
}

bool Natator::set_hit(Object *object, Status *status)
{
    m_swimming = false;
    bool result = Player::set_hit(object, status);

    return result;
}

void Natator::move_swim(Map *map)
{
    Actor::move(map);
    Body::move(map);
}

void Natator::move(Map *map)
{

    if (m_swimming) {
        move_swim(map);
    }
    else {
        if (in_water(map)) {
            // TODO: Shall we also start to swim after hit above seafloor
            if (m_action == Jump || m_action == Fall) {
                if (get_input() & PRESS_JUMP) {
std::cout << "Enter swim" << std::endl;
                    m_swimming = true;
                }
            }
        }
        Knight::move(map);
    }
}


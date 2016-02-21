#include <iostream>
#include "phoboz/ctrl.h"
#include "natator.h"

void Natator::set_swim_dir(Direction set_dir)
{
    switch(m_action) {
        case Still:
            if (set_dir == Right) {
                m_frame = get_attribute("right_still");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("left_still");
            }
            break;

        case Attack:
            if (set_dir == Right) {
                if (m_frame < get_attribute("right_attack_start") ||
                    m_frame > get_attribute("right_attack_end")) {
                    m_frame = get_attribute("right_attack_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("left_attack_start") ||
                    m_frame > get_attribute("left_attack_end")) {
                    m_frame = get_attribute("left_attack_start");
                }
            }
            break;

        default:
            if (set_dir == Right) {
                if (m_frame < get_attribute("right_swim_start") ||
                    m_frame > get_attribute("right_swim_end")) {
                    m_frame = get_attribute("right_swim_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("left_swim_start") ||
                    m_frame > get_attribute("left_swim_end")) {
                    m_frame = get_attribute("left_swim_start");
                }
            }
            break;
    }
}

void Natator::set_dir(Direction dir)
{
    if (!m_swimming) {
        Knight::set_dir(dir);
    }
    else {
        Body::set_dir(dir);
        dir = m_dir;
        set_swim_dir(dir);
    }
}

bool Natator::set_hit(Object *object, Status *status)
{
    m_swimming = false;
    bool result = Player::set_hit(object, status);

    return result;
}

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

void Natator::animate_swim()
{
    switch(m_dir) {
        case Right:
            if (m_frame == get_attribute("right_swim_start")) {
                m_frame = get_attribute("right_swim_end");
            }
            else {
                m_frame = get_attribute("right_swim_start");
            }
            break;

        case Left:
            if (m_frame == get_attribute("left_swim_start")) {
                m_frame = get_attribute("left_swim_end");
            }
            else {
                m_frame = get_attribute("left_swim_start");
            }
            break;

        default:
            break;
    }
}

void Natator::move_swim(Map *map)
{
    int input = get_input();

    Body::move(map);

    if (input & PRESS_RIGHT) {
        set_dir(Right);
        set_vx(get_attribute("move_speed"));
    }
    else if (input & PRESS_LEFT) {
        set_dir(Left);
        set_vx(-get_attribute("move_speed"));
    }
    else {
        set_vx(0);
    }

    if (m_swim_timer.check(get_attribute("swim_treshold"))) {
        if (input & PRESS_JUMP) {
            animate_swim();
            set_vy(-get_attribute("swim_speed"));
            m_swim_timer.reset();
        }
    }

    if (m_action == Fall && hit_ground(map)) {
        m_swimming = false;
    }

    Actor::move(map);
}

void Natator::move(Map *map)
{
    int input = get_input();

    if (m_swimming) {
        if (in_water(map)) {
            move_swim(map);
        }

        if (check_attack(input)) {
            set_dir(m_dir);
        }
        else {
            m_swimming = false;
        }
    }
    else {
        if (in_water(map)) {
            if (m_action == Fall) {
                if (input & PRESS_JUMP) {
                    m_swimming = true;
                }
            }
        }
        Knight::move(map);
    }
}


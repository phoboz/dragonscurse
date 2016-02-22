#include "phoboz/ctrl.h"
#include "flyer.h"

void Flyer::set_rise_dir(Direction set_dir)
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
                if (m_frame < get_attribute("right_rise_start") ||
                    m_frame > get_attribute("right_rise_end")) {
                    m_frame = get_attribute("right_rise_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("left_rise_start") ||
                    m_frame > get_attribute("left_rise_end")) {
                    m_frame = get_attribute("left_rise_start");
                }
            }
            break;
    }
}

void Flyer::set_dir(Direction dir)
{
    if (!m_flying) {
        Knight::set_dir(dir);
    }
    else {
        Body::set_dir(dir);
        dir = m_dir;
        set_rise_dir(dir);
    }
}

bool Flyer::set_hit(Object *object, Status *status)
{
    m_flying = false;
    bool result = Player::set_hit(object, status);

    return result;
}

void Flyer::animate_rise()
{
    switch(m_dir) {
        case Right:
            if (++m_frame > get_attribute("right_rise_end")) {
                m_frame = get_attribute("right_rise_start");
            }
            break;

        case Left:
            if (++m_frame > get_attribute("left_rise_end")) {
                m_frame = get_attribute("left_rise_start");
            }
            break;

        default:
            break;
    }
}

void Flyer::move_fly(Map *map)
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

    if (m_rise_timer.check(get_attribute("rise_treshold"))) {
        if (input & PRESS_JUMP) {
            animate_rise();
            set_vy(-get_attribute("rise_speed"));
            m_rise_timer.reset();
        }
    }

    if (m_action == Fall && hit_ground(map)) {
        m_flying = false;
    }

    Actor::move(map);
}

void Flyer::move(Map *map)
{
    int input = get_input();

    if (m_flying) {
        move_fly(map);

        if (check_attack(input)) {
            m_flying = false;
            set_dir(m_dir);
        }

        if (!in_medium(map)) {
            m_flying = false;
        }
    }
    else {
        if (in_medium(map)) {
            if (m_action == Fall) {
                if (input & PRESS_JUMP) {
                    m_flying = true;
                }
            }
        }
        Knight::move(map);
    }
}


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
    if (m_flying) {
        Body::set_dir(dir);
        dir = m_dir;
        set_rise_dir(dir);
    }
    else {
        Knight::set_dir(dir);
    }
}

bool Flyer::set_hit(Object *object, Status *status, Map *map)
{
    m_flying = false;
    m_fly_ready = false;
    bool result = Player::set_hit(object, status, map);

    return result;
}

void Flyer::animate_rise()
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
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
}

void Flyer::move_fly(Map *map, int input)
{
    Body::move(map);
    if (get_fall()) {
        set_action(Fall);
    }
    else {
        animate_rise();
    }

    if (input & PRESS_RIGHT) {
        set_dir(Right);
        set_vx(get_move_speed(map));
    }
    else if (input & PRESS_LEFT) {
        set_dir(Left);
        set_vx(-get_move_speed(map));
    }
    else {
        set_vx(0);
    }

    if (m_rise_timer.check(get_attribute("rise_treshold"))) {
        if (input & PRESS_JUMP) {
            set_action(Jump);
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
        move_fly(map, input);

        if (check_attack(input)) {
            m_flying = false;
            m_fly_ready = false;
            set_dir(m_dir);
        }

        if (!in_medium(map)) {
            m_flying = false;
        }
    }
    else {
        if (hit_ground(map)) {
            m_fly_ready = true;
        }

        if (in_medium(map)) {
            if (m_action == Fall) {
                if (m_fly_ready && input & PRESS_JUMP) {
                    m_flying = true;
                }
            }
        }
        Knight::move(map);
    }
}


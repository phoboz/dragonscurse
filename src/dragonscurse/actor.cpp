#include "actor.h"

bool Actor::set_move_dir(Direction dir)
{
    if (dir == Keep || (m_action == Move && dir == m_dir)) {
        m_action = Move;
        return false;
    }

    m_anim_dir = AnimUp;
    switch(dir) {
        case Right:
            m_frame = get_attribute("right_move_start");
            m_dir = dir;
            break;

        case Left:
            m_frame = get_attribute("left_move_start");
            m_dir = dir;
            break;

        default:
            return false;
    }
    m_action = Move;

    return true;
}

void Actor::swap_move_dir()
{
    switch(m_dir) {
        case Right:
            set_move_dir(Left);
            break;

        case Left:
            set_move_dir(Right);
            break;

        default:
            break;
    }
}

void Actor::set_still_instant()
{
    switch(m_dir) {
        case Right:
            m_frame = get_attribute("right_still");
            break;

        case Left:
            m_frame = get_attribute("left_still");
            break;

        default:
            break;
    }
    m_action = Still;
}

bool Actor::set_still(void)
{
    bool done = false;

    if (m_anim_timer.expired(get_attribute("treshold"))) {
        m_anim_dir = AnimUp;
        set_still_instant();
        done = true;
    }

    return done;
}

void Actor::set_jump()
{
    switch(m_dir) {
        case Right:
            m_frame = get_attribute("right_jump");
            break;

        case Left:
            m_frame = get_attribute("left_jump");
            break;

        default:
            break;
    }
    m_action = Jump;
}

void Actor::set_crouch(void)
{
    switch(m_dir) {
        case Right:
            m_frame = get_attribute("right_crouch");
            break;

        case Left:
            m_frame = get_attribute("left_crouch");
            break;

        default:
            break;
    }
    m_action = Crouch;
}

void Actor::set_attack(void)
{
    switch(m_dir) {
        case Right:
            if (m_action == Crouch) {
                m_frame = get_attribute("right_attack_low");
                m_action = AttackLow;
            }
            else {
                m_frame = get_attribute("right_attack");
                m_action = Attack;
            }
            break;

        case Left:
            if (m_action == Crouch) {
                m_frame = get_attribute("left_attack_low");
                m_action = AttackLow;
            }
            else {
                m_frame = get_attribute("left_attack");
                m_action = Attack;
            }
            break;

        default:
            break;
    }
}

void Actor::reset_attack()
{
    if (m_action == AttackLow) {
        set_crouch();
    }
    else {
        set_still_instant();
    }
}

void Actor::check_ground(Map *map)
{
    m_dy = get_attribute("weight");
    check_below(map);
    if (m_dy) {
        m_action = Fall;
    }
    else if (m_action == Fall) {
        set_still();
    }
}

void Actor::animate_move()
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
        switch(m_dir) {
            case Right:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame == get_attribute("right_move_end")) {
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame == get_attribute("right_move_start")) {
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            case Left:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame == get_attribute("left_move_end")) {
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame == get_attribute("left_move_start")) {
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            default:
                break;
        }
    }
}

void Actor::face_reference()
{
    if (m_xref > m_x) {
        set_move_dir(Right);
    }
    else if (m_xref < m_x) {
        set_move_dir(Left);
    }
}

void Actor::set_hit(Object *object)
{
    if (m_action != Hit) {
        m_frame = get_attribute("hit");
        m_action = Hit;
    }
}


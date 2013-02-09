#include "actor.h"

bool Actor::set_move_dir(Direction dir)
{
    m_action = Move;

    if (dir == Keep || dir == m_dir) {
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

bool Actor::set_still(void)
{
    bool done = false;

    if (++m_counter == get_attribute("treshold")) {
        m_counter = 0;
        m_anim_dir = AnimUp;
        done = true;
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
            }
            else {
                m_frame = get_attribute("right_attack");
            }
            break;

        case Left:
            if (m_action == Crouch) {
                m_frame = get_attribute("left_attack_low");
            }
            else {
                m_frame = get_attribute("left_attack");
            }
            break;

        default:
            break;
    }
    m_action = Attack;
}

void Actor::animate_move()
{
    if (++m_counter == get_attribute("treshold")) {
        m_counter = 0;
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


#include "phoboz/actor.h"

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

bool Actor::set_still(void)
{
    bool done = false;

    if (++m_counter == get_attribute("treshold")) {
        m_counter = 0;
        m_anim_dir = AnimUp;
        m_action = Still;
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
    }

    return done;
}

void Actor::set_jump()
{
    m_action = Jump;
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
}

void Actor::set_crouch(void)
{
    m_action = Crouch;
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


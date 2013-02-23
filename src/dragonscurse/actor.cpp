#include "actor.h"

bool Actor::set_move_dir(Direction dir)
{
    Direction set_dir;

    if (dir == Keep) {
        set_dir = m_dir;
    }
    else {
        set_dir = dir;
    }

    if (m_action == Move && set_dir == m_dir) {
        m_action = Move;
        return false;
    }

    m_anim_dir = AnimUp;
    switch(set_dir) {
        case Right:
            m_frame = get_attribute("right_move_start");
            break;

        case Left:
            m_frame = get_attribute("left_move_start");
            break;

        default:
            return false;
    }
    m_dir = set_dir;
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

void Actor::set_still()
{
    if (m_attack == AttackNone) {
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
    else {
        switch(m_dir) {
            case Right:
                m_frame = get_attribute("right_attack");
                break;

            case Left:
                m_frame = get_attribute("left_attack");
                break;

            default:
                break;
        }
    }
    m_action = Still;
}

void Actor::set_fall()
{
    m_action = Fall;
}

void Actor::set_jump_dir(Direction dir)
{
    Direction set_dir;

    if (dir == Keep) {
        set_dir = m_dir;
    }
    else {
        set_dir = dir;
    }

    if (m_attack == AttackNone) {
        switch(set_dir) {
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
    else if (m_action != Jump) {
        switch(set_dir) {
            case Right:
                m_frame = get_attribute("right_attack");
                break;

            case Left:
                m_frame = get_attribute("left_attack");
                break;

            default:
                break;
        }
    }
    m_dir = set_dir;
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
                m_attack = AttackLow;
            }
            else {
                m_frame = get_attribute("right_attack");
                m_attack = AttackMedium;
            }
            break;

        case Left:
            if (m_action == Crouch) {
                m_frame = get_attribute("left_attack_low");
                m_attack = AttackLow;
            }
            else {
                m_frame = get_attribute("left_attack");
                m_attack = AttackMedium;
            }
            break;

        default:
            break;
    }
}

void Actor::reset_attack()
{
    Attack last_attack = m_attack;

    m_attack = AttackNone;
    if (last_attack == AttackLow) {
        set_crouch();
    }
    else {
        set_still();
    }
}

void Actor::check_ground(Map *map)
{
    if (m_action != Jump) {
        m_dy = get_attribute("weight");
        check_below(map);
        if (m_dy) {
            set_fall();
        }
        else if (m_action == Fall) {
            set_still();
        }
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

void Actor::set_invisible(bool invisible)
{
    if (invisible) {
        m_invisible_timer.reset();
    }

    m_invisible = invisible;
}

bool Actor::set_hit(Object *object)
{
    int result = false;

    if (!m_invisible) {
        m_frame = get_attribute("hit");
        m_action = Still;
        m_hit = HitOne;
        result = true;
    }

    return result;
}

void Actor::reset_hit()
{
    set_still();
    m_hit = HitNone;
}

int Actor::get_front()
{
    int result;

    switch(m_dir) {
        case Right:
            result = m_x + get_attribute("right");
            break;

        case Left:
            result = m_x + get_attribute("left");
            break;

        default:
            result = 0;
            break;
    }

    return result;
}

int Actor::get_bottom()
{
    return m_y + get_attribute("bottom");
}

void Actor::move(Map *map)
{
    if (m_invisible_timer.expired(get_attribute("invisible_time"))) {
        set_invisible(false);
    }
}

void Actor::draw(SDL_Surface *dest, Map *map,
                 int clip_x, int clip_y, int clip_w, int clip_h) {
    if (m_invisible) {
        if (m_blink_timer.expired(2)) {
            Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
        }
    }
    else {
        Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


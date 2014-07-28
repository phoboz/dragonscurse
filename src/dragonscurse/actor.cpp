#include "actor.h"

void Actor::set_action(Action action)
{
    if (m_action != action) {
        m_anim_dir = AnimUp;
        m_action = action;
        set_dir();
    }
}

void Actor::set_dir(Direction dir)
{
    Direction set_dir;

    if (dir == Keep) {
        set_dir = m_dir;
    }
    else {
        set_dir = dir;
    }

    switch(m_action) {
        case Still:
        case Fall:
            if (set_dir == Right) {
                m_frame = get_attribute("right_still");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("left_still");
            }
            break;

        case Move:
            if (set_dir != m_dir) {
                m_anim_dir = AnimUp;
                if (set_dir == Right) {
                    m_frame = get_attribute("right_move_start");
                }
                else if (set_dir == Left) {
                    m_frame = get_attribute("left_move_start");
                }
            }
            break;

        case Jump:
            if (set_dir == Right) {
                m_frame = get_attribute("right_jump");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("left_jump");
            }
            break;

        case Crouch:
            if (set_dir == Right) {
                m_frame = get_attribute("right_crouch");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("left_crouch");
            }
            break;

        case MediumAttack:
            if (set_dir == Right) {
                m_frame = get_attribute("right_attack");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("left_attack");
            }
            break;

        case LowAttack:
           if (set_dir == Right) {
                m_frame = get_attribute("right_attack_low");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("left_attack_low");
            }
            break;

        case Hit:
            if (set_dir == Right) {
                m_frame = get_attribute("right_hit");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("left_hit");
            }
            break;

        default:
            break;
    }

    m_dir = set_dir;
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

void Actor::set_attack(void)
{
    if (m_action == Crouch) {
        set_action(LowAttack);
    }
    else {
        set_action(MediumAttack);
    }
    set_vx(0);
}

void Actor::reset_attack()
{
    if (m_action == LowAttack) {
        set_action(Crouch);
    }
    else {
        set_action(Still);
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

Object::Direction Actor::get_reference() const
{
    Direction dir;

    if (m_xref > get_front()) {
        dir = Right;
    }
    else if (m_xref < get_front()) {
        dir = Left;
    }

    return dir;
}

void Actor::face_reference(int width)
{
    const Sprite *spr = get_sprite();
    int check_width;

    if (!width) {
        check_width = spr->get_width();
    }
    else {
        check_width = width;
    }

    if (abs(m_xref - get_front()) < check_width) {
        set_move_dir();
    }
    else if (m_xref > get_front()) {
        set_move_dir(Right);
    }
    else if (m_xref < get_front()) {
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
        set_action(Hit);
        m_hit = HitOne;
        result = true;
    }

    return result;
}

void Actor::reset_hit()
{
    set_action(Still);
    m_hit = HitNone;
}

void Actor::set_perish()
{
    set_invisible(true);
    switch(m_dir) {
        case Right:
            m_frame = get_attribute("right_perish");
            break;

        case Left:
            m_frame = get_attribute("left_perish");
            break;

        default:
            break;
    }
    m_hit = HitPerish;
}

bool Actor::check_weak_collision(Object *object, int x, int y) const
{
    bool result = false;
    const Sprite *spr = object->get_sprite();

    if (m_dir == Right) {
        result = spr->check_collision(object->get_frame(),
                                      object->get_x(),
                                      object->get_y(),
                                      get_sprite(), m_frame,
                                      m_x, m_y,
                                      get_attribute("right_weak_x1"),
                                      get_attribute("right_weak_y1"),
                                      get_attribute("right_weak_x2"),
                                      get_attribute("right_weak_y2"));
    }
    else if (m_dir == Left) {
        result = spr->check_collision(object->get_frame(),
                                      object->get_x(),
                                      object->get_y(),
                                      get_sprite(), m_frame,
                                      m_x, m_y,
                                      get_attribute("left_weak_x1"),
                                      get_attribute("left_weak_y1"),
                                      get_attribute("left_weak_x2"),
                                      get_attribute("left_weak_y2"));
    }

    return result;
}

bool Actor::check_weak_collision(Object *object,
                                 int start_x1, int start_y1,
                                 int end_x1, int end_y1) const
{
    bool result = false;
    const Sprite *spr = object->get_sprite();

    if (m_dir == Right) {
        result = spr->check_collision(object->get_frame(),
                                      object->get_x(),
                                      object->get_y(),
                                      start_x1, start_y1,
                                      end_x1, end_y1,
                                      get_sprite(), m_frame,
                                      m_x, m_y,
                                      get_attribute("right_weak_x1"),
                                      get_attribute("right_weak_y1"),
                                      get_attribute("right_weak_x2"),
                                      get_attribute("right_weak_y2"));
    }
    else if (m_dir == Left) {
        result = spr->check_collision(object->get_frame(),
                                      object->get_x(),
                                      object->get_y(),
                                      start_x1, start_y1,
                                      end_x1, end_y1,
                                      get_sprite(), m_frame,
                                      m_x, m_y,
                                      get_attribute("left_weak_x1"),
                                      get_attribute("left_weak_y1"),
                                      get_attribute("left_weak_x2"),
                                      get_attribute("left_weak_y2"));
    }

    return result;
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


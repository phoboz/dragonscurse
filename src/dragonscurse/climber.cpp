#include <iostream>
#include "phoboz/ctrl.h"
#include "climber.h"

void Climber::set_climb_above(Direction set_dir)
{
    switch(m_action) {
        case Attack:
            if (set_dir == Right) {
                if (m_frame < get_attribute("above_right_attack_start") ||
                    m_frame > get_attribute("above_right_attack_end")) {
                    m_frame = get_attribute("above_right_attack_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("above_left_attack_start") ||
                    m_frame > get_attribute("above_left_attack_end")) {
                    m_frame = get_attribute("above_left_attack_start");
                }
            }
            break;

        default:
            if (set_dir == Right) {
                if (m_frame < get_attribute("above_right_move_start") ||
                    m_frame > get_attribute("above_right_move_end")) {
                    m_anim_dir = AnimUp;
                    m_frame = get_attribute("above_right_move_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("above_left_move_start") ||
                    m_frame > get_attribute("above_left_move_end")) {
                    m_anim_dir = AnimUp;
                    m_frame = get_attribute("above_left_move_start");
                }
            }
            break;
    }
}

void Climber::set_climb_below(Direction set_dir)
{
    switch(m_action) {
        case Attack:
            if (set_dir == Right) {
                if (m_frame < get_attribute("below_right_attack_start") ||
                    m_frame > get_attribute("below_right_attack_end")) {
                    m_frame = get_attribute("below_right_attack_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("below_left_attack_start") ||
                    m_frame > get_attribute("below_left_attack_end")) {
                    m_frame = get_attribute("below_left_attack_start");
                }
            }
            break;

        default:
            if (set_dir == Right) {
                if (m_frame < get_attribute("below_right_move_start") ||
                    m_frame > get_attribute("below_right_move_end")) {
                    m_anim_dir = AnimUp;
                    m_frame = get_attribute("below_right_move_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("below_left_move_start") ||
                    m_frame > get_attribute("below_left_move_end")) {
                    m_anim_dir = AnimUp;
                    m_frame = get_attribute("below_left_move_start");
                }
            }
            break;
    }
}

void Climber::set_climb_right(Direction set_dir)
{
    switch(m_action) {
        case Attack:
            if (set_dir == Right) {
                if (m_frame < get_attribute("right_down_attack_start") ||
                    m_frame > get_attribute("right_down_attack_end")) {
                    m_frame = get_attribute("right_down_attack_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("right_up_attack_start") ||
                    m_frame > get_attribute("right_up_attack_end")) {
                    m_frame = get_attribute("right_up_attack_start");
                }
            }
            break;

        default:
            if (set_dir == Right) {
                if (m_frame < get_attribute("right_down_move_start") ||
                    m_frame > get_attribute("right_down_move_end")) {
                    m_anim_dir = AnimUp;
                    m_frame = get_attribute("right_down_move_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("right_up_move_start") ||
                    m_frame > get_attribute("right_up_move_end")) {
                    m_anim_dir = AnimUp;
                    m_frame = get_attribute("right_up_move_start");
                }
            }
            break;
    }
}

void Climber::set_climb_left(Direction set_dir)
{
    switch(m_action) {
        case Attack:
            if (set_dir == Right) {
                if (m_frame < get_attribute("left_up_attack_start") ||
                    m_frame > get_attribute("left_up_attack_end")) {
                    m_frame = get_attribute("left_up_attack_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("left_down_attack_start") ||
                    m_frame > get_attribute("left_down_attack_end")) {
                    m_frame = get_attribute("left_down_attack_start");
                }
            }
            break;

        default:
            if (set_dir == Right) {
                if (m_frame < get_attribute("left_up_move_start") ||
                    m_frame > get_attribute("left_up_move_end")) {
                    m_anim_dir = AnimUp;
                    m_frame = get_attribute("left_up_move_start");
                }
            }
            else if (set_dir == Left) {
                if (m_frame < get_attribute("left_down_move_start") ||
                    m_frame > get_attribute("left_down_move_end")) {
                    m_anim_dir = AnimUp;
                    m_frame = get_attribute("left_down_move_start");
                }
            }
            break;
    }
}

void Climber::set_dir(Direction dir)
{
    if (m_climb_dir == ClimbNone) {
        Knight::set_dir(dir);
    }
    else {
        Body::set_dir(dir);
        switch(m_climb_dir) {
            case ClimbAbove:
                set_climb_above(dir);
                break;

            case ClimbBelow:
                set_climb_below(dir);
                break;

            case ClimbRight:
                set_climb_right(dir);
                break;

            case ClimbLeft:
                set_climb_left(dir);
                break;

            default:
                break;

        }
    }
}

void Climber::animate_climb_above()
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
        switch(m_dir) {
            case Right:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame >= get_attribute("above_right_move_end")) {
                        m_frame = get_attribute("above_right_move_end");
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame <= get_attribute("above_right_move_start")) {
                        m_frame = get_attribute("above_right_move_start");
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            case Left:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame >= get_attribute("above_left_move_end")) {
                        m_frame = get_attribute("above_left_move_end");
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame <= get_attribute("above_left_move_start")) {
                        m_frame = get_attribute("above_left_move_start");
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            default:
                break;
        }
    }
}

void Climber::animate_climb_below()
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
        switch(m_dir) {
            case Right:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame >= get_attribute("below_right_move_end")) {
                        m_frame = get_attribute("below_right_move_end");
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame <= get_attribute("below_right_move_start")) {
                        m_frame = get_attribute("below_right_move_start");
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            case Left:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame >= get_attribute("below_left_move_end")) {
                        m_frame = get_attribute("below_left_move_end");
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame <= get_attribute("below_left_move_start")) {
                        m_frame = get_attribute("below_left_move_start");
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            default:
                break;
        }
    }
}

void Climber::animate_climb_right()
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
        switch(m_dir) {
            case Right:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame >= get_attribute("right_down_move_end")) {
                        m_frame = get_attribute("right_down_move_end");
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame <= get_attribute("right_down_move_start")) {
                        m_frame = get_attribute("right_down_move_start");
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            case Left:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame >= get_attribute("right_up_move_end")) {
                        m_frame = get_attribute("right_up_move_end");
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame <= get_attribute("right_up_move_start")) {
                        m_frame = get_attribute("right_up_move_start");
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            default:
                break;
        }
    }
}

void Climber::animate_climb_left()
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
        switch(m_dir) {
            case Right:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame >= get_attribute("left_up_move_end")) {
                        m_frame = get_attribute("left_up_move_end");
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame <= get_attribute("left_up_move_start")) {
                        m_frame = get_attribute("left_up_move_start");
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            case Left:
                if (m_anim_dir == AnimUp) {
                    if (++m_frame >= get_attribute("left_down_move_end")) {
                        m_frame = get_attribute("left_down_move_end");
                        m_anim_dir = AnimDown;
                    }
                }
                else if (m_anim_dir == AnimDown) {
                    if (--m_frame <= get_attribute("left_down_move_start")) {
                        m_frame = get_attribute("left_down_move_start");
                        m_anim_dir = AnimUp;
                    }
                }
                break;

            default:
                break;
        }
    }
}

void Climber::animate_climb()
{
    switch(m_climb_dir) {
        case ClimbAbove:
            animate_climb_above();
            break;

        case ClimbBelow:
            animate_climb_below();
            break;

        case ClimbRight:
            animate_climb_right();
            break;

        case ClimbLeft:
            animate_climb_left();
            break;

        default:
            break;

    }
}

bool Climber::animate_attack_above()
{
    bool result = false;

    if (m_anim_timer.expired(get_attribute("attack_treshold"))) {
        switch(m_dir) {
            case Right:
                if (++m_frame >= get_attribute("above_right_attack_end")) {
                    m_frame = get_attribute("above_right_attack_end");
                    result = true;
                }
                break;

            case Left:
                if (++m_frame >= get_attribute("above_left_attack_end")) {
                    m_frame = get_attribute("above_left_attack_end");
                    result = true;
                }
                break;

            default:
                break;
        }
    }

    return result;
}

bool Climber::animate_attack_below()
{
    bool result = false;

    if (m_anim_timer.expired(get_attribute("attack_treshold"))) {
        switch(m_dir) {
            case Right:
                if (++m_frame >= get_attribute("below_right_attack_end")) {
                    m_frame = get_attribute("below_right_attack_end");
                    result = true;
                }
                break;

            case Left:
                if (++m_frame >= get_attribute("below_left_attack_end")) {
                    m_frame = get_attribute("below_left_attack_end");
                    result = true;
                }
                break;

            default:
                break;
        }
    }

    return result;
}

bool Climber::animate_attack_right()
{
    bool result = false;

    if (m_anim_timer.expired(get_attribute("attack_treshold"))) {
        switch(m_dir) {
            case Right:
                if (++m_frame >= get_attribute("right_down_attack_end")) {
                    m_frame = get_attribute("right_down_attack_end");
                    result = true;
                }
                break;

            case Left:
                if (++m_frame >= get_attribute("right_up_attack_end")) {
                    m_frame = get_attribute("right_up_attack_end");
                    result = true;
                }
                break;

            default:
                break;
        }
    }

    return result;
}

bool Climber::animate_attack_left()
{
    bool result = false;

    if (m_anim_timer.expired(get_attribute("attack_treshold"))) {
        switch(m_dir) {
            case Right:
                if (++m_frame >= get_attribute("left_up_attack_end")) {
                    m_frame = get_attribute("left_up_attack_end");
                    result = true;
                }
                break;

            case Left:
                if (++m_frame >= get_attribute("left_down_attack_end")) {
                    m_frame = get_attribute("left_down_attack_end");
                    result = true;
                }
                break;

            default:
                break;
        }
    }

    return result;
}

bool Climber::animate_attack()
{
    bool result;

    switch(m_climb_dir) {
        case ClimbAbove:
            result = animate_attack_above();
            break;

        case ClimbBelow:
            result = animate_attack_below();
            break;

        case ClimbRight:
            result = animate_attack_right();
            break;

        case ClimbLeft:
            result = animate_attack_left();
            break;

        default:
            result = Actor::animate_attack();
            break;
    }

    return result;
}

void Climber::enter_climb(ClimbDir dir)
{
    set_vx(0);
    set_ay(0);
    m_leave_ready = false;
    m_climb_dir = dir;
    set_dir(Left);
}

void Climber::leave_climb(Map *map)
{
#if 0
    switch (m_climb_dir) {
        case ClimbRight:
            set_vx(-get_attribute("move_speed"));
            break;

        case ClimbLeft:
            set_vx(get_attribute("move_speed"));
            break;

        default:
            break;
    }
#endif

    m_climb_dir = ClimbNone;
    set_vy(0);
    Player::set_jump(map);
}

int Climber::check_climb(Map *map, int len)
{
    int result = 0;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (m_climb_dir == ClimbAbove) {
        int bottom = get_attribute("climb_above_bottom") + 1;

        if (m_dir == Right) {
            int right = get_attribute("climb_above_right");
            int dx;
            for (dx = len; dx > 0; dx--) {
                if (check_collision(m_x + right + dx, m_y + bottom,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dx;
        }
        else if (m_dir == Left) {
            int left = get_attribute("climb_above_left");
            int dx;
            for (dx = len; dx > 0; dx--) {
                if (check_collision(m_x + left - dx, m_y + bottom,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dx;
        }
    }
    else if (m_climb_dir == ClimbBelow) {
        int top = get_attribute("climb_below_top") - 1;

        if (m_dir == Right) {
            int right = get_attribute("climb_below_right");
            int dx;
            for (dx = len; dx > 0; dx--) {
                if (check_collision(m_x + right + dx, m_y + top,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dx;
        }
        else if (m_dir == Left) {
            int left = get_attribute("climb_below_left");
            int dx;
            for (dx = len; dx > 0; dx--) {
                if (check_collision(m_x + left - dx, m_y + top,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dx;
        }
    }
    else if (m_climb_dir == ClimbRight) {
        int right = get_attribute("climb_right_right") + 1;

        if (m_dir == Right) {
            int bottom = get_attribute("climb_right_bottom");
            int dy;
            for (dy = len; dy > 0; dy--) {
                if (check_collision(m_x + right, m_y + bottom + dy,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dy;
        }
        else if (m_dir == Left) {
            int top = get_attribute("climb_right_top");
            int dy;
            for (dy = len; dy > 0; dy--) {
                if (check_collision(m_x + right, m_y + top - dy,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dy;
        }
    }
    else if (m_climb_dir == ClimbLeft) {
        int left = get_attribute("climb_left_left") - 1;

        if (m_dir == Right) {
            int bottom = get_attribute("climb_left_bottom");
            int dy;
            for (dy = len; dy > 0; dy--) {
                if (check_collision(m_x + left, m_y + bottom + dy,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dy;
        }
        else if (m_dir == Left) {
            int top = get_attribute("climb_left_top");
            int dy;
            for (dy = len; dy > 0; dy--) {
                if (check_collision(m_x + left, m_y + top - dy,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dy;
        }
    }

    return result;
}

bool Climber::climb_turn_right(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (check_climb(map, 1) == 0) {
        if (check_collision(m_x + get_attribute("right") + 1,
                            m_y + get_attribute("bottom"),
                            map, block_id, block_id)) {
            enter_climb(ClimbAbove);
            m_x += 32;
            m_y -= 32;
            result = true;
        }
        else if (check_collision(m_x + get_attribute("right") + 1,
                                 m_y + get_attribute("top"),
                                 map, block_id, block_id)) {
            enter_climb(ClimbBelow);
            m_x += 32;
            m_y += 5;
            result = true;
        }
    }

    return result;
}

void Climber::move_climb(Map *map, int input)
{
    if (!m_leave_ready && m_leave_timer.expired(c_leave_time)) {
        m_leave_ready = true;
    }

    if (input & PRESS_JUMP) {
        if (m_leave_ready) {
            leave_climb(map);
        }
    }
    else {
        switch(m_climb_dir) {
            case ClimbAbove:
                if (input & PRESS_RIGHT) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Right);
                    set_vx(check_climb(map, get_attribute("move_speed")));
                }
                else if (input & PRESS_LEFT) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Left);
                    set_vx(-check_climb(map, get_attribute("move_speed")));
                }
                else {
                    animate_climb();
                    set_dir(Keep);
                    set_action(Still);
                    set_vx(0);
                }
                break;

            case ClimbBelow:
                if (input & PRESS_RIGHT) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Right);
                    set_vx(check_climb(map, get_attribute("move_speed")));
                }
                else if (input & PRESS_LEFT) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Left);
                    set_vx(-check_climb(map, get_attribute("move_speed")));
                }
                else {
                    animate_climb();
                    set_dir(Keep);
                    set_action(Still);
                    set_vx(0);
                }
                break;

            case ClimbRight:
                if (input & PRESS_DOWN) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Right);
                    set_vy(check_climb(map, get_attribute("move_speed")));
                }
                else if (input & PRESS_UP) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Left);
                    set_vy(-check_climb(map, get_attribute("move_speed")));
                }
                else if (input & PRESS_RIGHT) {
                    if (m_leave_ready) {
                        if (climb_turn_right(map)) {
                            set_vy(0);
                        }
                    }
                }
                else {
                    animate_climb();
                    set_dir(Keep);
                    set_action(Still);
                    set_vy(0);
                }
                break;

            case ClimbLeft:
                if (input & PRESS_DOWN) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Right);
                    set_vy(check_climb(map, get_attribute("move_speed")));
                }
                else if (input & PRESS_UP) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Left);
                    set_vy(-check_climb(map, get_attribute("move_speed")));
                }
                else {
                    animate_climb();
                    set_dir(Keep);
                    set_action(Still);
                    set_vy(0);
                }
                break;
        }
    }

    Body::move(map);
}

void Climber::move(Map *map)
{
    int input = get_input();

    if (m_climb_dir == ClimbNone && (m_action == Jump || m_action == Fall)) {
        const Tmx::Tileset *tileset = map->get_tileset(0);
        const Tmx::PropertySet prop = tileset->GetProperties();

        // Check if on climb block
        int block_id = prop.GetNumericProperty("climb");
        if (block_id) {
            if (input & PRESS_DOWN) {
                if (check_below(map, 1, block_id, block_id) == 0) {
                    enter_climb(ClimbAbove);
std::cout << "climb above" << std::endl;
                }
            }
            else if (input & PRESS_UP) {
                if (check_above(map, 1, block_id, block_id) == 0) {
                    enter_climb(ClimbBelow);
std::cout << "climb below" << std::endl;
                }
            }
            else if (m_dir == Right && (input & PRESS_RIGHT)) {
                if (check_ahead(map, 1, block_id, block_id) == 0) {
                    enter_climb(ClimbRight);
std::cout << "climb right" << std::endl;
                }
            }
            else if (m_dir == Left && (input & PRESS_LEFT)) {
                if (check_ahead(map, 1, block_id, block_id) == 0) {
                    enter_climb(ClimbLeft);
std::cout << "climb left" << std::endl;
                }
            }
        }
    }

    if (m_climb_dir == ClimbNone) {
        Knight::move(map);
    }
    else {
        if (m_action == Attack) {
            if (animate_attack()) {
                reset_attack();
                set_dir(m_dir);
            }
        }
        else {
            move_climb(map, input);
            if (check_attack(input)) {
                set_dir(m_dir);
            }
        }
    }
}


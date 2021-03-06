#include "phoboz/ctrl.h"
#include "climber.h"

void Climber::set_climb_above(Direction set_dir)
{
    switch(m_action) {
        case Still:
            if (set_dir == Right) {
                m_frame = get_attribute("above_right_still");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("above_left_still");
            }
            break;

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
        case Still:
            if (set_dir == Right) {
                m_frame = get_attribute("below_right_still");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("below_left_still");
            }
            break;

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
        case Still:
            if (set_dir == Right) {
                m_frame = get_attribute("right_down_still");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("right_up_still");
            }
            break;

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
        case Still:
            if (set_dir == Right) {
                m_frame = get_attribute("left_up_still");
            }
            else if (set_dir == Left) {
                m_frame = get_attribute("left_down_still");
            }
            break;

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
        dir = m_dir;
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

void Climber::enter_climb(Map *map, ClimbDir dir, int x, int y)
{
    int block_x = x / map->get_tile_width();
    int block_y = y / map->get_tile_height();

    switch(dir) {
        case ClimbAbove:
            m_y = block_y * map->get_tile_height() +
                      get_attribute("climb_block_above");
            break;

        case ClimbBelow:
            m_y = block_y * map->get_tile_height() +
                      get_attribute("climb_block_below");
            break;

        case ClimbRight:
            m_x = block_x * map->get_tile_width() +
                      get_attribute("climb_block_right");
            break;

        case ClimbLeft:
            m_x = block_x * map->get_tile_width() +
                get_attribute("climb_block_left");
            break;

        default:
            break;
    }

    set_speed(0, 0);
    set_ay(0);
    m_leave_ready = false;
    m_climb_dir = dir;
    set_dir(Left);
}

void Climber::leave_climb(Map *map)
{
    if (m_climb_dir == ClimbRight) {
        set_vx(-get_move_speed(map));
    }
    else if (m_climb_dir == ClimbLeft) {
        set_vx(get_move_speed(map));
    }

    m_climb_dir = ClimbNone;
    set_vy(0);
}

int Climber::check_climb(Map *map, int len, Direction dir)
{
    int result = 0;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (dir == Keep) {
        dir = m_dir;
    }

    if (m_climb_dir == ClimbAbove) {
        int bottom = get_attribute("bottom") + 1;

        if (dir == Right) {
            int right = get_attribute("right");
            int dx;
            for (dx = len; dx > 0; dx--) {
                if (check_collision(m_x + right + dx, m_y + bottom,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dx;
        }
        else if (dir == Left) {
            int left = get_attribute("left");
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
        int top = get_attribute("top") - 1;

        if (dir == Right) {
            int right = get_attribute("right");
            int dx;
            for (dx = len; dx > 0; dx--) {
                if (check_collision(m_x + right + dx, m_y + top,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dx;
        }
        else if (dir == Left) {
            int left = get_attribute("left");
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
        int right = get_attribute("right") + 1;

        if (dir == Right) {
            int bottom = get_attribute("bottom");
            int dy;
            for (dy = len; dy > 0; dy--) {
                if (check_collision(m_x + right, m_y + bottom + dy,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dy;
        }
        else if (dir == Left) {
            int top = get_attribute("top");
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
        int left = get_attribute("left") - 1;

        if (dir == Right) {
            int bottom = get_attribute("bottom");
            int dy;
            for (dy = len; dy > 0; dy--) {
                if (check_collision(m_x + left, m_y + bottom + dy,
                                    map, block_id, block_id)) {
                    break;
                }
            }
            result = dy;
        }
        else if (dir == Left) {
            int top = get_attribute("top");
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

bool Climber::climb_above_turn_up(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (check_left(map, 1) == 0) {
        int x = m_x + get_attribute("left") - 1;
        int y = m_y + get_attribute("bottom");
        if (check_collision(x, y, map, block_id, block_id)) {
            enter_climb(map, ClimbLeft, x, y);
            result = true;
        }
    }
    else if (check_right(map, 1) == 0) {
        int x = m_x + get_attribute("right") + 1;
        int y = m_y + get_attribute("bottom");
        if (check_collision(x, y, map, block_id, block_id)) {
            enter_climb(map, ClimbRight, x, y);
            result = true;
        }
    }

    return result;
}

bool Climber::climb_above_turn_down(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (check_climb(map, 1, Left) == 0) {
        int x = m_x + get_attribute("left");
        int y = m_y + get_attribute("bottom") + 1;
        if (check_collision(x, y, map, block_id, block_id) &&
            !check_collision(x - map->get_tile_width(), y, map)) {
            enter_climb(map, ClimbRight, x, y);
            m_y += map->get_tile_height();
            result = true;
        }
    }
    else if (check_climb(map, 1, Right) == 0) {
        int x = m_x + get_attribute("right");
        int y = m_y + get_attribute("bottom") + 1;
        if (check_collision(x, y, map, block_id, block_id) &&
            !check_collision(x + map->get_tile_width(), y, map)) {
            enter_climb(map, ClimbLeft, x, y);
            m_y += map->get_tile_height();
            result = true;
        }
    }

    return result;
}

bool Climber::climb_below_turn_up(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (check_climb(map, 1, Left) == 0) {
        int x = m_x + get_attribute("left");
        int y = m_y + get_attribute("top") - 1;
        if (check_collision(x, y, map, block_id, block_id) &&
            !check_collision(x - map->get_tile_width(), y, map)) {
            enter_climb(map, ClimbRight, x, y);
            m_y -= map->get_tile_height() / 2;
            result = true;
        }
    }
    else if (check_climb(map, 1, Right) == 0) {
        int x = m_x + get_attribute("right");
        int y = m_y + get_attribute("top") - 1;
        if (check_collision(x, y, map, block_id, block_id) &&
            !check_collision(x + map->get_tile_width(), y, map)) {
            enter_climb(map, ClimbLeft, x, y);
            m_y -= map->get_tile_height() / 2;
            result = true;
        }
    }

    return result;
}

bool Climber::climb_below_turn_down(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (check_left(map, 1) == 0) {
        int x = m_x + get_attribute("left") - 1;
        int y = m_y + get_attribute("bottom");
        if (check_collision(x, y, map, block_id, block_id)) {
            enter_climb(map, ClimbLeft, x, y);
            result = true;
        }
    }
    else if (check_right(map, 1) == 0) {
        int x = m_x + get_attribute("right") + 1;
        int y = m_y + get_attribute("bottom");
        if (check_collision(x, y, map, block_id, block_id)) {
            enter_climb(map, ClimbRight, x, y);
            result = true;
        }
    }

    return result;
}

bool Climber::climb_right_turn_right(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (check_climb(map, 1, Left) == 0) {
        int x = m_x + get_attribute("right") + 1;
        int y = m_y + get_attribute("bottom");
        if (check_collision(x, y, map, block_id, block_id) &&
            !check_collision(x, y - map->get_tile_height(), map)) {
            enter_climb(map, ClimbAbove, x, y);
            m_x += map->get_tile_width() / 2;
            result = true;
        }
    }
    else if (check_climb(map, 1, Right) == 0) {
        int x = m_x + get_attribute("right") + 1;
        int y = m_y + get_attribute("top");
        if (check_collision(x, y, map, block_id, block_id) &&
            !check_collision(x, y + map->get_tile_height(), map)) {
            enter_climb(map, ClimbBelow, x, y);
            m_x += map->get_tile_width() / 2;
            result = true;
        }
    }

    return result;
}

bool Climber::climb_right_turn_left(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (check_above(map, 1) == 0) {
        int x = m_x + get_attribute("left");
        int y = m_y + get_attribute("top") - 1;
        if (check_collision(x, y, map, block_id, block_id)) {
            enter_climb(map, ClimbBelow, x, y);
            result = true;
        }
    }

    if (check_below(map, 1) == 0) {
        int x = m_x + get_attribute("left");
        int y = m_y + get_attribute("bottom") + 1;
            if (check_collision(x, y, map, block_id, block_id)) {
                enter_climb(map, ClimbAbove, x, y);
                result = true;
            }
    }

    return result;
}

bool Climber::climb_left_turn_right(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (check_above(map, 1) == 0) {
        int x = m_x + get_attribute("right");
        int y = m_y + get_attribute("top") - 1;
        if (check_collision(x, y, map, block_id, block_id)) {
            enter_climb(map, ClimbBelow, x, y);
            result = true;
        }
    }

    if (check_below(map, 1) == 0) {
        int x = m_x + get_attribute("right");
        int y = m_y + get_attribute("bottom") + 1;
            if (check_collision(x, y, map, block_id, block_id)) {
                enter_climb(map, ClimbAbove, x, y);
                result = true;
            }
    }

    return result;
}

bool Climber::climb_left_turn_left(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();
    int block_id = prop.GetNumericProperty("climb");

    if (check_climb(map, 1, Left) == 0) {
        int x = m_x + get_attribute("left") - 1;
        int y = m_y + get_attribute("bottom");
        if (check_collision(x, y, map, block_id, block_id) &&
            !check_collision(x, y - map->get_tile_height(), map)) {
            enter_climb(map, ClimbAbove, x, y);
            m_x -= map->get_tile_width() / 2;
            result = true;
        }
    }
    else if (check_climb(map, 1, Right) == 0) {
        int x = m_x + get_attribute("left") - 1;
        int y = m_y + get_attribute("top");
            if (check_collision(x, y, map, block_id, block_id) &&
            !check_collision(x, y + map->get_tile_height(), map)) {
                enter_climb(map, ClimbBelow, x, y);
                m_x -= map->get_tile_width() / 2;
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
            Player::set_jump(map);
        }
    }
    else {
        switch(m_climb_dir) {
            case ClimbAbove:
                if (input & PRESS_RIGHT) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Right);
                    set_vx(check_climb(map, get_move_speed(map)));
                }
                else if (input & PRESS_LEFT) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Left);
                    set_vx(-check_climb(map, get_move_speed(map)));
                }
                else if (input & PRESS_UP) {
                    if (m_leave_ready) {
                        climb_above_turn_up(map);
                    }
                    set_action(Still);
                    set_dir(Keep);
                    set_vx(0);
                }
                else if (input & PRESS_DOWN) {
                    if (m_leave_ready) {
                        climb_above_turn_down(map);
                    }
                    set_action(Still);
                    set_dir(Keep);
                    set_vx(0);
                }
                else {
                    set_action(Still);
                    set_dir(Keep);
                    set_vx(0);
                }
                break;

            case ClimbBelow:
                if (input & PRESS_RIGHT) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Right);
                    set_vx(check_climb(map, get_move_speed(map)));
                }
                else if (input & PRESS_LEFT) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Left);
                    set_vx(-check_climb(map, get_move_speed(map)));
                }
                else if (input & PRESS_UP) {
                    if (m_leave_ready) {
                        climb_below_turn_up(map);
                    }
                    set_action(Still);
                    set_dir(Keep);
                    set_vx(0);
                }
                else if (input & PRESS_DOWN) {
                    if (m_leave_ready) {
                        climb_below_turn_down(map);
                    }
                    set_action(Still);
                    set_dir(Keep);
                    set_vx(0);
                }
                else {
                    set_action(Still);
                    set_dir(Keep);
                    set_vx(0);
                }
                break;

            case ClimbRight:
                if (input & PRESS_DOWN) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Right);
                    set_vy(check_climb(map, get_move_speed(map)));
                }
                else if (input & PRESS_UP) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Left);
                    set_vy(-check_climb(map, get_move_speed(map)));
                }
                else if (input & PRESS_RIGHT) {
                    if (m_leave_ready) {
                        climb_right_turn_right(map);
                    }
                    set_action(Still);
                    set_dir(Keep);
                    set_vy(0);
                }
                else if (input & PRESS_LEFT) {
                    if (m_leave_ready) {
                        climb_right_turn_left(map);
                    }
                    set_action(Still);
                    set_dir(Keep);
                    set_vy(0);
                }
                else {
                    set_action(Still);
                    set_dir(Keep);
                    set_vy(0);
                }
                break;

            case ClimbLeft:
                if (input & PRESS_DOWN) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Right);
                    set_vy(check_climb(map, get_move_speed(map)));
                }
                else if (input & PRESS_UP) {
                    animate_climb();
                    set_action(Move);
                    set_dir(Left);
                    set_vy(-check_climb(map, get_move_speed(map)));
                }
                else if (input & PRESS_RIGHT) {
                    if (m_leave_ready) {
                        climb_left_turn_right(map);
                    }
                    set_action(Still);
                    set_dir(Keep);
                    set_vy(0);
                }
                else if (input & PRESS_LEFT) {
                    if (m_leave_ready) {
                        climb_left_turn_left(map);
                    }
                    set_action(Still);
                    set_dir(Keep);
                    set_vy(0);
                }
                else {
                    set_action(Still);
                    set_dir(Keep);
                    set_vy(0);
                }
                break;
        }
    }

    Body::move(map);
}

bool Climber::set_hit(Object *object, Status *status, Map *map)
{
    leave_climb(map);
    bool result = Player::set_hit(object, status, map);

    return result;
}

void Climber::move(Map *map)
{
    int input = get_input();

    if (m_climb_dir == ClimbNone) {
        Knight::move(map);

        if (m_action == Jump || m_action == Fall) {
            const Tmx::Tileset *tileset = map->get_tileset(0);
            const Tmx::PropertySet prop = tileset->GetProperties();

            // Check if on climb block
            int block_id = prop.GetNumericProperty("climb");
            if (block_id) {
                if (input & PRESS_DOWN) {
                    if (check_collision(m_x +
                                            get_attribute("climb_center_x"),
                                        m_y + get_attribute("bottom") + 1,
                                        map, block_id, block_id)) {
                        enter_climb(map, ClimbAbove,
                                    m_x, m_y + get_attribute("bottom") + 1);
                    }
                }
                else if (input & PRESS_UP) {
                    if (check_collision(m_x +
                                            get_attribute("climb_center_x"),
                                        m_y + get_attribute("top") - 1,
                                        map, block_id, block_id)) {
                        enter_climb(map, ClimbBelow,
                                    m_x, m_y + get_attribute("top") - 1);
                    }
                }
                else if (m_dir == Right && (input & PRESS_RIGHT)) {
                    if (check_collision(m_x + get_attribute("right") + 1,
                                        m_y + get_attribute("climb_center_y"),
                                        map, block_id, block_id)) {
                        enter_climb(map, ClimbRight,
                                    m_x + get_attribute("right") + 1, m_y);
                    }
                }
                else if (m_dir == Left && (input & PRESS_LEFT)) {
                    if (check_collision(m_x + get_attribute("left") - 1,
                                        m_y + get_attribute("climb_center_y"),
                                        map, block_id, block_id)) {
                        enter_climb(map, ClimbLeft,
                                    m_x + get_attribute("left") - 1, m_y);
                    }
                }
            }
        }
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
        Actor::move(map);
    }
}


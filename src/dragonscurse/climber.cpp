#include <iostream>
#include "phoboz/ctrl.h"
#include "climber.h"

void Climber::set_climb_right(Direction set_dir)
{
    switch(m_action) {
        case Still:
        case Move:
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
            break;
    }
}

void Climber::set_climb_left(Direction set_dir)
{
    switch(m_action) {
        case Still:
        case Move:
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

void Climber::move_climb(Map *map)
{
    int input = get_input();

    set_ay(0);
    switch (m_climb_dir) {
        case ClimbRight:
        case ClimbLeft:
            if (input & PRESS_DOWN) {
                animate_climb();
                set_action(Move);
                set_dir(Right);
                set_vy(get_attribute("move_speed"));
            }
            else if (input & PRESS_UP) {
                animate_climb();
                set_action(Move);
                set_dir(Left);
                set_vy(-get_attribute("move_speed"));
            }
            else {
                set_action(Still);
                set_vy(0);
            }
            break;

        default:
            break;
    }

    Body::move(map);
}

void Climber::move(Map *map)
{
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if on climb block
    int block_id = prop.GetNumericProperty("climb");
    if (block_id) {
        if (check_ahead(map, 1, block_id, block_id) == 0) {
            if (m_dir == Right) {
                m_climb_dir = ClimbRight;
            }
            else if (m_dir == Left) {
                m_climb_dir = ClimbLeft;
            }
        }
    }

    if (m_climb_dir == ClimbNone) {
        Knight::move(map);
    }
    else {
        move_climb(map);
    }
}


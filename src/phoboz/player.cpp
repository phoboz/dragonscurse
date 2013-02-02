#include <stdio.h>
#include <string.h>
#include "phoboz/ctrl.h"
#include "phoboz/player.h"

void Player::check(Map *map)
{
    int input = get_input();

    // Check ground
    if (m_action != Jump) {
        m_dy = get_attribute("weight");
        check_below(map);
        if (m_dy) {
            m_action = Fall;
        }
        else {
            if (m_action == Fall) {
                set_stand();
            }
        }
    }

    switch(m_action) {
        case Stand:
        case Walk:
            if (input & PRESS_RIGHT) {
                set_dir(Right);
                m_action = Walk;
                animate_walk();
                m_dx = get_attribute("walk_speed");
            }
            else if (input & PRESS_LEFT) {
                set_dir(Left);
                m_action = Walk;
                animate_walk();
                m_dx = get_attribute("walk_speed");
            }
            else if (m_action == Walk) {
                set_stand();
                m_dx = 0;
            }

            // Check for jump
            if (input & PRESS_SPACE) {
                if (m_jump_ready) {
                    m_jump_ready = false;
                    m_dy = get_attribute("jump_speed");
                    set_jump();
                }
            }
            else {
                m_jump_ready = true;

                // Check for crouch
                if (input & PRESS_DOWN) {
                    set_crouch();
                }
            }
            check_ahead(map);
            break;

        case Fall:
            // Below is already checked if action is not Jump
            check_ahead(map);
            break;

        case Jump:
            if (check_above(map)) {
                m_action = Fall;
                m_jump_counter = 0;
            }

            if (input & PRESS_RIGHT) {
                set_dir(Right);
                m_dx = get_attribute("walk_speed");
            }
            else if (input & PRESS_LEFT) {
                set_dir(Left);
                m_dx = get_attribute("walk_speed");
            }
            else {
                m_dx = 0;
            }

            // Check jump height
            if (++m_jump_counter == get_attribute("jump_limit")) {
                m_jump_counter = 0;
                m_action = Fall;
            }

            // Check horizontal direction
            check_ahead(map);
            break;

        case Crouch:
            if (!(input & PRESS_DOWN)) {
                set_stand();
            }
            break;

        default:
            break;
    }
}

void Player::move(Map *map)
{
    switch(m_action) {
        case Walk:
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }
            break;

        case Fall:
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }
            m_y += m_dy;
            break;

        case Jump:
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }
            m_y -= m_dy;
            break;

        default:
            break;
    }
}


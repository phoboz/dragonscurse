#include <iostream>
#include <string.h>
#include "phoboz/ctrl.h"
#include "phoboz/player.h"

void Player::move(Map *map)
{
    int input = get_input();

    // Check ground
    if (m_action != Jump) {
        m_dy = get_attribute("weight");
        check_below(map);
        if (m_dy) {
            m_action = Fall;
        }
        else if (m_action == Fall) {
            set_still();
        }
    }

    switch(m_action) {
        case Still:
            m_dx = 0;
        case Move:
            if (input & PRESS_RIGHT) {
                set_move_dir(Right);
                animate_move();
                m_dx = get_attribute("move_speed");
            }
            else if (input & PRESS_LEFT) {
                set_move_dir(Left);
                animate_move();
                m_dx = get_attribute("move_speed");
            }
            else if (m_action == Move) {
                set_still();
                m_dx = 0;
            }

            // Check for jump
            if (input & PRESS_JUMP) {
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

            // Move
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }
            break;

        case Fall:
            // Below is already checked if action is not Jump
            check_ahead(map);

            // Move
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }

            check_below(map);
            m_y += m_dy;
            break;

        case Jump:
            if (input & PRESS_RIGHT) {
                set_move_dir(Right);
                set_jump();
                m_dx = get_attribute("move_speed");
            }
            else if (input & PRESS_LEFT) {
                set_move_dir(Left);
                set_jump();
                m_dx = get_attribute("move_speed");
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

            // Move
            if (m_dir == Right) {
                m_x += m_dx;
            }
            else if (m_dir == Left) {
                m_x -= m_dx;
            }

            // Check if hit head
            if (check_above(map)) {
                m_action = Fall;
                m_jump_counter = 0;
            }
            m_y -= m_dy;
            break;

        case Crouch:
            if (!(input & PRESS_DOWN)) {
                set_still();
            }
            break;

        default:
            break;
    }
}


#include <stdio.h>
#include <string.h>
#include "phoboz/ctrl.h"
#include "dragon.h"

void Dragon::move(Map *map)
{
    int input = get_input();

    // Check fall
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

    // Check leave crouch
    if (m_action == Crouch) {
        set_stand();
    }

    // Check inputs for walk
    if (m_action == Stand || m_action == Walk) {
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
    }


    // Movement for walk
    if (m_action == Walk) {
        check_ahead(map);
        if (m_dir == Right) {
            m_x += m_dx;
        }
        else if (m_dir == Left) {
            m_x -= m_dx;
        }
    }

    // Movement for fall
    if (m_action == Fall) {
        // Test
        check_ahead(map);
        if (m_dir == Right) {
            m_x += m_dx;
        }
        else if (m_dir == Left) {
            m_x -= m_dx;
        }
        m_y += m_dy;
    }

    // Movement for jump
    if (m_action == Jump) {
        if (check_above(map)) {
            m_action = Fall;
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
        if (m_dir == Right) {
            m_x += m_dx;
        }
        else if (m_dir == Left) {
            m_x -= m_dx;
        }
        m_y -= m_dy;
    }
}


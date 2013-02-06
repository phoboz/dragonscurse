#include <iostream>
#include <string.h>
#include "phoboz/ctrl.h"
#include "phoboz/dragon.h"

Dragon::Dragon(const char *fn)
        : Object(Object::Player),
          m_jump_counter(0), m_jump_ready(true),
          m_bullet(0)
{
    Object::load(fn);
    m_bullet = new Bullet(get_string("bullet"));
    if (!m_bullet->get_loaded()) exit(1);
}

void Dragon::move(Map *map)
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
            set_stand();
        }
    }

    switch(m_action) {
        case Stand:
            m_dx = 0;
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
                set_dir(Right);
                set_jump();
                m_dx = get_attribute("walk_speed");
            }
            else if (input & PRESS_LEFT) {
                set_dir(Left);
                set_jump();
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
                set_stand();
            }
            break;

        default:
            break;
    }

    // TODO: Check in which state it shall be possible to fire
    if (input & PRESS_ENTER) {
        if (m_dir == Right) {
            m_bullet->fire(m_x + get_attribute("right"), m_y, m_dir);
        }
        else {
            m_bullet->fire(m_x + get_attribute("left"), m_y, m_dir);
        }
    }

    // Move bullet
    m_bullet->move(map);
}

void Dragon::draw(SDL_Surface *dest, Map *map,
                  int clip_x, int clip_y, int clip_w, int clip_h) const
{
    Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    m_bullet->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
}


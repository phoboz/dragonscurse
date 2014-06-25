#include <iostream>
#include <string.h>
#include "phoboz/ctrl.h"
#include "item.h"
#include "player.h"

bool Player::set_hit(Object *object)
{
    bool result = false;

    if (!m_invisible) {
        // TODO: Check if player hp is above zero instead
        result = Actor::set_hit(object);

        // Make player invisible for a certain time
        set_invisible(true);
    }

    return result;
}

bool Player::check_collision(Object *object)
{
    const Sprite *spr = get_sprite();

    return spr->check_collision(m_frame, m_x, m_y,
                                get_attribute("left"), get_attribute("top"),
                                get_attribute("right"), get_attribute("bottom"),
                                object->get_sprite(), object->get_frame(),
                                object->get_x(), object->get_y());
}

void Player::move(Map *map)
{
    Actor::move(map);

    // Check ground
    check_ground(map);

    // Handle hit
    if (m_hit == HitOne) {
        if (m_hit_timer.expired(get_attribute("hit_time"))) {
            m_dx = 0;
            set_still();
            m_hit = HitNone;
        }
        else {
            // Move backwards and upwards
            m_dx = get_attribute("move_speed");
            m_dy = m_dx;

            // Check for collision with map
            check_behind(map);
            check_above(map);

            // Move
            if (m_dir == Right) {
                m_x -= m_dx;
            }
            else if (m_dir == Left) {
                m_x += m_dx;
            }
            m_y -= m_dy;
        }
    }
    else {
        int input = get_input();
        switch(m_action) {
            case Still:
                m_dx = 0;
            case Move:
                if (m_attack == AttackNone) {
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
                            m_jump_timer.reset();
                            m_jump_ready = false;
                            set_jump_dir();
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
                }
                break;

            case Fall:
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
                    set_jump_dir(Right);
                    m_dx = get_attribute("move_speed");
                }
                else if (input & PRESS_LEFT) {
                    set_jump_dir(Left);
                    m_dx = get_attribute("move_speed");
                }
                else {
                    m_dx = 0;
                }

                // Check jump height
                if (m_jump_timer.expired(get_attribute("jump_limit"))) {
                    set_fall();
                }
                else {
                    m_dy = get_attribute("jump_speed");
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
                    m_jump_timer.reset();
                    set_fall();
                }
                m_y -= m_dy;
                break;

            case Catapult:
                if (input & PRESS_RIGHT) {
                    set_catapult_dir(Right);
                    m_dx = get_attribute("move_speed");
                }
                else if (input & PRESS_LEFT) {
                    set_catapult_dir(Left);
                    m_dx = get_attribute("move_speed");
                }
                else {
                    m_dx = 0;
                }

                // Check jump height
                if (m_jump_timer.expired(2 * get_attribute("jump_limit"))) {
                    set_fall();
                }
                else {
                    m_dy = get_attribute("jump_speed");
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
                    m_jump_timer.reset();
                    set_fall();
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
}

Item* Player::check_item(const char *name)
{
    Item *result = 0;

    for (std::list<Item*>::iterator it = m_items.begin();
         it != m_items.end();
         ++it) {

        Item *item = *it;
        if (strcmp(name, item->get_filename()) == 0) {
            result = item;
            break;
        }
    }

    return result;
}


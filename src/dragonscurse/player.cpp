#include <iostream>
#include <string.h>
#include "phoboz/ctrl.h"
#include "morph.h"
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

bool Player::is_morphing()
{
    bool result = false;

    if (m_morph) {
        if (m_morph->is_done()) {
            delete m_morph;
            m_morph = 0;
        }
        else {
            result = true;
        }
    }

    return result;
}

void Player::player_move(Map *map)
{
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if under water
    int start = prop.GetNumericProperty("water_start");
    int end = prop.GetNumericProperty("water_end");
    if (start && check_ahead(map, 1, start, end) == 0) {
        if (!m_water_timer.expired(3)) {
            return;
        }

        m_water_timer.reset();
    }

    // Check if on catapult
    int catid = prop.GetNumericProperty("catapult");
    if (catid && check_below(map, 1, catid, catid) == 0) {
        set_vy(int(-get_attribute("catapult_speed")));
        set_action(Jump);
    }

    Actor::move(map);
    set_ay(get_attribute("weight"));

    // Handle hit
    if (m_hit == HitOne) {
        if (m_hit_timer.expired(get_attribute("hit_time"))) {
            m_dx = 0;
            set_action(Still);
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
                set_vx(0);

            case Move:
                if (input & PRESS_RIGHT) {
                    animate_move();
                    set_action(Move);
                    set_vx(get_attribute("move_speed"));
                }
                else if (input & PRESS_LEFT) {
                    animate_move();
                    set_action(Move);
                    set_vx(-get_attribute("move_speed"));
                }
                else if (m_action == Move) {
                    set_action(Still);
                    set_vx(0);
                }

                Body::move(map);
                if (get_fall()) {
                    set_action(Fall);
                }

                // Check for jump
                if (input & PRESS_JUMP) {
                    if (m_jump_ready) {
                        m_jump_ready = false;
                        set_action(Jump);
                        set_vy(-get_attribute("jump_speed"));
                    }
                }
                else {
                    m_jump_ready = true;

                    // Check for crouch
                    if (input & PRESS_DOWN) {
                        set_action(Crouch);
                    }
                }
                break;

            case Fall:
                if (input & PRESS_RIGHT) {
                    set_vx(get_attribute("move_speed"));
                }
                else if (input & PRESS_LEFT) {
                    set_vx(-get_attribute("move_speed"));
                }
                else if (m_action == Move) {
                    set_action(Still);
                    set_vx(0);
                }

                Body::move(map);
                if (!get_fall()) {
                    set_action(Still);
                }
                break;

            case Jump:
                Body::move(map);
                if (get_fall()) {
                    set_action(Still);
                }
                break;

            case Crouch:
                set_vx(0);
                Body::move(map);

                if (!(input & PRESS_DOWN)) {
                    set_action(Still);
                }
                break;

            default:
                break;
        }
    }
}

void Player::move(Map *map)
{
    if (is_morphing()) {
        m_morph->move(map);
    }
    else {
        player_move(map);
    }
}

void Player::draw(SDL_Surface *dest, Map *map,
                  int clip_x, int clip_y, int clip_w, int clip_h)
{
    if (is_morphing()) {
        m_morph->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
    else {
        Actor::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


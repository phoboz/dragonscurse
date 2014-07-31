#include <iostream>
#include <string.h>
#include "phoboz/ctrl.h"
#include "morph.h"
#include "item.h"
#include "player.h"

Player::Player(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Actor(Object::TypePlayer, x, y, dir),
      m_morph(0), m_area(0),
      m_jump_ready(true), m_in_water(false)
{
    load(fn, media);
    set_ay(get_attribute("weight"));
}

void Player::set_jump(Map *map)
{
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if under water
    int start = prop.GetNumericProperty("water_start");
    int end = prop.GetNumericProperty("water_end");
    if (start && !check_center(map, start, end) == 0) {
        set_ay(-get_attribute("water_jump_power"));
        m_in_water = true;
    }
    else {
        set_ay(-get_attribute("jump_power"));
        m_in_water = false;
    }

    set_action(Jump);
}

void Player::reset_jump(bool reset)
{
    if (m_in_water) {
        set_ay(get_attribute("water_weight"));
    }
    else {
        set_ay(get_attribute("weight"));
    }

    if (reset) {
        m_jump_timer.reset();
        set_vx(0);
    }
}

bool Player::set_hit(Object *object)
{
    bool result = false;

    if (!m_invisible) {
        // TODO: Check if player hp is above zero instead
        result = Actor::set_hit(object);
        if (result) {

            reset_jump();
            set_lock_direction(true);

            // Move backwards and upwards
            if (m_dir == Right) {
                set_speed(-get_attribute("move_speed"),
                          -get_attribute("weight"));
            }
            else {
                set_speed(get_attribute("move_speed"),
                          -get_attribute("weight"));
            }

            // Make player invisible for a certain time
            set_invisible(true);
        }
    }

    return result;
}

bool Player::check_collision(Object *object) const
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
    Actor::move(map);

    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if on catapult
    int catid = prop.GetNumericProperty("catapult");
    if (catid && check_below(map, 1, catid, catid) == 0) {
        set_jump(map);
        set_vy(int(-get_attribute("catapult_speed")));
    }

    int input = get_input();
    switch(m_action) {
        case Still:
            reset_jump();

        case Move:
            // Check for jump
            if (input & PRESS_JUMP) {
                if (m_jump_ready) {
                    m_jump_ready = false;
                    if (input & PRESS_RIGHT) {
                        set_vx(get_attribute("jump_forward"));
                    }
                    else if (input & PRESS_LEFT) {
                        set_vx(-get_attribute("jump_forward"));
                    }
                    set_jump(map);
                }
            }
            else {
                // Restore jump lock
                m_jump_ready = true;

                // Check for crouch or move
                if (input & PRESS_DOWN) {
                    set_action(Crouch);
                }
                else if (input & PRESS_RIGHT) {
                    animate_move();
                    set_action(Move);
                    set_vx(get_attribute("move_speed"));
                }
                else if (input & PRESS_LEFT) {
                    animate_move();
                    set_action(Move);
                    set_vx(-get_attribute("move_speed"));
                }
                else {
                    set_action(Still);
                }
            }

            Body::move(map);
            if (get_fall()) {
                set_action(Fall);
            }
            break;

        case Fall:
            // Check for change of direction during fall
            if (input & PRESS_RIGHT) {
                set_vx(get_attribute("jump_forward"));
            }
            else if (input & PRESS_LEFT) {
                set_vx(-get_attribute("jump_forward"));
            }

            Body::move(map);
            if (!get_fall()) {
                set_action(Still);
            }
            break;

        case Jump:
            if (m_jump_timer.check(get_attribute("jump_time"))) {
                reset_jump(false);
            }
            Body::move(map);
            if (get_fall()) {
                m_jump_timer.reset();
                set_action(Fall);
            }
            break;

        case Crouch:
            reset_jump();
            Body::move(map);

            if (!(input & PRESS_DOWN)) {
                set_action(Still);
            }
            break;

        case Hit:
            if (m_hit_timer.expired(get_attribute("hit_time"))) {
                m_hit_timer.reset();
                set_vx(0);
                set_lock_direction(false);
                m_hit = HitNone;
                set_action(Still);
            }
            Body::move(map);
            break;

        default:
            reset_jump();
            Body::move(map);
            break;
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


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
        if (result) {

            set_lock_direction(true);

            // Move backwards and upwards
            if (m_dir == Right) {
                set_speed(-get_attribute("move_speed"),
                          -get_attribute("jump_speed"));
            }
            else {
                set_speed(get_attribute("move_speed"),
                          -get_attribute("jump_speed"));
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
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if under water
    int start = prop.GetNumericProperty("water_start");
    int end = prop.GetNumericProperty("water_end");
    if (start && check_ahead(map, 1, start, end) == 0) {
        if (!m_water_timer.expired(get_attribute("water_treshold"))) {
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

    int input = get_input();
    switch(m_action) {
        case Still:
            set_vx(0);

        case Move:
            // Check for jump
            if (input & PRESS_JUMP) {
                if (m_jump_ready) {
                    m_jump_ready = false;
                    set_action(Jump);
                    if (input & PRESS_RIGHT) {
                        set_speed(get_attribute("jump_forward"),
                                  -get_attribute("jump_speed"));
                    }
                    else if (input & PRESS_LEFT) {
                        set_speed(-get_attribute("jump_forward"),
                                  -get_attribute("jump_speed"));
                    }
                    else {
                        set_vy(-get_attribute("jump_speed"));
                    }
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
                    set_vx(0);
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
            Body::move(map);
            if (get_fall()) {
                set_action(Fall);
            }
            break;

        case Crouch:
            set_vx(0);
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


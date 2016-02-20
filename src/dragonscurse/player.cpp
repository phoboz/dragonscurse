#include <string.h>
#include "phoboz/ctrl.h"
#include "status.h"
#include "morph.h"
#include "item.h"
#include "monster.h"
#include "player.h"

Player::Player(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Actor(Object::TypePlayer, x, y, dir),
      m_morph(0), m_area(0),
      m_jump_ready(true), m_in_water(false)
{
    load(fn, media);
    set_ay(get_attribute("weight"));
}

void Player::check_water(Map *map)
{
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if under water
    int start = prop.GetNumericProperty("water_start");
    int end = prop.GetNumericProperty("water_end");
    if (start && check_center(map, start, end)) {
        set_ay(get_attribute("water_weight"));
        m_in_water = true;
    }
    else {
        if (m_in_water) {
            if (m_action == Jump) {
                set_vy(-get_attribute("water_jump_speed"));
            }
            else if (m_action == Catapult) {
                set_vy(-get_attribute("water_catapult_speed"));
            }
        }
        set_ay(get_attribute("weight"));
        m_in_water = false;
    }
}

void Player::set_jump(Map *map, bool catapult)
{
    m_media->play_sound("jump.wav");

    if (m_in_water) {
        if (catapult) {
            set_vy(-get_attribute("water_catapult_speed"));
            set_action(Catapult);
        }
        else {
            set_vy(-get_attribute("water_jump_speed"));
            set_action(Jump);
        }
    }
    else {
        if (catapult) {
            set_vy(-get_attribute("catapult_speed"));
            set_action(Catapult);
        }
        else {
            set_vy(-get_attribute("jump_speed"));
            set_action(Jump);
        }
    }
}

void Player::set_attack()
{
    if (m_action == Move) {
        set_vx(0);
    }

    Actor::set_attack();
}

bool Player::set_hit(Object *object, Status *status)
{
    bool result = false;

    if (!m_invisible) {
        result = Actor::set_hit(object);
        if (result) {

            set_lock_direction(true);

            // Move backwards and upwards
            if (m_dir == Right) {
                set_vx(-get_attribute("move_speed"));
            }
            else {
                set_vx(get_attribute("move_speed"));
            }

            if (m_in_water) {
                set_vy(-get_attribute("water_jump_speed"));
            }
            else {
                set_vy(-get_attribute("jump_speed"));
            }

            Monster *monster = (Monster *) object;
            if (status->set_hit(monster->get_attribute("ap")) &&
                !status->use_potion()) {
                set_invisible(true);
                set_solid(false);
                set_perish(false);
            }
            else {
                // Make player invisible for a certain time
                set_invisible(true);
            }
        }
    }

    return result;
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

    check_water(map);

    int input = get_input();

    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if on catapult
    int catid = prop.GetNumericProperty("catapult");
    if (catid && check_below(map, 1, catid, catid) == 0) {
        if (input & PRESS_RIGHT) {
            set_vx(get_attribute("move_speed"));
        }
        else if (input & PRESS_LEFT) {
            set_vx(-get_attribute("move_speed"));
        }
        set_jump(map, true);
    }

    switch(m_action) {
        case Still:
            set_vx(0);

        case Move:
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

            // Check for jump
            if (input & PRESS_JUMP) {

                if (m_jump_ready && hit_ground(map)) {
                    if (input & PRESS_RIGHT) {
                        set_vx(get_attribute("move_speed"));
                    }
                    else if (input & PRESS_LEFT) {
                        set_vx(-get_attribute("move_speed"));
                    }
                    set_jump(map, false);
                }
                m_jump_ready = false;
            }
            else {
                // Restore jump lock
                m_jump_ready = true;
            }

            Body::move(map);
            if (get_fall()) {
                set_action(Fall);
            }
            break;

        case Fall:
            // Check for change of direction during fall
            if (input & PRESS_RIGHT) {
                set_vx(get_attribute("move_speed"));
            }
            else if (input & PRESS_LEFT) {
                set_vx(-get_attribute("move_speed"));
            }

            Body::move(map);
            if (hit_ground(map)) {
                set_action(Still);
            }
            break;

        case Jump:
        case Catapult:
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
                set_vx(0);
                set_lock_direction(false);
                reset_hit();
            }
            Body::move(map);
            break;

        case HitPerish:
            animate_perish();
            set_speed(0, -get_attribute("move_speed"));
            Body::move(map);
            if (m_y < -get_image_height()) {
                set_solid(true);
                set_invisible(false);
                set_action(HitPerished);
            }
            break;

        case Attack:
        case AttackLow:
            if (animate_attack()) {
                reset_attack();
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

void Player::draw(Surface *dest, Map *map,
                  int clip_x, int clip_y, int clip_w, int clip_h)
{
    if (is_morphing()) {
        m_morph->draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
    else {
        Actor::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


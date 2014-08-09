#include <math.h>
#include "actor.h"
#include "bullet.h"

Bullet::Bullet(const char *fn, MediaDB *media)
    : Body(Object::TypeBullet),
      m_active(false), m_ready(true),
      m_distance(0), m_hit_one(false)
{
    load(fn, media);
    if (get_attribute("treshold")) {
        m_animated = true;
    }
    else {
        m_animated = false;
    }
}

void Bullet::set_dir(Direction dir)
{
    if (dir != m_dir) {
        if (dir == Right) {
            m_frame = get_attribute("right_move_start");
        }
        else if (dir == Left) {
            m_frame = get_attribute("left_move_start");
        }

        m_dir = dir;
    }
}

void Bullet::reload(bool active)
{
    m_ready = false;
    m_distance = 0;
    m_reload_timer.reset();
    m_active = active;
}

bool Bullet::hit_object(Object *object)
{
    bool result = false;

    if (m_active) {
        if (object->check_shielded_collision(this)) {
            // Remove bullet if it hits a shielded area
            reload(false);
        }
        else if (object->check_weak_collision(this)) {

            // Remove bullet if it only is supposed to hit one target
            if (m_hit_one) {
                if (object->get_type() == TypeMonster) {
                    Actor *actor = (Actor *) object;
                    if (actor->get_action() != Actor::HitPerish) {
                        reload(false);
                    }
                }
                else {
                    reload(false);
                }
            }
            result = true;
        }
    }

    return result;
}

void Bullet::animate_move()
{
    if (m_anim_timer.expired(get_attribute("treshold"))) {
        switch(m_dir) {
            case Right:
                if (++m_frame > get_attribute("right_move_end")) {
                    m_frame = get_attribute("right_move_start");
                }
                break;

            case Left:
                if (++m_frame > get_attribute("left_move_end")) {
                    m_frame = get_attribute("left_move_start");
                }
                break;

            default:
                break;
        }
    }
}

void Bullet::move(Map *map)
{
    if (m_reload_timer.expired(get_attribute("reload_time"))) {
        m_ready = true;
    }

    if (m_active) {
        if (m_animated) {
            animate_move();
        }

        if (m_distance < get_attribute("distance")) {
            Body::move(map);
            if (get_moving()) {
                m_distance += sqrt(m_dx * m_dx + m_dy * m_dy);
            }
            else {
                reload(false);
            }
        }
        else {
            reload(false);
        }
    }
}


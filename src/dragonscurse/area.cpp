#include <string.h>
#include "phoboz/ctrl.h"
#include "actor.h"
#include "area.h"

Area::Area(const char *name, const char *type,
           int x, int y, int w, int h, int lock_id)
    : Object(Object::TypeArea, x, y),
      m_name(name),
      m_h(h), m_w(w),
      m_lock_id(lock_id),
      m_state(StateIdle)
{
    if (strcmp(type, "warp") == 0) {
        m_type = TypeWarp;
    }
    else if (strcmp(type, "travel") == 0) {
        m_type = TypeTravel;
    }
    else {
        m_type = TypeUser;
        load(type);
    }

    m_frame = get_attribute("open_start");
}

void Area::set_lock(WorldDB::LockType lock)
{
    if (m_lock_id) {
        m_state = StateLocked;
        switch(m_lock) {
            case WorldDB::LockTypeGreen:
                m_frame = get_attribute("green_lock");
                break;

            case WorldDB::LockTypeRed:
                m_frame = get_attribute("red_lock");
                break;
        }
        m_lock = lock;
    }
}

bool Area::is_locked() const
{
    bool result = false;

    if (m_state == StateLocked) {
        result = true;
    }

    return result;
}

bool Area::inside(Actor *actor)
{
    bool result = false;
    int x = actor->get_front();
    int y = actor->get_bottom();

    // Check if inside
    if (x >= m_x && x <= m_x + m_w &&
        y >= m_y && y <= m_y + m_h) {
        if (m_type == TypeUser) {
            if (m_state == StateOpen) {
                result = true;
                m_state = StateIdle;
            }
        }
        else {
            result = true;
        }
    }

    return result;
}

void Area::move(Map *map)
{
    if (m_type == TypeUser) {
        if (m_state == StateIdle) {
            int input = get_input();
            if (input & PRESS_UP) {
                if (m_open_timer.expired(get_attribute("open_time"))) {
                    m_open_timer.reset();
                    m_state = StateOpening;
                }
            }
            else {
                m_open_timer.reset();
            }
        }
        else if (m_state == StateOpening) {
            if (m_anim_timer.expired(get_attribute("treshold"))) {
                if (++m_frame > get_attribute("open_end")) {
                    m_anim_timer.reset();
                    m_frame = get_attribute("open_start");
                    m_state = StateOpen;
                }
            }
        }
    }
}

void Area::draw(SDL_Surface *dest, Map *map,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    if (m_type == TypeUser) {
        Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


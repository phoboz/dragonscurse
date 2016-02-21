#include <string.h>
#include "phoboz/ctrl.h"
#include "actor.h"
#include "item.h"
#include "curse.h"
#include "world.h"
#include "world_db.h"
#include "area.h"

Area::Area(const char *name, MediaDB *media,
           const char *type, int x, int y, int w, int h)
    : Object(Object::TypeArea, x, y),
      m_name(name),
      m_w(w), m_h(h)
{
    if (strcmp(type, "warp") == 0) {
        m_type = TypeWarp;
        m_state = StateOpen;
        m_frame = 0;
    }
    else if (strcmp(type, "map") == 0) {
        m_type = TypeMap;
        m_state = StateOpen;
        m_frame = 0;
    }
    else {
        m_type = TypeUser;
        m_state = StateClosed;
        load(type, media);
        m_frame = get_attribute("open_start");
    }
}

Area::Area(Curse *curse)
    : Object(Object::TypeArea, curse->get_x(), curse->get_y()),
      m_name(curse->get_destination()),
      m_type(TypeCurse),
      m_w(curse->get_image_width()), m_h(curse->get_image_height()),
      m_data(curse->get_player()),
      m_state(StateOpen)
{
    m_sx = curse->get_sx();
    m_sy = curse->get_sy();
}

Area::Area(const char *destination, int sx, int sy)
    : Object(Object::TypeArea, 0, 0),
      m_name(destination),
      m_type(TypeWarp),
      m_w(0), m_h(0),
      m_state(StateOpen)
{
    m_sx = sx;
    m_sy = sy;
}

Area::Area(EventArea *area, MediaDB *media)
    : Object(Object::TypeArea, area->x, area->y),
      m_type(TypeUser),
      m_state(StateClosed),
      m_name(area->name),
      m_w(area->width), m_h(area->height)
{
    m_sx = area->start_x;
    m_sy = area->start_y;

    load(area->type, media);
    m_frame = get_attribute("open_start");
}

void Area::world_initialize(World *world)
{
    if (m_type != TypeMap) {
        m_sx = get_attribute("start_x");
        m_sy = get_attribute("start_y");
    }

    int lock_id = get_attribute("lock_id");

    if (lock_id) {
        WorldDB *db = world->get_db();
        LockInfo info;
        if (db->get_lock_info(&info, lock_id, world->get_filename())) {
            m_state = StateLocked;
            m_frame = get_attribute(info.lock_name);
            m_world_key = info.key;
            m_data = std::string(info.type_name);
            m_once = info.once;
        }
    }
}

bool Area::is_over(Actor *actor)
{
    bool result = false;
    int x = actor->get_front();
    int y = actor->get_bottom();

    // Check if inside
    if (x >= m_x && x <= m_x + m_w &&
        y >= m_y && y <= m_y + m_h) {

        // Special handling for map area temporary storage of delta components
        if (m_type == TypeMap) {
            if (m_state == StateOpen) {
                m_sx = actor->get_x() - m_x;
                m_sy = actor->get_y() - m_y;
            }
        }

        result = true;
    }
    else if (m_state == StateInactive) {
        m_state = StateOpen;
    }

    return result;
}

void Area::move(Map *map)
{
    if (m_type == TypeUser) {
        if (m_state == StateClosed) {
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
                    m_frame = get_attribute("open_end");
                    m_state = StateOpen;
                }
            }
        }
    }
}

bool Area::unlock(World *world, Item *item)
{
    bool result = false;

    if (m_type == TypeUser) {
        if (m_state == StateLocked) {
            if (m_data == std::string(item->get_filename())) {
                int input = get_input();
                if (input & PRESS_UP) {
                    if (m_open_timer.expired(get_attribute("open_time"))) {
                        m_open_timer.reset();

                        // Unlock in database
                        if (m_once) {
                            WorldDB *db = world->get_db();
                            db->remove(m_world_key);
                        }

                        // Mark as unlocked
                        m_state = StateClosed;
                        m_frame = get_attribute("open_start");
                        result = true;
                    }
                }
                else {
                    m_open_timer.reset();
                }
            }
        }
    }

    return result;
}

void Area::draw(Surface *dest, Map *map,
                int clip_x, int clip_y, int clip_w, int clip_h)
{
    if (m_type == TypeUser) {
        Object::draw(dest, map, clip_x, clip_y, clip_w, clip_h);
    }
}


bool Area::map_to_world(World *world)
{
    bool result = false;
    int id = get_attribute("destination_id");
    Area *area = world->find_area(get_attribute("destination_id"));

    if (area) {
        m_sx += area->get_x();
        m_sy += area->get_y();
        area->m_state = StateInactive;
        result = true;
    }

    return result;
}


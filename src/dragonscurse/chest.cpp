#include "world.h"
#include "world_db.h"
#include "object_factory.h"
#include "actor.h"
#include "chest.h"

Chest::Chest(const char *fn, MediaDB *media, int x, int y)
    : Object(TypeChest, x, y),
      m_media(media),
      m_state(StateClosed),
      m_db(0),
      m_world_key(-1),
      m_once(0)
{
    load(fn, media);
}

void Chest::world_initialize(World *world)
{
    m_db = world->get_db();
    int chest_id = get_attribute("chest_id");
    if (chest_id) {
        ChestInfo info;
        if (m_db->get_chest_info(&info, chest_id, world->get_filename())) {
            if (!info.user) {
                m_world_key = info.key;
                m_once = info.once;
                for (int i = 0; i < info.num_objects; i++) {
                    Object *object = ObjectFactory::create_object(
                                         &info.objects[i],
                                         m_media,
                                         get_x(),
                                         get_y());
                    if (object->get_type() == Object::TypeItem) {
                        ((Item *) object)->set_from_chest(true);
                    }
                    else if (object->get_type() == Object::TypeCollectable) {
                        ((Item *) object)->set_from_chest(true);
                    }
                    m_objects.push_back(object);
                }
            }
        }
    }
}

bool Chest::is_open(Actor *actor)
{
    bool result = false;

    if (m_state == StateOpen) {
        result = true;
    }
    else {
        int x = actor->get_front();
        int y = actor->get_bottom();
        int w = get_image_width();
        int h = get_image_height();

        // Check if inside
        if (x >= m_x && x <= m_x + w &&
            y >= m_y && y <= m_y + h) {
            m_frame = get_attribute("open");
            m_state = StateOpen;
            if (m_db) {
                if (m_once) {
                    m_db->remove(m_world_key);
                }
                else {
                    m_db->set_user(m_world_key, 1);
                }
            }
            result = true;
        }
    }

    return result;
}

Object* Chest::release_object()
{
    Object *object = 0;

    if (m_object_timer.expired(get_attribute("treshold"))) {
        m_object_timer.reset();
        if (m_objects.size()) {
            object = m_objects.back();
            m_objects.pop_back();
        }
    }

    return object;
}


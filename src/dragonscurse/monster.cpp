#include "world.h"
#include "item.h"
#include "coin.h"
#include "curse.h"
#include "object_factory.h"
#include "monster.h"

Monster::Monster(const char *fn, MediaDB *media, int x, int y, Direction dir)
    : Actor(Object::TypeMonster, x, y, dir),
      m_invinsible(false)
{
    load(fn, media);
    m_curr_hp = get_attribute("hp");
    set_still();
}

void Monster::world_initialize(World *world)
{
    Item *item = 0;
    int object_id = get_attribute("object_id");

    if (object_id) {
        WorldDB *db = world->get_db();
        ObjectInfo info;
        if (db->get_object_info(&info,
                                object_id, world->get_filename())) {
            switch(info.object_type) {
                case Object::TypeItem:
                    item = (Item *) ObjectFactory::create_object(
                                        info.data.item.name,
                                        m_media, "Item");
                    item->set_world_key(info.key);
                    m_objects.push_back(item);
                    break;

                case Object::TypeCurse:
                    m_objects.push_back(new Curse(&info, m_media));
                    break;

                default:
                    break;
            }
        }
    }
}

bool Monster::set_hit(Object *object)
{
    bool result = false;

    if (!m_invinsible && m_hit == HitNone) {
        Actor::set_hit(object);

        // Reduce hp
        // TODO: Get attackers attack power
        m_curr_hp--;
        if (m_curr_hp <= 0) {
            set_perish();
        }

        result = true;
    }

    return result;
}

Object* Monster::release_object()
{
    Object *object = 0;

    if (m_objects.size()) {
        object = m_objects.back();
        m_objects.pop_back();
    }
    else {
        const char *col = get_string("collectable");
        if (col) {
            object = ObjectFactory::create_object(col, m_media, "Collectable");
        }
    }

    return object;
}

void Monster::move(Map *map)
{
    if (m_hit == HitPerish) {
        if (m_perish_timer.expired(get_attribute("perish_time"))) {
            m_hit = HitPerished;
        }
    }
}


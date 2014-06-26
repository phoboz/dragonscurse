#include "world.h"
#include "item.h"
#include "curse.h"
#include "monster.h"

Monster::Monster(const char *fn, int x, int y, Direction dir)
    : Actor(Object::TypeMonster, x, y, dir),
      m_invinsible(false)
{
    load(fn);
    m_curr_hp = get_attribute("hp");
    set_still();
}

void Monster::world_initialize(World *world)
{
    int object_id = get_attribute("object_id");

    if (object_id) {
        WorldDB *db = world->get_db();
        int key;
        const char *fn = db->get_object_name(&key,
                                             object_id, world->get_filename());
        if (fn) {
            Object::Type type = db->get_object_type(object_id,
                                                    world->get_filename());
            switch(type) {
                case Object::TypeItem:
                    m_objects.push_back(new Item(fn, key));
                    break;

                case Object::TypeCurse:
                    m_objects.push_back(new Item(fn, key));
                    m_objects.push_back(new Curse(fn, key));
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


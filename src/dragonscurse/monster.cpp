#include "world.h"
#include "item.h"
#include "monster.h"

Monster::Monster(const char *fn, int x, int y, Direction dir)
    : Actor(Object::TypeEnemy, x, y, dir),
      m_invinsible(false),
      m_item(0)
{
    load(fn);
    m_curr_hp = get_attribute("hp");
    set_still();
}

void Monster::world_initialize(World *world)
{
    int item_id = get_attribute("item_id");

    if (item_id) {
        WorldDB *db = world->get_db();
        int key;
        const char *fn = db->get_item_name(&key,
                                           item_id, world->get_filename());
        if (fn) {
            m_item = new Item(fn, key);
        }
    }
}

void Monster::world_deinitialize(World *world)
{
    if (m_item) {
        m_item->aquire(world);
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

void Monster::move(Map *map)
{
    if (m_hit == HitPerish) {
        if (m_perish_timer.expired(get_attribute("perish_time"))) {
            m_hit = HitPerished;
        }
    }
}


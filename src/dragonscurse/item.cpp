#include "item.h"

Item::Item(const char *fn, int world_key)
    : Object(TypeItem),
      m_world_key(world_key)
{
    load(fn);
}

void Item::aquire(World *world)
{
    WorldDB *db = world->get_db();

    // TODO: Store item in player inventory
    std::cout << "Unlocks: " << get_string("lock_type") << std::endl;

    // Remove item from world database
    db->remove(m_world_key);
}


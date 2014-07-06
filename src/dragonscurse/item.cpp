#include "item.h"

void Item::aquire(World *world)
{
    WorldDB *db = world->get_db();

    // Remove item from world database
    db->remove(m_world_key);
}


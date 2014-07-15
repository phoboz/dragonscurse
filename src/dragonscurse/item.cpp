#include "item.h"

void Item::aquire(World *world)
{
    // Remove item from world database
    if (m_world_key > 0) {
        WorldDB *db = world->get_db();
        db->remove(m_world_key);
    }
}


#include "world_db.h"
#include "item.h"

void Item::aquire(WorldDB *db)
{
    db->remove(m_world_key);
}

void Item::aquire(World *world)
{
    // Remove item from world database
    WorldDB *db = world->get_db();
    aquire(db);
}


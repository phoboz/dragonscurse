#include "item.h"

void Item::aquire(World *world)
{
    // Remove item from world database
    WorldDB *db = world->get_db();
    aquire(db);
}


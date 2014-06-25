#include "item.h"

Item::Item(const char *fn, int world_key)
    : Object(TypeItem),
      m_world_key(world_key)
{
    load(fn);
}

Item::Item(const char *fn, int x, int y)
    : Object(TypeItem, x, y)
{
    load(fn);
}

void Item::aquire(World *world)
{
    WorldDB *db = world->get_db();

    // Remove item from world database
    db->remove(m_world_key);
}

void Item::move(Map *map)
{
    // TODO: Should impement the effect of gravity
}


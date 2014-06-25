#include "item.h"

Item::Item(const char *fn, int world_key)
    : Object(TypeItem),
      m_world_key(world_key)
{
    load(fn);

    m_dy = -get_attribute("move_speed");
    m_delta_y = m_dy;
}

Item::Item(const char *fn, int x, int y)
    : Object(TypeItem, x, y)
{
    Item(fn, 0);
}

void Item::aquire(World *world)
{
    WorldDB *db = world->get_db();

    // Remove item from world database
    db->remove(m_world_key);
}

void Item::check_ground(Map *map)
{
    const Tmx::Tileset *tileset = map->get_tileset(0);

    if (m_delta_y < 0) {
        m_dy = -m_delta_y;
        check_above(map);
        m_delta_y += get_attribute("weight");
    }
    else if (m_delta_y < tileset->GetTileHeight()) {
        m_dy = m_delta_y;
        check_below(map);
        m_delta_y += get_attribute("weight");
    }
}

void Item::move(Map *map)
{
    check_ground(map);

    if (m_delta_y > 0) {
        m_y += m_dy;
    }
    else if (m_delta_y < 0) {
        m_y -= m_dy;
    }
}


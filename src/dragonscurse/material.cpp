#include "material.h"

Material::Material(Type type, const char *fn, MediaDB *media)
    : Object(type)
{
    load(fn, media);

    m_dy = -get_attribute("move_speed");
    m_delta_y = m_dy;
}

Material::Material(Type type, const char *fn, MediaDB *media, int x, int y)
    : Object(type, x, y)
{
    load(fn, media);

    m_dy = -get_attribute("move_speed");
    m_delta_y = m_dy;
}

void Material::check_ground(Map *map)
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

void Material::move(Map *map)
{
    check_ground(map);

    if (m_delta_y > 0) {
        m_y += m_dy;
    }
    else if (m_delta_y < 0) {
        m_y -= m_dy;
    }
}


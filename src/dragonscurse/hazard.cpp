#include <string>
#include "hazard.h"

Hazard::Hazard(const char *fn, MediaDB *media)
    : Object(Object::TypeMonster)
{
    load(fn, media);

    const char *name = get_string("name");
    if (name) {
        m_start_name = std::string(name) + std::string("_start");
        m_end_name = std::string(name) + std::string("_end");
    }
}

bool Hazard::get_hazard_range(int *start, int *end, Map *map)
{
    int result = false;

    if (get_loaded()) {
        const Tmx::Tileset *tileset = map->get_tileset(0);
        const Tmx::PropertySet prop = tileset->GetProperties();

        // Get range of tiles
        *start = prop.GetNumericProperty(m_start_name.c_str());
        *end = prop.GetNumericProperty(m_end_name.c_str());

        result = true;
    }

    return result;
}


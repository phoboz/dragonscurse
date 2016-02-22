#include "phoboz/ctrl.h"
#include "natator.h"

bool Natator::in_medium(Map *map)
{
    bool result = false;
    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if under water
    int start = prop.GetNumericProperty("water_start");
    int end = prop.GetNumericProperty("water_end");
    if (check_center(map, start, end)) {
        result = true;
    }

    return result;
}


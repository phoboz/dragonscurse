#include "world.h"
#include "swimmer.h"

void Swimmer::world_initialize(World *world)
{
    Map *map = world->get_map();

    const Tmx::Tileset *tileset = map->get_tileset(0);
    const Tmx::PropertySet prop = tileset->GetProperties();

    // Check if under water
    int m_start_tile = prop.GetNumericProperty("water_start");
    int m_end_tile = prop.GetNumericProperty("water_end");
}


#ifndef _Item_H
#define _Item_H

#include "material.h"
#include "world.h"

class Item : public Material {
public:
    Item(const char *fn, MediaDB *media, int world_key)
        : Material(TypeItem, fn, media),
          m_world_key(world_key) { }
    Item(const char *fn, MediaDB *media, int x, int y)
        : Material(TypeItem, fn, media, x, y),
          m_world_key(0) { }

    void aquire(World *world);

private:

    int m_world_key;
};

#endif


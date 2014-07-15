#ifndef _Item_H
#define _Item_H

#include "material.h"
#include "world.h"

class Item : public Material {
public:
    enum ItemType { TypeKey, TypeSword, TypeShield, TypeArmour };

    Item(ItemType type, const char *fn, MediaDB *media, int x, int y)
        : Material(TypeItem, fn, media, x, y),
          m_item_type(type),
          m_world_key(-1) { }

    void set_world_key(int key) {
        m_world_key = key;
    }

    void aquire(World *world);

private:

    int m_world_key;
    ItemType m_item_type;
};

#endif


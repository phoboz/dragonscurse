#ifndef _Collectable_H
#define _Collectable_H

#include "material.h"
#include "world_db.h"

class Collectable : public Material {
public:
    enum CollectableType {
        TypeGold,
        TypeHeartContainer,
        TypeHeartRefill,
        TypePotion,
        TypeStone,
        TypeFireRefill,
        TypeTornadoRefill,
        TypeArrowRefill,
        TypeBoomerangRefill,
        TypeThunderRefill,
        TypeBreakRock,
        TypeCreateRock
    };

    CollectableType get_collectable_type() const { return m_collectable_type; }
    int get_value() const { return m_value; }

protected:
    Collectable(CollectableType type, const char *fn, MediaDB *media,
                int x, int y)
        : Material(TypeCollectable, fn, media, x, y),
          m_collectable_type(type) { }

    void set_value(int value) { m_value = value; }

private:
    CollectableType m_collectable_type;
    int m_value;
};

#endif


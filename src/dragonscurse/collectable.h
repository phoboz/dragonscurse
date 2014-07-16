#ifndef _Collectable_H
#define _Collectable_H

#include "material.h"

class Collectable : public Material {
public:
    enum CollectableType { TypeGold };

    CollectableType get_collectable_type() const { return m_collectable_type; }
    int get_value() const { return m_value; }

protected:
    int m_value;

    Collectable(CollectableType type, const char *fn, MediaDB *media,
                int x, int y)
        : Material(TypeCollectable, fn, media, x, y),
          m_collectable_type(type),
          m_value(0) { }

private:
    CollectableType m_collectable_type;
};

#endif


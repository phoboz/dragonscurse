#ifndef _Collectable_H
#define _Collectable_H

#include "material.h"

class Collectable : public Material {
public:
    int get_value() const { return m_value; }

protected:
    int m_value;

    Collectable(const char *fn, MediaDB *media, int x, int y)
        : Material(TypeCollectable, fn, media, x, y),
          m_value(0) { }
};

#endif


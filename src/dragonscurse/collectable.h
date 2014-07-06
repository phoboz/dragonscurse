#ifndef _Collectable_H
#define _Collectable_H

#include "material.h"

class Collectable : public Material {
public:
    int get_value() const { return m_value; }

protected:
    int m_value;

    Collectable(const char *fn, MediaDB *media, int value = 0)
        : Material(TypeCollectable, fn, media),
          m_value(value) { }
};

#endif


#ifndef _Collectable_H
#define _Collectable_H

#include "material.h"

class Collectable : public Material {
protected:
    Collectable(const char *fn, MediaDB *media)
        : Material(TypeCollectable, fn, media) { }
};

#endif


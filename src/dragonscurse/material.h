#ifndef _Material_H
#define _Material_H

#include "object.h"

class Material : public Object {
public:
    virtual void move(Map *map);

protected:
    Material(Type type, const char *fn, MediaDB *media, int x, int y);

    void check_ground(Map *map);

    int m_delta_y;
};

#endif


#ifndef _Chest_H
#define _Chest_H

#include <vector>
#include "object.h"

class Chest : public Object {
public:
    Chest(const char *fn, MediaDB *media, int x, int y);


    virtual void world_initialize(World *world);

    virtual void move(Map *map) { }

private:
    std::vector<Object*> m_objects;
};

#endif


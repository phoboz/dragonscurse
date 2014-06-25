#ifndef _Item_H
#define _Item_H

#include "object.h"
#include "world.h"

class Item : public Object {
public:
    Item(const char *fn, int world_key);
    Item(const char *fn, int x, int y);

    void aquire(World *world);

    void move(Map *map);

private:
    int m_world_key;
};

#endif


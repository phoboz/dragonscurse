#ifndef _Natator_H
#define _Natator_H

#include "knight.h"

class Natator : public Knight {
public:
    Natator(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Knight(fn, media, x, y, dir), 
          m_swimming(false) { }

    virtual bool set_hit(Object *object, Status *status);

    void move_swim(Map *map);
    virtual void move(Map *map);

private:
    bool m_swimming;

    bool in_water(Map *map);
};

#endif


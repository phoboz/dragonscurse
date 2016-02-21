#ifndef _Natator_H
#define _Natator_H

#include "phoboz/timer.h"
#include "knight.h"

class Natator : public Knight {
public:
    Natator(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Knight(fn, media, x, y, dir), 
          m_swimming(false) { }

    virtual void set_dir(Direction dir);
    virtual bool set_hit(Object *object, Status *status);

    void move_swim(Map *map);
    virtual void move(Map *map);

private:
    bool m_swimming;
    Timer m_swim_timer;

    void set_swim_dir(Direction set_dir);
    bool in_water(Map *map);
    void animate_swim();
};

#endif


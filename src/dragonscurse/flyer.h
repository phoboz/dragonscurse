#ifndef _Flyer_H
#define _Flyer_H

#include <string>
#include "phoboz/timer.h"
#include "knight.h"

class Flyer : public Knight {
public:
    Flyer(const char *fn, MediaDB *media, int x, int y, Direction dir)
        : Knight(fn, media, x, y, dir), 
          m_flying(false) { }

    virtual void set_dir(Direction dir);
    virtual bool set_hit(Object *object, Status *status, Map *map);

    void move_fly(Map *map, int input);
    virtual void move(Map *map);

private:
    std::string m_medium_start, m_medium_end;
    bool m_flying;
    Timer m_rise_timer;

    void set_rise_dir(Direction set_dir);
    virtual bool in_medium(Map *map) { return true; }
    void animate_rise();
};

#endif

